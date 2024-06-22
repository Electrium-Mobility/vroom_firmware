/*
 * memory.h
 *
 *  Created on: Jun 22, 2024
 *      Author: Victor Kalenda
 */

#ifndef APPLICATION_USER_CUSTOM_LAYERS_MEMORYTASK_H_
#define APPLICATION_USER_CUSTOM_LAYERS_MEMORYTASK_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
  MEMORY_OK                    = 0,         ///< Operation completed successfully.
  MEMORY_WRITE_ERROR           = 1,         ///< Unspecified memory write error
  MEMORY_READ_ERROR            = 2,         ///< Unspecified memory read error
} memory_status_t;

// Memory Struct to be stored in Emulated EEPROM for a maximum of 10 users
typedef struct
{
	// Login Memory
	char users[15][10];							// memory code 0
	char passwords[15][10];						// memory code 1

	// Calibration Settings
	uint16_t throttle_max;						// memory code 2
	uint16_t throttle_min;						// memory code 3
	uint16_t brake_max;							// memory code 4
	uint16_t brake_min;							// memory code 5

	// User Specific Settings
	uint16_t throttle_thresholds[10];			// memory code 6
	uint16_t brake_thresholds[10];				// memory code 7
	float diagnostic_frequencies[10];			// memory code 8
	float motor_frequencies[10];				// memory code 9
}memory_t;

void memoryTask_init();

void memoryTask_poll();


memory_status_t save_memory(const uint32_t memory_code, const uint32_t data);

#ifdef __cplusplus
}
#endif

#endif /* APPLICATION_USER_CUSTOM_LAYERS_MEMORYTASK_H_ */
