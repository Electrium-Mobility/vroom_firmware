/*
 * definitions.h
 *
 *  Created on: Aug 7, 2024
 *      Author: Victor Kalenda
 */

#ifndef APPLICATION_USER_CUSTOM_LAYERS_DEFINITIONS_H_
#define APPLICATION_USER_CUSTOM_LAYERS_DEFINITIONS_H_

// GUI constants

// Startup screen defines
//Startup will actually take twice this amount of ticks for idle animation and motorcycle animation
#define STARTUP_ANIMATION_DURATION 100

// User screen defines
#define KEYBOARD_ANIMATION_DURATION 20

#define FADE_ANIMATION_DURATION 40

// Main screen defines
#define NB_FUNCTIONS 10
#define TRANSITION_ANIMATION_DURATION 10
#define CALIBRATION_ANIMATION_DURATION 30

#define KEYPAD_ANIMATION_DURATION 40
#define KEYPAD_SET_ANIMATION_DURATION 100

#define LIST_ANIMATION_DURATION 40
#define LIST_SET_ANIMATION_DURATION 100

// ADC Retrieval enumeration
enum
{
	THROTTLE,
	BRAKE,
};

// User Data
#define MAX_NUM_USERS 12
#define USERNAME_SIZE 16
#define PASSWORD_SIZE 16
#define MIN_BUFFER_SIZE 16

// Emulated EEPROM Structure
typedef struct
{
	float motor_frequency;
	float diagnostic_frequency;
	uint16_t throttle_threshold;
	uint16_t throttle_max;
	uint16_t throttle_min;

	uint16_t brake_threshold;
	uint16_t brake_max;
	uint16_t brake_min;
	uint8_t analog_brake_active;
	float brake_rate;

	uint8_t num_users;
	uint8_t usernames[USERNAME_SIZE * MAX_NUM_USERS];
	uint8_t passwords[PASSWORD_SIZE * MAX_NUM_USERS];
}ee_Storage_t;

// CAN commands extracted from comm_can.c, comm_can.h, datatypes.h on vesc firmware github
typedef enum
{
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

typedef struct
{
	// CAN_PACKET_STATUS
	uint32_t erpm;
	uint16_t current;
	uint16_t duty_cycle;
	// CAN_PACKET_STATUS_2
	uint32_t amp_hours;
	uint32_t amp_hours_charged;
	// CAN_PACKET_STATUS_3
	uint32_t watt_hours;
	uint32_t watt_hours_charged;
	// CAN_PACKET_STATUS_4
	uint16_t fet_temperature;
	uint16_t motor_temperature;
	uint16_t current_in;
	uint16_t pid_position;
	// CAN_PACKET_STATUS_5
	uint32_t tachometer;
	uint16_t voltage_in;

	// CAN_PACKET_STATUS_6
	uint16_t adc_1;
	uint16_t adc_2;
	uint16_t adc_3;
	uint16_t ppm;
} motor_data_t;

#endif /* APPLICATION_USER_CUSTOM_LAYERS_DEFINITIONS_H_ */
