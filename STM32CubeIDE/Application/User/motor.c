/*
 * motor.c
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

// CAN commands extracted from comm_can.c, comm_can.h, datatypes.h on vesc firmware github
typedef enum {
	CAN_PACKET_SET_DUTY						= 0,
	CAN_PACKET_SET_CURRENT					= 1,
	CAN_PACKET_SET_CURRENT_BRAKE			= 2,
	CAN_PACKET_SET_RPM						= 3,
	CAN_PACKET_SET_POS						= 4,
	//CAN_PACKET_FILL_RX_BUFFER					= 5, for advanced commands
	//CAN_PACKET_FILL_RX_BUFFER_LONG			= 6, for advanced commands
	//CAN_PACKET_PROCESS_RX_BUFFER				= 7, for motor controllers
	//CAN_PACKET_PROCESS_SHORT_BUFFER			= 8, for motor controllers
	CAN_PACKET_STATUS						= 9,
	CAN_PACKET_SET_CURRENT_REL				= 10,
	CAN_PACKET_SET_CURRENT_BRAKE_REL		= 11,
	CAN_PACKET_SET_CURRENT_HANDBRAKE		= 12,
	CAN_PACKET_SET_CURRENT_HANDBRAKE_REL	= 13,
	CAN_PACKET_STATUS_2						= 14,
	CAN_PACKET_STATUS_3						= 15,
	CAN_PACKET_STATUS_4						= 16,
	CAN_PACKET_PING							= 17,
	CAN_PACKET_PONG							= 18,
	CAN_PACKET_DETECT_APPLY_ALL_FOC			= 19,
	CAN_PACKET_DETECT_APPLY_ALL_FOC_RES		= 20,
	CAN_PACKET_CONF_CURRENT_LIMITS			= 21,
	CAN_PACKET_CONF_STORE_CURRENT_LIMITS	= 22,
	CAN_PACKET_CONF_CURRENT_LIMITS_IN		= 23,
	CAN_PACKET_CONF_STORE_CURRENT_LIMITS_IN	= 24,
	CAN_PACKET_CONF_FOC_ERPMS				= 25,
	CAN_PACKET_CONF_STORE_FOC_ERPMS			= 26,
	CAN_PACKET_STATUS_5						= 27,
	//CAN_PACKET_POLL_TS5700N8501_STATUS		= 28, not sure what this is
	CAN_PACKET_CONF_BATTERY_CUT				= 29,
	CAN_PACKET_CONF_STORE_BATTERY_CUT		= 30,
	CAN_PACKET_SHUTDOWN						= 31,
	//CAN_PACKET_IO_BOARD_ADC_1_TO_4			= 32, not sure if it's relevant
	//CAN_PACKET_IO_BOARD_ADC_5_TO_8			= 33, not sure if it's relevant
	//CAN_PACKET_IO_BOARD_ADC_9_TO_12			= 34, not sure if it's relevant
	//CAN_PACKET_IO_BOARD_DIGITAL_IN			= 35, not sure if it's relevant
	//CAN_PACKET_IO_BOARD_SET_OUTPUT_DIGITAL	= 36, not sure if it's relevant
	//CAN_PACKET_IO_BOARD_SET_OUTPUT_PWM		= 37, not sure if it's relevant
	//CAN_PACKET_BMS_V_TOT						= 38,
	//CAN_PACKET_BMS_I							= 39,
	//CAN_PACKET_BMS_AH_WH						= 40,
	//CAN_PACKET_BMS_V_CELL						= 41,
	//CAN_PACKET_BMS_BAL						= 42,
	//CAN_PACKET_BMS_TEMPS						= 43,
	//CAN_PACKET_BMS_HUM						= 44,
	//CAN_PACKET_BMS_SOC_SOH_TEMP_STAT			= 45,
	//CAN_PACKET_PSW_STAT						= 46, not sure what psw means
	//CAN_PACKET_PSW_SWITCH						= 47, not sure what psw means
	//CAN_PACKET_BMS_HW_DATA_1					= 48,
	//CAN_PACKET_BMS_HW_DATA_2					= 49,
	//CAN_PACKET_BMS_HW_DATA_3					= 50,
	//CAN_PACKET_BMS_HW_DATA_4					= 51,
	//CAN_PACKET_BMS_HW_DATA_5					= 52,
	//CAN_PACKET_BMS_AH_WH_CHG_TOTAL			= 53,
	//CAN_PACKET_BMS_AH_WH_DIS_TOTAL			= 54,
	CAN_PACKET_UPDATE_PID_POS_OFFSET		= 55,
	//CAN_PACKET_POLL_ROTOR_POS					= 56, not sure if it's relevant
	//CAN_PACKET_NOTIFY_BOOT					= 57, for motor controllers
	CAN_PACKET_STATUS_6						= 58,
	//CAN_PACKET_GNSS_TIME						= 59, not sure if it's relevant
	//CAN_PACKET_GNSS_LAT						= 60, not sure if it's relevant
	//CAN_PACKET_GNSS_LON						= 61, not sure if it's relevant
	//CAN_PACKET_GNSS_ALT_SPEED_HDOP			= 62, not sure if it's relevant
	CAN_PACKET_MAKE_ENUM_32_BITS = 0xFFFFFFFF,
} CAN_PACKET_ID;

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





// Throttle Filtering Algorithm

extern uint16_t threshold; // Variable for max sensitivity difference in analog values
uint16_t previous_value = 0; // Variable to store the previous analog value

void handle_throttle(uint32_t sensor_data, uint32_t *filtered_data, int32_t *acceleration)
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

void handle_brake(uint16_t t, float *brake_magnitude)
{
}

int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

