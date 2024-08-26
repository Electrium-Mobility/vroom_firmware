/*
 * diagnosticsTask.c
 *
 *  Created on: Jun 22, 2024
 *      Author: Victor Kalenda
 */

#include "diagnosticsTask.h"

#include "main.h"
#include "cmsis_os.h"
#include "motor.h"
#include <gui/common/definitions.h>

// Public Variables
motor_data_t motor_data;

// Private Variables
CAN_RxHeaderTypeDef rx_header;
uint8_t rx_data[8];

float diagnostic_frequency = 1; // the frequency of diagnostic test data acquisition in Hz

extern CAN_HandleTypeDef hcan2;

extern osSemaphoreId_t collect_diagnostic_dataHandle;

extern osSemaphoreId_t suspend_diagnostics_taskHandle;

extern osThreadId_t diagnosticsTaskHandle;

void handle_diagnostics_task_suspension();
void handle_diagnostics_timing();

void diagnosticsTask_init()
{

}

void diagnosticsTask_poll()
{
	handle_diagnostics_task_suspension();
	//CAN receive decoding - may be moved to lower priority task if needed
	if(osSemaphoreGetCount(collect_diagnostic_dataHandle))
	{
		if(HAL_CAN_GetRxFifoFillLevel(&hcan2, CAN_RX_FIFO0))
		{
			HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &rx_header, rx_data);
			can_packet_read(&rx_header, rx_data, &motor_data);
			osSemaphoreAcquire(collect_diagnostic_dataHandle, 10);

//			sprintf(uart_tx, "%u%u%u%u", rx_data[0], rx_data[1], rx_data[2], rx_data[3]);
//			HAL_UART_Transmit(&huart3, (uint8_t*)uart_tx, rx_header.DLC, HAL_MAX_DELAY);
		}
	}
	handle_diagnostics_timing();
}

void handle_diagnostics_timing()
{
	osDelayUntil(osKernelGetTickCount() + ((1000 / diagnostic_frequency) / portTICK_PERIOD_MS));
}

void handle_diagnostics_task_suspension()
{
	if(osSemaphoreGetCount(suspend_diagnostics_taskHandle))
	{
		osThreadSuspend(diagnosticsTaskHandle);
	}
}
