################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/generated/images/src/__generated/image_alternate_theme_images_backgrounds_800x480_gradient_dark.cpp \
../TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_gauge_medium_backgrounds_active.cpp \
../TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_gauge_medium_needles_smooth.cpp \
../TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_togglebutton_medium_rounded_off_light.cpp \
../TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_togglebutton_medium_rounded_on_normal.cpp 

OBJS += \
./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_backgrounds_800x480_gradient_dark.o \
./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_gauge_medium_backgrounds_active.o \
./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_gauge_medium_needles_smooth.o \
./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_togglebutton_medium_rounded_off_light.o \
./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_togglebutton_medium_rounded_on_normal.o 

CPP_DEPS += \
./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_backgrounds_800x480_gradient_dark.d \
./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_gauge_medium_backgrounds_active.d \
./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_gauge_medium_needles_smooth.d \
./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_togglebutton_medium_rounded_off_light.d \
./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_togglebutton_medium_rounded_on_normal.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/generated/images/src/__generated/%.o TouchGFX/generated/images/src/__generated/%.su TouchGFX/generated/images/src/__generated/%.cyclo: ../TouchGFX/generated/images/src/__generated/%.cpp TouchGFX/generated/images/src/__generated/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F469xx -c -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-generated-2f-images-2f-src-2f-__generated

clean-TouchGFX-2f-generated-2f-images-2f-src-2f-__generated:
	-$(RM) ./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_backgrounds_800x480_gradient_dark.cyclo ./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_backgrounds_800x480_gradient_dark.d ./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_backgrounds_800x480_gradient_dark.o ./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_backgrounds_800x480_gradient_dark.su ./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_gauge_medium_backgrounds_active.cyclo ./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_gauge_medium_backgrounds_active.d ./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_gauge_medium_backgrounds_active.o ./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_gauge_medium_backgrounds_active.su ./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_gauge_medium_needles_smooth.cyclo ./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_gauge_medium_needles_smooth.d ./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_gauge_medium_needles_smooth.o ./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_gauge_medium_needles_smooth.su ./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_togglebutton_medium_rounded_off_light.cyclo ./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_togglebutton_medium_rounded_off_light.d ./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_togglebutton_medium_rounded_off_light.o ./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_togglebutton_medium_rounded_off_light.su ./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_togglebutton_medium_rounded_on_normal.cyclo ./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_togglebutton_medium_rounded_on_normal.d ./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_togglebutton_medium_rounded_on_normal.o ./TouchGFX/generated/images/src/__generated/image_alternate_theme_images_widgets_togglebutton_medium_rounded_on_normal.su

.PHONY: clean-TouchGFX-2f-generated-2f-images-2f-src-2f-__generated

