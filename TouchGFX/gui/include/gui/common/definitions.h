/*
 * definitions.h
 *
 *  Created on: Aug 7, 2024
 *      Author: Victor Kalenda
 */

#ifndef APPLICATION_USER_CUSTOM_LAYERS_DEFINITIONS_H_
#define APPLICATION_USER_CUSTOM_LAYERS_DEFINITIONS_H_

// GUI constants
//Startup will actually take twice this amount of ticks for idle animation and motorcycle animation
#define STARTUP_ANIMATION_DURATION 100

#define FADE_ANIMATION_DURATION 40

#define KEYBOARD_ANIMATION_DURATION 20
#define KEYPAD_ANIMATION_DURATION 40
#define KEYPAD_SET_ANIMATION_DURATION 100

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

// Emulated EEPROM Structure
typedef struct
{
	uint8_t num_users;

	char usernames[USERNAME_SIZE * MAX_NUM_USERS];
	char passwords[PASSWORD_SIZE * MAX_NUM_USERS];
}ee_Storage_t;



#endif /* APPLICATION_USER_CUSTOM_LAYERS_DEFINITIONS_H_ */
