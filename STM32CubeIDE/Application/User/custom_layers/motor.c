/*
 * motor.c
 *
 *  Created on: Jan 9, 2024
 *      Author: Victor Kalenda
 *
 *
 *      Sources:
 *      CAN Protocol Commands - https://github.com/vedderb/bldc/blob/master/comm/comm_can.c
 *     	CAN Implementation - https://github.com/vedderb/bldc/blob/master/documentation/comm_can.md
 */

#include <stdint.h>
#include "motor.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gui/common/definitions.h>


extern CAN_HandleTypeDef hcan2;
extern CAN_TxHeaderTypeDef tx_header;
extern uint32_t tx_mailbox;
extern UART_HandleTypeDef huart3;

char uart_tx_2[64];

// Implementation for sending extended ID CAN-frames
void can_transmit_eid(uint32_t id, uint8_t *data, uint8_t len)
{
	tx_header.IDE = CAN_ID_EXT;
	tx_header.ExtId = id;
	tx_header.RTR = CAN_RTR_DATA;
	tx_header.DLC = len;
	sprintf(uart_tx_2, "Sending CAN \r\n");
	HAL_UART_Transmit(&huart3, (uint8_t*)uart_tx_2, strlen(uart_tx_2) , HAL_MAX_DELAY);
	HAL_CAN_AddTxMessage(&hcan2, &tx_header, data, &tx_mailbox);
}

void can_packet_read(CAN_RxHeaderTypeDef *rx_header, uint8_t *data, motor_data_t *motor_data)
{
	uint8_t cmdID = (rx_header->ExtId>>8) & 0xff;							//get VESC command ID
	switch (cmdID)
	{
		case CAN_PACKET_STATUS:
		{
			motor_data->erpm = 		 (uint32_t)((data[0] << 24) + (data[1] << 16) + (data[2] << 8) + data[3]);
			motor_data->current = 	 (uint16_t)((data[0] << 8) + data[1]);
			motor_data->duty_cycle = (uint16_t)((data[0] << 8) + data[1]);
			break;
		}
		case CAN_PACKET_STATUS_2:
		{
			motor_data->amp_hours = 		(uint32_t)((data[0] << 24) + (data[1] << 16) + (data[2] << 8) + data[3]);
			motor_data->amp_hours_charged = (uint32_t)((data[4] << 24) + (data[5] << 16) + (data[6] << 8) + data[7]);
			break;
		}
		case CAN_PACKET_STATUS_3:
		{
			motor_data->watt_hours = 		 (uint32_t)((data[0] << 24) + (data[1] << 16) + (data[2] << 8) + data[3]);
			motor_data->watt_hours_charged = (uint32_t)((data[4] << 24) + (data[5] << 16) + (data[6] << 8) + data[7]);
			break;
		}
		case CAN_PACKET_STATUS_4:
		{
			motor_data->fet_temperature = 	(uint16_t)((data[0] << 8) + data[1]);
			motor_data->motor_temperature = (uint16_t)((data[2] << 8) + data[3]);
			motor_data->current_in = 		(uint16_t)((data[4] << 8) + data[5]);
			motor_data->pid_position = 		(uint16_t)((data[6] << 8) + data[7]);
			break;
		}
		case CAN_PACKET_STATUS_5:
		{
			motor_data->tachometer = (uint32_t)((data[0] << 24) + (data[1] << 16) + (data[2] << 8) + data[3]);
			motor_data->voltage_in = (uint16_t)((data[4] << 8) + data[5]);
			break;
		}
		case CAN_PACKET_STATUS_6:
		{
			motor_data->adc_1 = (uint16_t)((data[0] << 8) + data[1]);
			motor_data->adc_2 = (uint16_t)((data[2] << 8) + data[3]);
			motor_data->adc_3 = (uint16_t)((data[4] << 8) + data[5]);
			motor_data->ppm = 	(uint16_t)((data[6] << 8) + data[7]);
			break;
		}
		default:
		{
			break;
		}
	}
}


void buffer_append_int16(uint8_t* buffer, int16_t number, int32_t *index)
{
	buffer[(*index)++] = number >> 8;
	buffer[(*index)++] = number;
}

void buffer_append_int32(uint8_t* buffer, int32_t number, int32_t *index)
{
	buffer[(*index)++] = number >> 24;
	buffer[(*index)++] = number >> 16;
	buffer[(*index)++] = number >> 8;
	buffer[(*index)++] = number;
}

void buffer_append_float16(uint8_t* buffer, float number, float scale, int32_t *index)
{
    buffer_append_int16(buffer, (int16_t)(number * scale), index);
}

void buffer_append_float32(uint8_t* buffer, float number, float scale, int32_t *index)
{
    buffer_append_int32(buffer, (int32_t)(number * scale), index);
}

void comm_can_set_duty(uint8_t controller_id, float duty)
{
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)(duty * 100000.0), &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_DUTY << 8), buffer, send_index);
}

void comm_can_set_current(uint8_t controller_id, float current) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)(current * 1000.0), &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT << 8), buffer, send_index);
}

void comm_can_set_current_off_delay(uint8_t controller_id, float current, float off_delay) {
	int32_t send_index = 0;
	uint8_t buffer[6];
	buffer_append_int32(buffer, (int32_t)(current * 1000.0), &send_index);
	buffer_append_float16(buffer, off_delay, 1e3, &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT << 8), buffer, send_index);
}

void comm_can_set_current_brake(uint8_t controller_id, float current) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)(current * 1000.0), &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT_BRAKE << 8), buffer, send_index);
}

void comm_can_set_rpm(uint8_t controller_id, float rpm) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)rpm, &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_RPM << 8), buffer, send_index);
}

void comm_can_set_pos(uint8_t controller_id, float pos) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)(pos * 1000000.0), &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_POS << 8), buffer, send_index);
}

void comm_can_set_current_rel(uint8_t controller_id, float current_rel) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_float32(buffer, current_rel, 1e5, &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT_REL << 8), buffer, send_index);
}

void comm_can_set_current_rel_off_delay(uint8_t controller_id, float current_rel, float off_delay) {
	int32_t send_index = 0;
	uint8_t buffer[6];
	buffer_append_float32(buffer, current_rel, 1e5, &send_index);
	buffer_append_float16(buffer, off_delay, 1e3, &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT_REL << 8), buffer, send_index);
}

void comm_can_set_current_brake_rel(uint8_t controller_id, float current_rel) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_float32(buffer, current_rel, 1e5, &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT_BRAKE_REL << 8), buffer, send_index);
}

void comm_can_set_handbrake(uint8_t controller_id, float current) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_float32(buffer, current, 1e3, &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT_HANDBRAKE << 8), buffer, send_index);
}

void comm_can_set_handbrake_rel(uint8_t controller_id, float current_rel) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_float32(buffer, current_rel, 1e5, &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT_HANDBRAKE_REL << 8), buffer, send_index);
}


/*
 *
 * Parameter Setting Functions
 *
 */

void comm_can_conf_current_limits(uint8_t controller_id, uint8_t store, float min, float max)
{
	int32_t send_index = 0;
	uint8_t buffer[8];
	buffer_append_float32(buffer, min, 1e3, &send_index);
	buffer_append_float32(buffer, max, 1e3, &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)(store ? CAN_PACKET_CONF_STORE_CURRENT_LIMITS :
					CAN_PACKET_CONF_CURRENT_LIMITS) << 8), buffer, send_index);
}

void comm_can_conf_current_limits_in(uint8_t controller_id, uint8_t store, float min, float max)
{
	int32_t send_index = 0;
	uint8_t buffer[8];
	buffer_append_float32(buffer, min, 1e3, &send_index);
	buffer_append_float32(buffer, max, 1e3, &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)(store ? CAN_PACKET_CONF_STORE_CURRENT_LIMITS_IN :
					CAN_PACKET_CONF_CURRENT_LIMITS_IN) << 8), buffer, send_index);
}

void comm_can_conf_foc_erpms(uint8_t controller_id, uint8_t store, float foc_openloop_rpm, float foc_sl_erpm)
{
	int32_t send_index = 0;
	uint8_t buffer[8];
	buffer_append_float32(buffer, foc_openloop_rpm, 1e3, &send_index);
	buffer_append_float32(buffer, foc_sl_erpm, 1e3, &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)(store ? CAN_PACKET_CONF_STORE_FOC_ERPMS :
					CAN_PACKET_CONF_FOC_ERPMS) << 8), buffer, send_index);
}

void comm_can_detect_apply_all_foc(uint8_t controller_id, uint8_t activate_status_msgs, float max_power_loss)
{
	int32_t send_index = 0;
	uint8_t buffer[6];
	buffer[send_index++] = 0; //host controller_id (may be required)
	buffer[send_index++] = activate_status_msgs;
	buffer_append_float32(buffer, max_power_loss, 1e3, &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_DETECT_APPLY_ALL_FOC << 8), buffer, send_index);
}

void comm_can_conf_battery_cut(uint8_t controller_id, uint8_t store, float start, float end)
{
	int32_t send_index = 0;
	uint8_t buffer[8];
	buffer_append_float32(buffer, start, 1e3, &send_index);
	buffer_append_float32(buffer, end, 1e3, &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)(store ? CAN_PACKET_CONF_STORE_BATTERY_CUT :
					CAN_PACKET_CONF_BATTERY_CUT) << 8), buffer, send_index);
}

void comm_can_update_pid_pos_offset(int controller_id, float angle_now, uint8_t store)
{
	int32_t send_index = 0;
	uint8_t buffer[8];

	buffer_append_float32(buffer, angle_now, 1e4, &send_index);
	buffer[send_index++] = store;

	can_transmit_eid(controller_id | ((uint32_t)CAN_PACKET_UPDATE_PID_POS_OFFSET << 8),
			buffer, send_index);
}

void comm_can_shutdown(uint8_t controller_id)
{
	int32_t send_index = 0;
	uint8_t buffer[8];
	can_transmit_eid(controller_id |
			((uint32_t)(CAN_PACKET_SHUTDOWN) << 8), buffer, send_index);
}


/*
 *
 * Functions for Testing CAN Protocol
 *
 */

uint8_t comm_can_ping(uint8_t controller_id)
{
	uint8_t buffer[1];
	buffer[0] = 0; //host controller ID (may be required)
	can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_PING << 8), buffer, 1);

	// wait for a response, We must implement
	return 0;
}





// Sensor Filtering Algorithm
/*
 * filter_sensor_data
 *
 * Filters the sensor data so that it does not increase or decrease faster than a given threshold specified by threshold
 *
 * sensor_data is passed by value since it should not be used after the function is executed
 * filtered_data and acceleration are passed by reference so that we can access both their outputs after the function is executed
 */
void filter_sensor_data(uint32_t sensor_data, uint32_t *filtered_data, int32_t *acceleration, uint16_t threshold)
{
	(*acceleration) = (uint32_t)(sensor_data - (*filtered_data)); // change in sensor_data / time

	sprintf(uart_tx_2, "%d, ", abs(*acceleration));
	HAL_UART_Transmit(&huart3, (uint8_t*)uart_tx_2, strlen(uart_tx_2), HAL_MAX_DELAY); //actual sensor analog value (0 to 4096)

	// Check if the change of throttle data is very fast (exceeds the threshold)
	if (abs(*acceleration) > threshold)
	{
		// limit the smoothed_value from changing faster than the threshold
		if((*acceleration) > 0)
		{
			(*filtered_data) += threshold;
		}
		else
		{
			(*filtered_data) -= threshold;
		}
	}
	else
	{
		(*filtered_data) = sensor_data;
	}
	//print current values that is compatible with serial plotter
	sprintf(uart_tx_2, "%ld, ", sensor_data);
	HAL_UART_Transmit(&huart3, (uint8_t*)uart_tx_2, strlen(uart_tx_2), HAL_MAX_DELAY); //actual sensor analog value (0 to 4096)
	sprintf(uart_tx_2, "%ld, ", (*filtered_data));
	HAL_UART_Transmit(&huart3, (uint8_t*)uart_tx_2, strlen(uart_tx_2), HAL_MAX_DELAY);
}

void handle_digital_brake(uint32_t t, float *brake_magnitude)
{

}

int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

