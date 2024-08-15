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
#define NB_FUNCTIONS 9
#define TRANSITION_ANIMATION_DURATION 10
#define CALIBRATION_ANIMATION_DURATION 10

#define KEYPAD_ANIMATION_DURATION 40
#define KEYPAD_SET_ANIMATION_DURATION 100

#define LIST_ANIMATION_DURATION 40
#define LIST_SET_ANIMATION_DURATION 100

// ADC Retrieval enumeration
typedef enum
{
	NO_RETRIEVAL,
	THROTTLE,
	BRAKE
}adcRetrievalState;

// User Data
#define MAX_NUM_USERS 12
#define USERNAME_SIZE 16
#define PASSWORD_SIZE 16
#define MIN_BUFFER_SIZE 16

// Emulated EEPROM Structure
typedef struct
{
	uint8_t num_users;

	uint8_t usernames[USERNAME_SIZE * MAX_NUM_USERS];
	uint8_t passwords[PASSWORD_SIZE * MAX_NUM_USERS];
}ee_Storage_t;



#endif /* APPLICATION_USER_CUSTOM_LAYERS_DEFINITIONS_H_ */
