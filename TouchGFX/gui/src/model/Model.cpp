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

// Mutexes
extern osMutexId_t settingMutexHandle;

// Sensor Data
extern volatile uint16_t sensor_data[2];

// Diagnostics Variables
extern osSemaphoreId_t collect_diagnostic_dataHandle;
extern motor_data_t motor_data;

// Task Handling Variables
extern osSemaphoreId_t suspend_diagnostics_taskHandle;
extern osSemaphoreId_t suspend_motor_taskHandle;
extern osSemaphoreId_t diagnostic_timing_modifiedHandle;
extern osSemaphoreId_t motor_timing_modifiedHandle;

extern osThreadId_t diagnosticsTaskHandle;
extern osThreadId_t motorTaskHandle;

extern osSemaphoreId_t collect_adc_dataHandle;

// Emulated EEPROM Data
extern ee_Storage_t ee;
}

#endif // SIMULATOR

Model::Model() :
		modelListener(0),
		user_screen_state(LOGIN),
		retrieve_adc_data(false)
{}

void Model::tick()
{
#ifndef SIMULATOR
	if(retrieve_adc_data)
	{
		if(!osSemaphoreGetCount(collect_adc_dataHandle))
		{
			modelListener->display_adc(sensor_data);
			osSemaphoreRelease(collect_diagnostic_dataHandle);
		}
	}

	if(!osSemaphoreGetCount(collect_diagnostic_dataHandle))
	{
		modelListener->update_motor_data(&motor_data);
		osSemaphoreRelease(collect_diagnostic_dataHandle);
	}
#endif // SIMULATOR
}

void Model::resume_motor_task()
{
#ifndef SIMULATOR
	if(osSemaphoreGetCount(suspend_motor_taskHandle))
	{
		osSemaphoreAcquire(suspend_motor_taskHandle, 10);
		osThreadResume(motorTaskHandle);

	}
#endif
}

void Model::resume_diagnostics_task()
{
#ifndef SIMULATOR
	if(osSemaphoreGetCount(suspend_diagnostics_taskHandle))
	{
		osSemaphoreAcquire(suspend_diagnostics_taskHandle, 10);
		osThreadResume(diagnosticsTaskHandle);
	}
#endif
}

void Model::suspend_motor_task()
{
#ifndef SIMULATOR
	if(!osSemaphoreGetCount(suspend_motor_taskHandle))
	{
		osSemaphoreRelease(suspend_motor_taskHandle);
	}
#endif
}

void Model::suspend_diagnostics_task()
{
#ifndef SIMULATOR
	if(!osSemaphoreGetCount(suspend_diagnostics_taskHandle))
	{
		osSemaphoreRelease(suspend_diagnostics_taskHandle);
	}
#endif
}

void Model::activate_adc(bool retrieve_data)
{
	retrieve_adc_data = retrieve_data;
}

void Model::set_throttle_high_point()
{
#ifndef SIMULATOR
	if (osMutexAcquire(settingMutexHandle, osWaitForever) == osOK)
	{
//		HAL_ADC_Start(&hadc1);
//		HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
//		throttle_max = HAL_ADC_GetValue(&hadc1);
//		HAL_ADC_Stop(&hadc1);
		// Not sure if this will work
		ee.throttle_max = sensor_data[THROTTLE];

		EE_Write();

		osMutexRelease(settingMutexHandle);
	}
#endif
}

void Model::set_throttle_low_point()
{
#ifndef SIMULATOR
	if (osMutexAcquire(settingMutexHandle, osWaitForever) == osOK)
	{
//		HAL_ADC_Start(&hadc1);
//		HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
//		throttle_min = HAL_ADC_GetValue(&hadc1);
//		HAL_ADC_Stop(&hadc1);
		// Not sure if this will work
		ee.throttle_min = sensor_data[THROTTLE];

		EE_Write();

		osMutexRelease(settingMutexHandle);
	}
#endif
}

void Model::set_brake_high_point()
{
#ifndef SIMULATOR
	if (osMutexAcquire(settingMutexHandle, osWaitForever) == osOK)
	{
		//HAL_ADC_Start(&hadc2);
		//HAL_ADC_PollForConversion(&hadc2, HAL_MAX_DELAY);
		//brake_max = HAL_ADC_GetValue(&hadc2);
		//HAL_ADC_Stop(&hadc2);
		// Not sure if this will work
		ee.brake_max = sensor_data[BRAKE];

		EE_Write();

		osMutexRelease(settingMutexHandle);
	}
#endif
}

void Model::set_brake_low_point()
{
#ifndef SIMULATOR
	if (osMutexAcquire(settingMutexHandle, osWaitForever) == osOK)
	{
		//HAL_ADC_Start(&hadc2);
		//HAL_ADC_PollForConversion(&hadc2, HAL_MAX_DELAY);
		//brake_min = HAL_ADC_GetValue(&hadc2);
		//HAL_ADC_Stop(&hadc2);
		// Not sure if this will work
		ee.brake_min = sensor_data[BRAKE];

		EE_Write();

		osMutexRelease(settingMutexHandle);
	}
#endif
}

uint16_t Model::get_throttle_sensitivity()
{
	unsigned int temp = 100;
#ifndef SIMULATOR
	// Aquire Mutex
	if (osMutexAcquire(settingMutexHandle, osWaitForever) == osOK)
	{
		temp = ee.throttle_threshold;

		// Release Mutex
		osMutexRelease(settingMutexHandle);
	}
#endif // SIMULATOR
	return temp;
}

void Model::set_throttle_sensitivity(uint16_t throttle_value)
{
#ifndef SIMULATOR
	// Aquire Mutex
	if (osMutexAcquire(settingMutexHandle, osWaitForever) == osOK)
	{
		ee.throttle_threshold = throttle_value;

		EE_Write();

		// Release Mutex
		osMutexRelease(settingMutexHandle);
	}
#endif // SIMULATOR
}

uint16_t Model::get_brake_sensitivity()
{
	unsigned int temp = 100;
#ifndef SIMULATOR
	// Aquire Mutex
	if (osMutexAcquire(settingMutexHandle, osWaitForever) == osOK)
	{
		temp = ee.brake_threshold;
		// Release Mutex
		osMutexRelease(settingMutexHandle);
	}
#endif // SIMULATOR
	return temp;
}

void Model::set_brake_sensitivity(uint16_t brake_value)
{
#ifndef SIMULATOR
	// Aquire Mutex
	if (osMutexAcquire(settingMutexHandle, osWaitForever) == osOK)
	{
		ee.brake_threshold = brake_value;

		EE_Write();

		// Release Mutex
		osMutexRelease(settingMutexHandle);
	}
#endif // SIMULATOR
}

void Model::toggle_analog_brake()
{
#ifndef SIMULATOR
	if(osMutexAcquire(settingMutexHandle, osWaitForever))
	{
		ee.analog_brake_active = (ee.analog_brake_active == 1) ? 0 : 1;
		osMutexRelease(settingMutexHandle);
	}
#else
	test_bool = (test_bool == 1) ? 0 : 1;
#endif
}

uint8_t Model::get_analog_brake()
{
	uint8_t temp = 0;
#ifndef SIMULATOR
	if(osMutexAcquire(settingMutexHandle, osWaitForever))
	{
		temp = ee.analog_brake_active;
		osMutexRelease(settingMutexHandle);
	}
#else
	temp = test_bool;
#endif
	return temp;
}

float Model::get_CAN_transmit_frequency()
{
	unsigned int temp = 1000;
#ifndef SIMULATOR
	// Aquire Mutex
	if (osMutexAcquire(settingMutexHandle, osWaitForever) == osOK)
	{
		temp = ee.motor_frequency;
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
	if (osMutexAcquire(settingMutexHandle, osWaitForever) == osOK)
	{
		osSemaphoreRelease(motor_timing_modifiedHandle);
		ee.motor_frequency = frequency_value;

		EE_Write();

		// Release Mutex
		osMutexRelease(settingMutexHandle);
	}
#endif // SIMULATOR
}

void Model::get_username(int8_t user, uint8_t* username, uint8_t size)
{
#ifndef SIMULATOR
	if (osMutexAcquire(settingMutexHandle, osWaitForever) == osOK)
	{
		for(uint8_t i = 0; i < size; i++)
		{
			username[i] = ee.usernames[(user * USERNAME_SIZE) + i];
		}
		osMutexRelease(settingMutexHandle);
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
	if(osMutexAcquire(settingMutexHandle, osWaitForever))
	{
		for(uint8_t i = 0; i < size; i++)
		{
			password[i] = ee.passwords[(user * PASSWORD_SIZE) + i];
		}
		osMutexRelease(settingMutexHandle);
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
	if(osMutexAcquire(settingMutexHandle, osWaitForever))
	{
		return ee.num_users;
	}
#else
	return 1;
#endif
}

void Model::edit_username(uint8_t user, uint8_t* username)
{
#ifndef SIMULATOR
	if(osMutexAcquire(settingMutexHandle, osWaitForever))
	{
		for(uint8_t i = 0; i < USERNAME_SIZE; i++)
		{
			ee.usernames[(user * USERNAME_SIZE) + i] = username[i];
		}
		EE_Write();
		osMutexRelease(settingMutexHandle);
	}
#endif
}

void Model::edit_password(uint8_t user, uint8_t* password)
{
#ifndef SIMULATOR
	if(osMutexAcquire(settingMutexHandle, osWaitForever))
	{
		for(uint8_t i = 0; i < PASSWORD_SIZE; i++)
		{
			ee.passwords[(user * PASSWORD_SIZE) + i] = password[i];
		}
		EE_Write();
		osMutexRelease(settingMutexHandle);
	}
#endif
}

void Model::add_user(uint8_t* username, uint8_t* password)
{
#ifndef SIMULATOR
	if(osMutexAcquire(settingMutexHandle, osWaitForever))
	{
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
		osMutexRelease(settingMutexHandle);
	}
#endif
}

void Model::remove_user(uint8_t user)
{
#ifndef SIMULATOR
	if(osMutexAcquire(settingMutexHandle, osWaitForever))
	{
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
		osMutexRelease(settingMutexHandle);
	}
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

