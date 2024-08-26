/*
 * motorTask.c
 *
 *  Created on: Jun 22, 2024
 *      Author: Victor Kalenda
 */

#include "motorTask.h"

#include "main.h"
#include "cmsis_os.h"
#include "motor.h"
#include <gui/common/definitions.h>

// Timing
volatile uint32_t start_time = 0;
uint32_t delay = 0;

// Analog Throttle Variables
uint16_t throttle_threshold = 100;
uint16_t throttle_min = 1085;
uint16_t throttle_max = 3205;
uint32_t filtered_throttle;
int32_t duty_cycle = 0;
int32_t acceleration;

// Analog Brake Variables
uint16_t brake_threshold = 10;
uint16_t brake_min = 1085;
uint16_t brake_max = 3205;
uint32_t filtered_brake;
uint8_t analog_brake_active = 0;

// Digital Brake Variables
float brake_magnitude = 0;
uint16_t brake_rate = 10; // A rate in seconds of how quickly the regen brake will reach 100% in magnitude

float motor_frequency = 1;

volatile uint16_t adc_buffer[2];
volatile uint16_t sensor_data[2];

extern osMessageQueueId_t adcQueueHandle;

extern UART_HandleTypeDef huart3;
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

extern osThreadId_t motorTaskHandle;
extern osSemaphoreId_t suspend_motor_taskHandle;
extern osSemaphoreId_t motor_timing_modifiedHandle;
extern osSemaphoreId_t collect_adc_dataHandle;
extern osMutexId_t settingMutexHandle;

extern char uart_tx[64];

volatile uint8_t brake_sensor = 0;

void handle_motor_task_suspension();
void handle_motor_timing();

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == BRAKE_Pin)
	{
		start_time = osKernelGetTickCount();
		// reverse time to make the motor immediately deactivate or activate upon interrupt
		if(HAL_GPIO_ReadPin(BRAKE_GPIO_Port, BRAKE_Pin) == GPIO_PIN_SET)
		{
			brake_sensor = 0;
		}
		else
		{
			brake_sensor = 1;
		}
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if(osSemaphoreGetCount(collect_adc_dataHandle))
	{
		sensor_data[THROTTLE] = adc_buffer[THROTTLE];
		sensor_data[BRAKE] = adc_buffer[BRAKE];
		osSemaphoreAcquire(collect_adc_dataHandle, 0);
	}
}

void motorTask_init()
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_buffer, 2);
}

void motorTask_poll()
{
	handle_motor_task_suspension();

	sprintf(uart_tx, "throttle: ");
	HAL_UART_Transmit(&huart3, (uint8_t*)uart_tx, 10, HAL_MAX_DELAY);

	sprintf(uart_tx, "%u", adc_buffer[THROTTLE]);
	HAL_UART_Transmit(&huart3, (uint8_t*)uart_tx, sizeof(uart_tx), HAL_MAX_DELAY);

	sprintf(uart_tx, "brake: ");
	HAL_UART_Transmit(&huart3, (uint8_t*)uart_tx, 7, HAL_MAX_DELAY);

	sprintf(uart_tx, "%u\r\n", adc_buffer[BRAKE]);
	HAL_UART_Transmit(&huart3, (uint8_t*)uart_tx, sizeof(uart_tx), HAL_MAX_DELAY);

	// This is for digital brake regen braking, it is disabled by default
	if(brake_sensor)
	{
		if(!analog_brake_active)
		{
			// Activate regenerative breaking to slow the bike down to the appropriate speed
			handle_digital_brake(osKernelGetSysTimerCount() - start_time, &brake_magnitude);
			comm_can_set_current_brake_rel(MOTOR_CAN_ID, brake_magnitude);
		}
	}
	else
	{
		// ensure the sensor value is reasonable to send to the motor
		filter_sensor_data(adc_buffer[THROTTLE], &filtered_throttle, &acceleration, throttle_threshold);
		duty_cycle = map(filtered_throttle, throttle_min, throttle_max, 0, 100);

		sprintf(uart_tx, "%d\r\n", duty_cycle);
		HAL_UART_Transmit(&huart3, (uint8_t*)uart_tx, sizeof(uart_tx), HAL_MAX_DELAY);

		if(acceleration > 0)
		{
			// Activate the motor to accelerate to the desired speed
		}
		else
		{
			// Activate regenerative breaking to slow the bike down to the appropriate speed
		}
	}
	// handle_the analog brake sensor
	if(analog_brake_active)
	{
		filter_sensor_data(adc_buffer[BRAKE], &filtered_brake, &acceleration, brake_threshold);
		duty_cycle = map(filtered_brake, brake_min, brake_max, 0, 100);
		if(acceleration > 0)
		{
			// Activate the regen brake to accelerate to the desired brake magnitude
		}
	}

	handle_motor_timing();
}

void handle_motor_task_suspension()
{
	if(osSemaphoreGetCount(suspend_motor_taskHandle))
	{
		osThreadSuspend(motorTaskHandle);
	}
}

void handle_motor_timing()
{
	if(osSemaphoreGetCount(motor_timing_modifiedHandle))
	{
		// the refresh rate has been changed
		int8_t status = osMutexAcquire(settingMutexHandle, osWaitForever);
		if(status == osOK)
		{
			// Safety Check, ensure that an invalid value doesn't result in no delay
			if(motor_frequency < 0 || motor_frequency > 1000)
			{
				motor_frequency = 1.0;

				// Setup the delay variable regardless of EE is written properly
				delay = (uint32_t) (1000 / motor_frequency);

				if(EE_Write())
				{
					// Only change the state of the timing semaphore if the refresh rate
					// was successfully written to EE, otherwise make the task retry
					osSemaphoreAcquire(motor_timing_modifiedHandle, 0);
				}
				else
				{
					// Ensure the next iteration will attempt the EE_Write operation again
					motor_frequency = 0;
				}
			}
			else
			{
				delay = (uint32_t)(1000 / motor_frequency);

				osSemaphoreAcquire(motor_timing_modifiedHandle, 0);
			}
			osMutexRelease(settingMutexHandle);
		}
	}
	osDelayUntil(osKernelGetTickCount() + (delay / portTICK_PERIOD_MS));
}
