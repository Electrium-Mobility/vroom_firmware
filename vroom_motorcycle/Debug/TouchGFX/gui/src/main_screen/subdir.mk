################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/gui/src/main_screen/mainPresenter.cpp \
../TouchGFX/gui/src/main_screen/mainView.cpp 

OBJS += \
./TouchGFX/gui/src/main_screen/mainPresenter.o \
./TouchGFX/gui/src/main_screen/mainView.o 

CPP_DEPS += \
./TouchGFX/gui/src/main_screen/mainPresenter.d \
./TouchGFX/gui/src/main_screen/mainView.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/gui/src/main_screen/%.o TouchGFX/gui/src/main_screen/%.su TouchGFX/gui/src/main_screen/%.cyclo: ../TouchGFX/gui/src/main_screen/%.cpp TouchGFX/gui/src/main_screen/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F469xx -c -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-gui-2f-src-2f-main_screen

clean-TouchGFX-2f-gui-2f-src-2f-main_screen:
	-$(RM) ./TouchGFX/gui/src/main_screen/mainPresenter.cyclo ./TouchGFX/gui/src/main_screen/mainPresenter.d ./TouchGFX/gui/src/main_screen/mainPresenter.o ./TouchGFX/gui/src/main_screen/mainPresenter.su ./TouchGFX/gui/src/main_screen/mainView.cyclo ./TouchGFX/gui/src/main_screen/mainView.d ./TouchGFX/gui/src/main_screen/mainView.o ./TouchGFX/gui/src/main_screen/mainView.su

.PHONY: clean-TouchGFX-2f-gui-2f-src-2f-main_screen

