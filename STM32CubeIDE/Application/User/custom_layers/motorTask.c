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

adcRetrievalState adc_retrieval;

// Analog Throttle Variables
uint16_t throttle_threshold = 100;
uint16_t throttle_min = 1085;
uint16_t throttle_max = 3205;
uint32_t filtered_throttle;
uint32_t duty_cycle = 0;
int32_t acceleration;

// Analog Brake Variables
uint16_t brake_threshold = 10;
uint16_t brake_min = 1085;
uint16_t brake_max = 3205;
uint32_t filtered_brake;

// Digital brake Variables
float brake_magnitude = 0;
uint16_t brake_rate = 10; // A rate in seconds of how quickly the regen brake will reach 100% in magnitude

volatile uint16_t throttle_data;
volatile uint16_t brake_data;
volatile uint16_t sensor_buffer[2];


extern osThreadId_t motorTaskHandle;
extern osMessageQueueId_t adcQueueHandle;

extern UART_HandleTypeDef huart3;
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

extern char uart_tx[64];

volatile uint8_t brake_sensor = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == BRAKE_Pin)
	{
		// reverse time to make the motor immediately deactivate or activate upon interrupt
		if(HAL_GPIO_ReadPin(BRAKE_GPIO_Port, BRAKE_Pin) == GPIO_PIN_SET)
		{
			brake_sensor = 0;
			/* PLEASE CONTACT ME
			 * For FreeRTOS functions, I recommend sticking to the cmsis_os2.h implementations
			 * They abstracted the FreeRTOS functions to make them safer to use. All functions start with os
			 *
			 * https://www.freertos.org/FreeRTOS_Support_Forum_Archive/May_2008/freertos_vTaskPrioritySet_from_an_ISR._2030373.html
			 *
			 * These functions are not safe to use within interrupts, you will need to design a new function for this it work
			 * vTaskPrioritySet and osThreadSetPriority are both not designed to be used in ISR's
			 *
			 * It is considered dangerous to modify tasks within ISR's, preferably use semaphores or task notifications for synchronisation
			 * https://www.freertos.org/taskresumefromisr.html?_ga=2.123565195.1898795614.1718930664-902068592.1706319440
			 *
			 */
			//vTaskPrioritySet(xTask, uxNewPriority)
			//osThreadSetPriority(motorTaskHandle, osPriorityHigh7);
		}
		else
		{
			brake_sensor = 1;
			//osThreadSetPriority(motorTaskHandle, osPriorityIdle); // I'm not sure what the logic behind this is, please contact me
		}
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  throttle_data = sensor_buffer[0];
  brake_data = sensor_buffer[1];
  if(adc_retrieval == THROTTLE)
  {
	  osMessageQueuePut(adcQueueHandle, &throttle_data, 0, 0);
  }
  else if (adc_retrieval == BRAKE)
  {
	  osMessageQueuePut(adcQueueHandle, &brake_data, 0, 0);
  }
}

void motorTask_init()
{
	float prevDuty;
	float currentDuty = 0;
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)sensor_buffer, 2);
	uint16_t temp;
}

void motorTask_poll()
{
	// This is the first method of transmiting CAN messages
//	prevDuty = currentDuty;
//	currentDuty = map(throttle_data, 20, 4096, 0, 1);

	sprintf(uart_tx, "throttle: ");
	HAL_UART_Transmit(&huart3, (uint8_t*)uart_tx, 10, HAL_MAX_DELAY);

	sprintf(uart_tx, "%u", throttle_data);
	HAL_UART_Transmit(&huart3, (uint8_t*)uart_tx, sizeof(uart_tx), HAL_MAX_DELAY);

	sprintf(uart_tx, "brake: ");
	HAL_UART_Transmit(&huart3, (uint8_t*)uart_tx, 7, HAL_MAX_DELAY);

	sprintf(uart_tx, "%u\r\n", brake_data);
	HAL_UART_Transmit(&huart3, (uint8_t*)uart_tx, sizeof(uart_tx), HAL_MAX_DELAY);

//	handle_throttle(prevDuty, &currentDuty, throttle_threshold); // handle throttle is not designed to work like this (see comments in motor.c)
//	temp = (uint16_t) (100 * currentDuty);
//
//	sprintf(uart_tx, "%u\r\n", temp);
//	HAL_UART_Transmit(&huart3, (uint8_t*)uart_tx, sizeof(uart_tx), HAL_MAX_DELAY);
//	if (brakeActive == 1)
//	{
//		comm_can_set_duty(MOTOR_CAN_ID, 0.1);
//	}
//
//
//	duty_cycle = throttle_map(filtered_throttle, throttle_min, throttle_max, 0, 100);




	//This is the second method of transmitting CAN Messages
	// This is for digital brake regen braking, it is disabled by default
	if(brake_sensor)
	{
		// Activate regenerative breaking to slow the bike down to the appropriate speed
		handle_digital_brake(osKernelGetSysTimerCount(), &brake_magnitude);
		comm_can_set_current_brake_rel(MOTOR_CAN_ID, 1);
	}
	else
	{
		// ensure the sensor value is reasonable to send to the motor
		handle_throttle(throttle_data, &filtered_throttle, &acceleration);
		duty_cycle = map(filtered_throttle, throttle_min, throttle_max, 0, 100);

		sprintf(uart_tx, "%ld\r\n", duty_cycle);
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
}
