#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#ifndef SIMULATOR

extern "C" {
#include "motor.h"
#include "main.h"
#include "cmsis_os.h"

extern uint16_t threshold;
// extern uint16_t brake_sensitivity;
// extern uint8_t display_throttle_adc;
// extern uint8_t display_brake_adc;

extern osMessageQueueId_t adcQueueHandle;
extern osMutexId_t settingMutexHandle;
extern ADC_HandleTypeDef hadc1;
extern uint16_t throttle_max;
extern uint16_t throttle_min;
//extern uint16_t brake_max;
//extern uint16_t brake_min;
}

#endif // SIMULATOR

/*
 * TODO:
 * For the task which handles the throttle and brake ADC
 * create the variable display_throttle_adc, display_brake_adc, brake_max, brake_min and brake_sensitivity in main.c
 * if the values of these variables is true, Put the adc value of the corresponding sensors into the adcQueue
 * use the function osMessageQueuePut(adcQueueHandle, adc_value, 0, 0) in an if statement like in Model:: tick below
 *
 * Initialize an adc for the brake sensor
 */

Model::Model() :
		modelListener(0), retrieve_adc(false), adc_value(0) {

}

void Model::tick() {
#ifndef SIMULATOR
	if (retrieve_adc) {
		// Retrieve the throttle ADC value from the queue
		if (osMessageQueueGetCount(adcQueueHandle) > 0) {
			if (osMessageQueueGet(adcQueueHandle, &adc_value, 0, 0) == osOK) {
				modelListener->display_adc(adc_value);
			}
		}
	}
#endif // SIMULATOR
}

void Model::set_throttle_high_point() {
#ifndef SIMULATOR
	if (osMutexAcquire(settingMutexHandle, 10) == osOK) {
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
		throttle_max = HAL_ADC_GetValue(&hadc1);
		HAL_ADC_Stop(&hadc1);

		osMutexRelease(settingMutexHandle);
	}
#endif
}

void Model::set_throttle_low_point() {
#ifndef SIMULATOR
	if (osMutexAcquire(settingMutexHandle, 10) == osOK) {
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
		throttle_min = HAL_ADC_GetValue(&hadc1);
		HAL_ADC_Stop(&hadc1);

		osMutexRelease(settingMutexHandle);
	}
#endif
}

void Model::set_brake_high_point() {
#ifndef SIMULATOR
	if (osMutexAcquire(settingMutexHandle, 10) == osOK) {
		//HAL_ADC_Start(&hadc2);
		//HAL_ADC_PollForConversion(&hadc2, HAL_MAX_DELAY);
		//brake_max = HAL_ADC_GetValue(&hadc2);
		//HAL_ADC_Stop(&hadc2);

		osMutexRelease(settingMutexHandle);
	}
#endif
}

void Model::set_brake_low_point() {
#ifndef SIMULATOR
	if (osMutexAcquire(settingMutexHandle, 10) == osOK) {
		//HAL_ADC_Start(&hadc2);
		//HAL_ADC_PollForConversion(&hadc2, HAL_MAX_DELAY);
		//brake_min = HAL_ADC_GetValue(&hadc2);
		//HAL_ADC_Stop(&hadc2);

		osMutexRelease(settingMutexHandle);
	}
#endif
}

unsigned int Model::get_throttle_sensitivity() {
	unsigned int temp = 100;
#ifndef SIMULATOR
	// Aquire Mutex
	if (osMutexAcquire(settingMutexHandle, 10) == osOK) {
		temp = threshold;
		// Release Mutex
		osMutexRelease(settingMutexHandle);
	}
#endif // SIMULATOR
	return temp;
}

void Model::set_throttle_sensitivity(unsigned int throttle_value) {
#ifndef SIMULATOR
	// Aquire Mutex
	if (osMutexAcquire(settingMutexHandle, 10) == osOK) {
		threshold = throttle_value;
		// Release Mutex
		osMutexRelease(settingMutexHandle);
	}
#endif // SIMULATOR
}

unsigned int Model::get_brake_sensitivity() {
	unsigned int temp = 100;
#ifndef SIMULATOR
	// Aquire Mutex
	if (osMutexAcquire(settingMutexHandle, 10) == osOK) {
		//temp = brake_threshold;
		// Release Mutex
		osMutexRelease(settingMutexHandle);
	}

#endif // SIMULATOR
	return temp;
}

void Model::set_brake_sensitivity(unsigned int brake_value) {
#ifndef SIMULATOR
	// Aquire Mutex
	if (osMutexAcquire(settingMutexHandle, 10) == osOK) {
		//brake_threshold = brake_value;
		// Release Mutex
		osMutexRelease(settingMutexHandle);
	}
#endif // SIMULATOR
}

unsigned int Model::get_CAN_transmit_frequency() {
	unsigned int temp = 1000;
#ifndef SIMULATOR
	// Aquire Mutex
	if (osMutexAcquire(settingMutexHandle, 10) == osOK) {
		//temp = motor_task_delay;
		// Release Mutex
		osMutexRelease(settingMutexHandle);
	}
#endif // SIMULATOR

	// Return frequency in Hz
	return 1000 / temp;
}

void Model::start_throttle_adc() {
#ifndef SIMULATOR
	// Aquire Mutex
	if (osMutexAcquire(settingMutexHandle, 10) == osOK) {
		//display_throttle_adc = true;
		//retrieve_adc = display_throttle_adc;

		// Release Mutex
		osMutexRelease(settingMutexHandle);
	}

#endif
}

void Model::start_brake_adc() {
#ifndef SIMULATOR
	// Aquire Mutex
	if (osMutexAcquire(settingMutexHandle, 10) == osOK) {
		// display_brake_adc = true;
		// retrieve_adc = display_brake_adc;

		// Release Mutex
		osMutexRelease(settingMutexHandle);
	}
#endif
}

void Model::stop_adc_retrieval() {
#ifndef SIMULATOR
	// Aquire Mutex
	if (osMutexAcquire(settingMutexHandle, 10) == osOK) {
		// display_throttle_adc = false;
		// display_brake_adc = false;
		retrieve_adc = false;
		// Release Mutex
		osMutexRelease(settingMutexHandle);
	}
#endif
}
