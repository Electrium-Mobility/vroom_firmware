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
#include "ee.h"

// Public Variables
motor_data_t motor_data;

// Private Variables
CAN_RxHeaderTypeDef rx_header;
uint8_t rx_data[8];

extern CAN_HandleTypeDef hcan2;

extern osSemaphoreId_t collect_diagnostic_dataHandle;

extern osSemaphoreId_t suspend_diagnostics_taskHandle;

extern osSemaphoreId_t diagnostic_timing_modifiedHandle;

extern osThreadId_t diagnosticsTaskHandle;

extern osMutexId_t settingMutexHandle;

extern ee_Storage_t ee;

uint32_t diagnostic_delay = 0;


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
	if(osSemaphoreGetCount(diagnostic_timing_modifiedHandle))
	{
		// the refresh rate has been changed
		if(osMutexAcquire(settingMutexHandle, osWaitForever) == osOK)
		{
			// Safety Check, ensure that an invalid value doesn't result in no diagnostic_delay
			if(ee.diagnostic_frequency < 0 || ee.diagnostic_frequency > 1000)
			{
				ee.diagnostic_frequency = 1.0;

				// Setup the diagnostic_delay variable regardless of EE is written properly
				diagnostic_delay = (uint32_t) (1000 / ee.diagnostic_frequency);

				if(EE_Write())
				{
					// Only change the state of the timing semaphore if the refresh rate
					// was successfully written to EE, otherwise make the task retry
					osSemaphoreAcquire(diagnostic_timing_modifiedHandle, 0);
				}
				else
				{
					// Ensure the next iteration will attempt the EE_Write operation again
					ee.diagnostic_frequency = 0;
				}
			}
			else
			{
				diagnostic_delay = (uint32_t)(1000 / ee.diagnostic_frequency);

				osSemaphoreAcquire(diagnostic_timing_modifiedHandle, 0);
			}
			osMutexRelease(settingMutexHandle);
		}
	}
	osDelayUntil(osKernelGetTickCount() + (diagnostic_delay / portTICK_PERIOD_MS));
}

void handle_diagnostics_task_suspension()
{
	if(osSemaphoreGetCount(suspend_diagnostics_taskHandle))
	{
		osThreadSuspend(diagnosticsTaskHandle);
	}
}
