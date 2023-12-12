#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#ifndef SIMULATOR

#include <cmsis_os2.h>
#include <main.h>

extern "C"
{
	extern osMessageQueueId_t ADCQueueHandle;
}

#endif

Model::Model() : modelListener(0), ADC_value(30)
{

}

void Model::tick()
{
	if(osMessageQueueGetCount(ADCQueueHandle) > 0)
	{
		if(osMessageQueueGet(ADCQueueHandle, &ADC_value, 0, 0) == osOK)
		{
			modelListener->setADC(ADC_value);
		}
	}
}
