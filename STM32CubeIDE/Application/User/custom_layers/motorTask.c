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
#include <stdio.h>
#include "ee.h"

// Timing
volatile uint32_t start_time = 0;
uint32_t motor_delay = 0;

// Analog Throttle Variables
uint16_t filtered_throttle = 0;

// Analog Brake Variables
uint16_t filtered_brake = 0;

int32_t duty_cycle = 0;
int32_t acceleration;

// Digital Brake Variables
float brake_magnitude = 0;

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

extern ee_Storage_t ee;

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

	if(osMutexAcquire(settingMutexHandle, osWaitForever) == osOK)
	{
		if(brake_sensor)
		{
			// Digital brake handling
			if(!ee.analog_brake_active)
			{
				// Activate regenerative breaking to slow the bike down to the appropriate speed
				handle_digital_brake(osKernelGetSysTimerCount() - start_time, &brake_magnitude, ee.brake_rate);
				comm_can_set_current_brake_rel(MOTOR_CAN_ID, brake_magnitude);
			}
		}
		else
		{
			// Ensure the sensor value is reasonable to send to the motor
			filter_sensor_data(adc_buffer[THROTTLE], &filtered_throttle, &acceleration, ee.throttle_threshold);
			duty_cycle = map(filtered_throttle, ee.throttle_min, ee.throttle_max, 0, 100);

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
		if(ee.analog_brake_active)
		{
			// Analog brake handling
			filter_sensor_data(adc_buffer[BRAKE], &filtered_brake, &acceleration, ee.brake_threshold);
			duty_cycle = map(filtered_brake, ee.brake_min, ee.brake_max, 0, 100);
			if(acceleration > 0)
			{
				// Activate the regen brake to accelerate to the desired brake magnitude
			}
		}
		osMutexRelease(settingMutexHandle);
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
		if(osMutexAcquire(settingMutexHandle, osWaitForever) == osOK)
		{
			// Safety Check, ensure that an invalid value doesn't result in no motor_delay
			if(ee.motor_frequency < 0 || ee.motor_frequency > 1000)
			{
				ee.motor_frequency = 1.0;

				// Setup the motor_delay variable regardless of EE is written properly
				motor_delay = (uint32_t) (1000 / ee.motor_frequency);

				if(EE_Write())
				{
					// Only change the state of the timing semaphore if the refresh rate
					// was successfully written to EE, otherwise make the task retry
					osSemaphoreAcquire(motor_timing_modifiedHandle, 0);
				}
				else
				{
					// Ensure the next iteration will attempt the EE_Write operation again
					ee.motor_frequency = 0;
				}
			}
			else
			{
				motor_delay = (uint32_t)(1000 / ee.motor_frequency);

				osSemaphoreAcquire(motor_timing_modifiedHandle, 0);
			}
			osMutexRelease(settingMutexHandle);
		}
	}
	osDelayUntil(osKernelGetTickCount() + (motor_delay / portTICK_PERIOD_MS));
}
