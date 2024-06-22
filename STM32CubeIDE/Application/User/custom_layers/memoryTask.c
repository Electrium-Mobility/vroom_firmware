/*
 * memory.c
 *
 *  Created on: Jun 22, 2024
 *      Author: Victor Kalenda
 */
#include "memoryTask.h"

#include "main.h"
#include "cmsis_os.h"

extern osThreadId_t memoryTaskHandle;
extern osMessageQueueId_t memoryQueueHandle;


// Private Variables
uint32_t data = 0;
uint32_t memory_code = 0;
uint8_t message_count = 0;

void memoryTask_init()
{
}

void memoryTask_poll()
{
	// There is definitely a much more efficient way of implementing this
	message_count = osMessageQueueGetCount(memoryQueueHandle);
	if(message_count > 0)
	{
		// 1 count translates to 2 indexes in the queue
		for(uint8_t i = 0; i < message_count; i++)
		{
			osMessageQueueGet(memoryQueueHandle, &memory_code, 0, 0);
			osMessageQueueGet(memoryQueueHandle, &data, 0, 0);
			save_memory(memory_code, data);
		}
	}
}

memory_status_t save_memory(const uint32_t memory_code, const uint32_t data)
{
	memory_status_t status = MEMORY_WRITE_ERROR;

	return status;
}
