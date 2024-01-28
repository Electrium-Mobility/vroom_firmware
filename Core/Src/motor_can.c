/*
 * motor_can.c
 *
 *  Created on: Jan 9, 2024
 *      Author: Victor Kalenda
 */

#include <stdint.h>
#include "motor.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * All CAN commands according to telemetry pdf, refer to comm_can.c on VESC github for all commands
CAN_PACKET_SET_DUTY = 0,
CAN_PACKET_SET_CURRENT = 1,
CAN_PACKET_SET_CURRENT_BRAKE = 2,
CAN_PACKET_SET_RPM = 3,
CAN_PACKET_SET_POS = 4,
CAN_PACKET_FILL_RX_BUFFER = 5,
CAN_PACKET_FILL_RX_BUFFER_LONG = 6,
CAN_PACKET_PROCESS_RX_BUFFER = 7,
CAN_PACKET_PROCESS_SHORT_BUFFER = 8,
CAN_PACKET_STATUS = 9,
CAN_PACKET_SET_CURRENT_REL = 10,
CAN_PACKET_SET_CURRENT_BRAKE_REL = 11,
CAN_PACKET_SET_CURRENT_HANDBRAKE = 12,
CAN_PACKET_SET_CURRENT_HANDBRAKE_REL = 13,
CAN_PACKET_STATUS_2 = 14,
CAN_PACKET_STATUS_3 = 15,
CAN_PACKET_STATUS_4 = 16,
CAN_PACKET_PING = 17,
CAN_PACKET_PONG = 18,
CAN_PACKET_DETECT_APPLY_ALL_FOC = 19,
CAN_PACKET_DETECT_APPLY_ALL_FOC_RES = 20,
CAN_PACKET_CONF_CURRENT_LIMITS = 21,
CAN_PACKET_CONF_STORE_CURRENT_LIMITS = 22,
CAN_PACKET_CONF_CURRENT_LIMITS_IN = 23,
CAN_PACKET_CONF_STORE_CURRENT_LIMITS_IN = 24,
CAN_PACKET_CONF_FOC_ERPMS = 25,
CAN_PACKET_CONF_STORE_FOC_ERPMS = 26,
CAN_PACKET_STATUS_5 = 27
*/
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

typedef enum
{
	CAN_PACKET_SET_DUTY = 0,
	CAN_PACKET_SET_CURRENT,
	CAN_PACKET_SET_CURRENT_BRAKE,
	CAN_PACKET_SET_RPM,
	CAN_PACKET_SET_POS,
	CAN_PACKET_SET_CURRENT_REL = 10,
	CAN_PACKET_SET_CURRENT_BRAKE_REL,
	CAN_PACKET_SET_CURRENT_HANDBRAKE,
	CAN_PACKET_SET_CURRENT_HANDBRAKE_REL,
	CAN_PACKET_MAKE_ENUM_32_BITS = 0xFFFFFFFF,
} CAN_PACKET_ID;

void buffer_append_int16(uint8_t* buffer, int16_t number, int32_t *index) {
	buffer[(*index)++] = number >> 8;
	buffer[(*index)++] = number;
}

void buffer_append_int32(uint8_t* buffer, int32_t number, int32_t *index) {
	buffer[(*index)++] = number >> 24;
	buffer[(*index)++] = number >> 16;
	buffer[(*index)++] = number >> 8;
	buffer[(*index)++] = number;
}

void buffer_append_float16(uint8_t* buffer, float number, float scale, int32_t *index) {
    buffer_append_int16(buffer, (int16_t)(number * scale), index);
}

void buffer_append_float32(uint8_t* buffer, float number, float scale, int32_t *index) {
    buffer_append_int32(buffer, (int32_t)(number * scale), index);
}

// Set the power going to the motors as a decimal percentage, range -1 to 1
void comm_can_set_duty(uint8_t controller_id, float duty) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)(duty * 100000.0), &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_DUTY << 8), buffer, send_index);
}

// Set the power going to the motors as amperage, range unknown (mA)
void comm_can_set_current(uint8_t controller_id, float current) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)(current * 1000.0), &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT << 8), buffer, send_index);
}

//
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

// Set the electrical RPM (ERPM) of the motor, range unknown
void comm_can_set_rpm(uint8_t controller_id, float rpm) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)rpm, &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_RPM << 8), buffer, send_index);
}

// Designed for Servo Motors, range 0 - 360
void comm_can_set_pos(uint8_t controller_id, float pos) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)(pos * 1000000.0), &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_POS << 8), buffer, send_index);
}

// Set current relative to minimum and maximum limits as a decimal percentage, range -1 to 1
void comm_can_set_current_rel(uint8_t controller_id, float current_rel) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_float32(buffer, current_rel, 1e5, &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT_REL << 8), buffer, send_index);
}

/**
 * Same as above, but also sets the off delay. Note that this command uses 6 bytes now. The off delay is useful to set to keep the current controller running for a while even after setting currents below the minimum current.
 */
void comm_can_set_current_rel_off_delay(uint8_t controller_id, float current_rel, float off_delay) {
	int32_t send_index = 0;
	uint8_t buffer[6];
	buffer_append_float32(buffer, current_rel, 1e5, &send_index);
	buffer_append_float16(buffer, off_delay, 1e3, &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT_REL << 8), buffer, send_index);
}

// Set braking current relative to minimum current limit as a decimal percentage, range 0 to 1
void comm_can_set_current_brake_rel(uint8_t controller_id, float current_rel) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_float32(buffer, current_rel, 1e5, &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT_BRAKE_REL << 8), buffer, send_index);
}

// Set handbrake as a percentage, 0 to 1
void comm_can_set_handbrake(uint8_t controller_id, float current) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_float32(buffer, current, 1e3, &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT_HANDBRAKE << 8), buffer, send_index);
}

// Set the handbrake relative to minimum current limit as a percentage, range 0 to 1
void comm_can_set_handbrake_rel(uint8_t controller_id, float current_rel) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_float32(buffer, current_rel, 1e5, &send_index);
	can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT_HANDBRAKE_REL << 8), buffer, send_index);
}


extern uint16_t threshold; // Variable for max sensitivity difference in analog values
uint16_t previous_value = 0; // Variable to store the previous analog value

void handle_throttle(uint32_t sensor_data, uint32_t *filtered_data, int32_t *acceleration)
{
	const float smoothingFactor = 0.175; //Variable for factor of smoothing of analog readings, if lower, filtering is more intense
	(*acceleration) = (uint32_t)(sensor_data - previous_value) / 100; // change in sensor_data / time
	int32_t change = abs(sensor_data - previous_value); // Calculate the absolute change in analog signal

	// Smoothen the analog value
	(*filtered_data) = (smoothingFactor * (float)sensor_data) + ((1 - smoothingFactor) * (float)(*filtered_data)); //EMA filtering formula

	// Check if the change of throttle data is very fast (exceeds the threshold)
	// TODO: Either we use the filtered_data or the raw change, we must choose
	if (abs((*filtered_data) - previous_value) > threshold)
	{
		// limit the smoothed_value from changing faster than the threshold
		if((*acceleration) > 0)
		{
			(*filtered_data) = previous_value + threshold;
		}
		else
		{
			(*filtered_data) = previous_value - threshold;
		}
	}
	//print current values that is compatible with serial plotter
	sprintf(uart_tx_2, "Raw : %ld\r\n", sensor_data);
	HAL_UART_Transmit(&huart3, (uint8_t*)uart_tx_2, strlen(uart_tx_2), HAL_MAX_DELAY); //actual sensor analog value (0 to 4096)
	sprintf(uart_tx_2, "Filtered : %ld\r\n", (*filtered_data));
	HAL_UART_Transmit(&huart3, (uint8_t*)uart_tx_2, strlen(uart_tx_2), HAL_MAX_DELAY);


	previous_value = sensor_data; // Update the previous value for the next iteration
	HAL_Delay(100); // Adjust the delay based on needs
}

