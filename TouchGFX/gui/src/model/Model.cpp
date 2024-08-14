#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <gui/common/definitions.h>

#ifndef SIMULATOR

extern "C"
{
#include "motor.h"
#include "main.h"
#include "cmsis_os.h"
#include "ee.h"

// Queues
extern osMessageQueueId_t adcQueueHandle;

// Mutexes
extern osMutexId_t settingMutexHandle;

extern float motor_frequency;

// ADC's
extern ADC_HandleTypeDef hadc1; // (may remove this if it is unnecessary)
extern adcRetrievalState adc_retrieval; // no need to aquire a mutex as this will only be set by the TouchGFX Task

// Throttle Sensor Varaibles
extern uint16_t throttle_threshold;
extern uint16_t throttle_max;
extern uint16_t throttle_min;
extern volatile uint16_t throttle_data;

// Brake Sensor Variables
extern uint16_t brake_threshold;
extern uint16_t brake_max;
extern uint16_t brake_min;
extern volatile uint16_t brake_data;

// Emulated EEPROM Data
extern ee_Storage_t ee;
}

#endif // SIMULATOR

Model::Model() :
		modelListener(0),
		adc_value(0),
		user_screen_state(LOGIN)
{

}

void Model::tick()
{
#ifndef SIMULATOR
	if (adc_retrieval != NO_RETRIEVAL)
	{
		// Retrieve the ADC value from the queue, can be from the throttle or the brake, but not both
		if (osMessageQueueGetCount(adcQueueHandle) > 0)
		{
			if (osMessageQueueGet(adcQueueHandle, &adc_value, 0, 0) == osOK)
			{
				modelListener->display_adc(adc_value);
			}
		}
	}
#endif // SIMULATOR
}

void Model::set_throttle_high_point()
{
#ifndef SIMULATOR
	if (osMutexAcquire(settingMutexHandle, 10) == osOK)
	{
//		HAL_ADC_Start(&hadc1);
//		HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
//		throttle_max = HAL_ADC_GetValue(&hadc1);
//		HAL_ADC_Stop(&hadc1);
		// Not sure if this will work
		throttle_max = throttle_data;
		// throttle_max = adc_value; // may also work
		osMutexRelease(settingMutexHandle);
	}
#endif
}

void Model::set_throttle_low_point()
{
#ifndef SIMULATOR
	if (osMutexAcquire(settingMutexHandle, 10) == osOK)
	{
//		HAL_ADC_Start(&hadc1);
//		HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
//		throttle_min = HAL_ADC_GetValue(&hadc1);
//		HAL_ADC_Stop(&hadc1);
		// Not sure if this will work
		throttle_min = throttle_data;
		// throttle_min = adc_value; // may also work
		osMutexRelease(settingMutexHandle);
	}
#endif
}

void Model::set_brake_high_point()
{
#ifndef SIMULATOR
	if (osMutexAcquire(settingMutexHandle, 10) == osOK)
	{
		//HAL_ADC_Start(&hadc2);
		//HAL_ADC_PollForConversion(&hadc2, HAL_MAX_DELAY);
		//brake_max = HAL_ADC_GetValue(&hadc2);
		//HAL_ADC_Stop(&hadc2);
		// Not sure if this will work
		brake_max = brake_data;
		// brake_max = adc_value; // may also work
		osMutexRelease(settingMutexHandle);
	}
#endif
}

void Model::set_brake_low_point()
{
#ifndef SIMULATOR
	if (osMutexAcquire(settingMutexHandle, 10) == osOK)
	{
		//HAL_ADC_Start(&hadc2);
		//HAL_ADC_PollForConversion(&hadc2, HAL_MAX_DELAY);
		//brake_min = HAL_ADC_GetValue(&hadc2);
		//HAL_ADC_Stop(&hadc2);
		// Not sure if this will work
		brake_min = brake_data;
		// brake_min = adc_value; // may also work
		osMutexRelease(settingMutexHandle);
	}
#endif
}

uint32_t Model::get_throttle_sensitivity()
{
	unsigned int temp = 100;
#ifndef SIMULATOR
	// Aquire Mutex
	if (osMutexAcquire(settingMutexHandle, 10) == osOK)
	{
		temp = throttle_threshold;
		// Release Mutex
		osMutexRelease(settingMutexHandle);
	}
#endif // SIMULATOR
	return temp;
}

void Model::set_throttle_sensitivity(uint32_t throttle_value)
{
#ifndef SIMULATOR
	// Aquire Mutex
	if (osMutexAcquire(settingMutexHandle, 10) == osOK)
	{
		throttle_threshold = throttle_value;
		// Release Mutex
		osMutexRelease(settingMutexHandle);
	}
#endif // SIMULATOR
}

uint32_t Model::get_brake_sensitivity()
{
	unsigned int temp = 100;
#ifndef SIMULATOR
	// Aquire Mutex
	if (osMutexAcquire(settingMutexHandle, 10) == osOK)
	{
		temp = brake_threshold;
		// Release Mutex
		osMutexRelease(settingMutexHandle);
	}
#endif // SIMULATOR
	return temp;
}

void Model::set_brake_sensitivity(uint32_t brake_value)
{
#ifndef SIMULATOR
	// Aquire Mutex
	if (osMutexAcquire(settingMutexHandle, 10) == osOK)
	{
		brake_threshold = brake_value;
		// Release Mutex
		osMutexRelease(settingMutexHandle);
	}
#endif // SIMULATOR
}

float Model::get_CAN_transmit_frequency()
{
	unsigned int temp = 1000;
#ifndef SIMULATOR
	// Aquire Mutex
	if (osMutexAcquire(settingMutexHandle, 10) == osOK)
	{
		temp = motor_frequency;
		// Release Mutex
		osMutexRelease(settingMutexHandle);
	}
#endif // SIMULATOR

	// Return frequency in Hz
	return temp;
}

void Model::set_CAN_transmit_frequency(float frequency_value)
{
#ifndef SIMULATOR
	// Aquire Mutex
	if (osMutexAcquire(settingMutexHandle, 10) == osOK)
	{
		motor_frequency = frequency_value;
		// Release Mutex
		osMutexRelease(settingMutexHandle);
	}
#endif // SIMULATOR
}

void Model::start_throttle_adc()
{
#ifndef SIMULATOR
	// Aquire Mutex
	if (osMutexAcquire(settingMutexHandle, 10) == osOK)
	{
		adc_retrieval = THROTTLE;
		// Release Mutex
		osMutexRelease(settingMutexHandle);
	}

#endif
}

void Model::start_brake_adc()
{
#ifndef SIMULATOR
	// Aquire Mutex
	if (osMutexAcquire(settingMutexHandle, 10) == osOK)
	{
		adc_retrieval = BRAKE;
		// Release Mutex
		osMutexRelease(settingMutexHandle);
	}
#endif
}

void Model::stop_adc_retrieval()
{
#ifndef SIMULATOR
	// Aquire Mutex
	if (osMutexAcquire(settingMutexHandle, 10) == osOK)
	{
		// display_throttle_adc = false;
		// display_brake_adc = false;
		adc_retrieval = NO_RETRIEVAL;
		// Release Mutex
		osMutexRelease(settingMutexHandle);
	}
#endif
}




void Model::get_username(int8_t user, uint8_t* username, uint8_t size)
{
#ifndef SIMULATOR
	for(uint8_t i = 0; i < size; i++)
	{
		username[i] = ee.usernames[(user * USERNAME_SIZE) + i];
	}
#else
	if(user == 0)
	{
		username[0] = 'A';
		username[1] = 'd';
		username[2] = 'm';
		username[3] = 'i';
		username[4] = 'n';
	}
#endif
}

void Model::get_password(int8_t user, uint8_t* password, uint8_t size)
{
#ifndef SIMULATOR
	for(uint8_t i = 0; i < size; i++)
	{
		password[i] = ee.passwords[(user * PASSWORD_SIZE) + i];
	}
#else
	if(user == 0)
	{
		password[0] = 'V';
		password[1] = 'r';
		password[2] = 'o';
		password[3] = 'o';
		password[4] = 'm';
		password[5] = '2';
		password[6] = '0';
		password[7] = '2';
		password[8] = '4';
		password[9] = '!';
	}
#endif
}

uint8_t Model::get_num_users()
{
#ifndef SIMULATOR
	return ee.num_users;
#else
	return 1;
#endif
}

void Model::edit_username(uint8_t user, uint8_t* username)
{
#ifndef SIMULATOR
	for(uint8_t i = 0; i < USERNAME_SIZE; i++)
	{
		ee.usernames[(user * USERNAME_SIZE) + i] = username[i];
	}
	EE_Write();
#endif
}

void Model::edit_password(uint8_t user, uint8_t* password)
{
#ifndef SIMULATOR
	for(uint8_t i = 0; i < PASSWORD_SIZE; i++)
	{
		ee.passwords[(user * PASSWORD_SIZE) + i] = password[i];
	}
	EE_Write();
#endif
}

void Model::add_user(uint8_t* username, uint8_t* password)
{
#ifndef SIMULATOR
	for(uint8_t i = 0; i < USERNAME_SIZE; i++)
	{
		ee.usernames[(ee.num_users * USERNAME_SIZE) * i] = username[i];
	}
	for(uint8_t i = 0; i < PASSWORD_SIZE; i++)
	{
		ee.passwords[(ee.num_users * PASSWORD_SIZE) + i] = password[i];
	}
	ee.num_users++;
	EE_Write();
#endif
}

void Model::remove_user(uint8_t user)
{
#ifndef SIMULATOR
	for(uint8_t i = 0; i < USERNAME_SIZE; i++)
	{
		ee.usernames[(user * USERNAME_SIZE) + i] = 0;
	}
	for(uint8_t i = 0; i < PASSWORD_SIZE; i++)
	{
		ee.passwords[(user * PASSWORD_SIZE) + i] = 0;
	}
	ee.num_users--;
	EE_Write();
#endif
}

Model::UserScreenState Model::get_user_screen_state()
{
	return user_screen_state;
}

void Model::set_user_screen_state(Model::UserScreenState state)
{
	user_screen_state = state;
}

