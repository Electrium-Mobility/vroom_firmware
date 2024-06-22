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

// Private Variables
MotorData motorDataStruct;
CAN_RxHeaderTypeDef rx_header;
uint8_t rx_data[8];

extern CAN_HandleTypeDef hcan2;

void diagnosticsTask_init()
{

}

void diagnosticsTask_poll()
{
	//CAN receive decoding - may be moved to lower priority task if needed
	if(HAL_CAN_GetRxFifoFillLevel(&hcan2, CAN_RX_FIFO0))
	{
		HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &rx_header, rx_data);
		can_packet_read(&rx_header, rx_data, &motorDataStruct);
//		sprintf(uart_tx, "%u%u%u%u", rx_data[0], rx_data[1], rx_data[2], rx_data[3]);
//		HAL_UART_Transmit(&huart3, (uint8_t*)uart_tx, rx_header.DLC, HAL_MAX_DELAY);
	}
}
