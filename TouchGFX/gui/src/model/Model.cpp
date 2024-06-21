#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#ifndef SIMULATOR

extern "C"
{
#include "motor.h"
#include "main.h"
#include "cmsis_os.h"

// Queues
extern osMessageQueueId_t adcQueueHandle;

// Mutexes
extern osMutexId_t settingMutexHandle;

extern uint32_t motor_task_delay;

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

}

#endif // SIMULATOR

Model::Model() :
		modelListener(0),
		adc_value(0)
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

unsigned int Model::get_throttle_sensitivity()
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

void Model::set_throttle_sensitivity(unsigned int throttle_value)
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

unsigned int Model::get_brake_sensitivity()
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

void Model::set_brake_sensitivity(unsigned int brake_value)
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

unsigned int Model::get_CAN_transmit_frequency()
{
	unsigned int temp = 1000;
#ifndef SIMULATOR
	// Aquire Mutex
	if (osMutexAcquire(settingMutexHandle, 10) == osOK)
	{
		temp = motor_task_delay;
		// Release Mutex
		osMutexRelease(settingMutexHandle);
	}
#endif // SIMULATOR

	// Return frequency in Hz
	return 1000 / temp;
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
