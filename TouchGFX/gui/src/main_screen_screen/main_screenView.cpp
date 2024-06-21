#include <gui/main_screen_screen/main_screenView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <gui/containers/function_element.hpp>

#ifndef SIMULATOR
extern "C"
{
#include "motor.h"
#include "main.h"
#include "cmsis_os.h" // includes cmsis_os2 within the header file

	//Parameters to be set by touchGFX Task
	extern uint16_t threshold;						// For throttle sensitivity
	extern uint16_t throttle_min;		// For throttle calibration
	extern uint16_t throttle_max;		// For throttle calibration
	// Add brake sensor Calibration parameters
	// Add motor transmit frequency variable

	//MotorDataStruct is for hardware
	extern MotorData motorDataStruct;

	// Tasks
	extern osThreadId_t motorTaskHandle;

	// Mutexes
	extern osMutexId_t settingMutexHandle;

}
#endif

main_screenView::main_screenView() :
		high_point(true),
		calibration_mode(false),
		keypad_value_f(0.0),
		keypad_value_d(0),
		animation_tick(0),
		keypad_animation_state(KEYPAD_ANIMATION_READY),
		scrollWheelSelectedItemCallback(this,&main_screenView::scrollWheelSelectedItemHandler)
{
}

void main_screenView::setupScreen()
{
	main_screenViewBase::setupScreen();
	HAL::getInstance()->setFrameRateCompensation(true);
	function_wheel.setAnimationEndedCallback(scrollWheelSelectedItemCallback);

	keypad.setPosition(keypad_image.getX(), keypad_image.getY(), keypad_image.getWidth(), keypad_image.getHeight());
	delete_button.setPosition( keypad_image.getX() + keypad_image.getWidth()+ keypad.get_button_w_offset(),keypad_image.getY() + keypad.get_text_offset(),delete_button.getWidth(), delete_button.getHeight());
	cancel_button.setPosition(delete_button.getX(),delete_button.getY() + delete_button.getHeight()+ keypad.get_button_h_offset(), cancel_button.getWidth(),cancel_button.getHeight());
	enter_button.setPosition(cancel_button.getX(),cancel_button.getY() + cancel_button.getHeight()+ keypad.get_button_h_offset(), enter_button.getWidth(),enter_button.getHeight());
	command_box.setPosition(keypad_image.getX()- (command_box.getWidth() - keypad_image.getWidth()) / 2,keypad_image.getY(), command_box.getWidth(),command_box.getHeight());

	dummy_function_name_center.setWideTextAction(WIDE_TEXT_WORDWRAP);
	dummy_function_name_1.setVisible(false);
	dummy_function_name_center.setVisible(false);
	dummy_function_name_2.setVisible(false);
	value_set_background.setVisible(true);
	value_set_background.setAlpha(0);
	value_set_background.invalidate();

	command_page.add(keypad);
	keypad.setVisible(true);
	scrollWheelSelectedItemHandler();
}

void main_screenView::tearDownScreen()
{
	main_screenViewBase::tearDownScreen();
	HAL::getInstance()->setFrameRateCompensation(false);
}

void main_screenView::handleTickEvent()
{
	if (keypad_animation_state != 0)
	{
		animation_tick++;

		// General transition variables
		int16_t delta_alpha = EasingEquations::cubicEaseInOut(animation_tick, 0, 255, KEYPAD_ANIMATION_DURATION);

		// Keypad transition in out variables
		int16_t delta_x_keypad = EasingEquations::cubicEaseInOut(animation_tick, 0, 443, KEYPAD_ANIMATION_DURATION);
		int16_t function_title_x = EasingEquations::cubicEaseInOut(animation_tick, 273, 494 - 273, KEYPAD_ANIMATION_DURATION);
		int16_t delta_y_function_name = EasingEquations::cubicEaseInOut(animation_tick, 132, function_wheel.getY() - 132, KEYPAD_ANIMATION_DURATION);
		int16_t delta_h_function_name = EasingEquations::cubicEaseInOut(animation_tick, 50, function_wheel.getHeight() - 50, KEYPAD_ANIMATION_DURATION);
		int16_t delta_y_function_background = EasingEquations::cubicEaseInOut(animation_tick, 129, function_wheel.getY() - 129, KEYPAD_ANIMATION_DURATION);
		int16_t delta_h_function_background = EasingEquations::cubicEaseInOut(animation_tick, 55, function_wheel.getHeight() - 55, KEYPAD_ANIMATION_DURATION);
		int16_t delta_y_value_title = EasingEquations::cubicEaseInOut(animation_tick, 315, 264 - 315, KEYPAD_ANIMATION_DURATION);

		// Calibration transition in out variables
		int16_t delta_y_calibration_title = EasingEquations::cubicEaseInOut(animation_tick, 0, 42, KEYPAD_ANIMATION_DURATION);
		int16_t delta_y_calibration_value = EasingEquations::cubicEaseInOut(animation_tick, 0, 120, KEYPAD_ANIMATION_DURATION);
		int16_t delta_y_calibration_button = EasingEquations::cubicEaseInOut(animation_tick, 0, 110, KEYPAD_ANIMATION_DURATION);

		if (keypad_animation_state == KEYPAD_ANIMATION_IN_STEP_0)
		{
			if (animation_tick < KEYPAD_ANIMATION_DURATION)
			{
				// Fade out objects
				if (function_wheel.isVisible())
				{
					function_wheel.setVisible(false);
					dummy_function_name_1.setVisible(true);
					dummy_function_name_center.setVisible(true);
					dummy_function_name_2.setVisible(true);
				}

				dummy_background_1.setAlpha(255 - delta_alpha);
				dummy_function_name_1.setAlpha(255 - delta_alpha);
				dummy_background_2.setAlpha(255 - delta_alpha);
				dummy_function_name_2.setAlpha(255 - delta_alpha);

				dummy_background_1.invalidate();
				dummy_function_name_1.invalidate();
				dummy_background_2.invalidate();
				dummy_function_name_2.invalidate();

				function_select_button.setAlpha(255 - delta_alpha);
				button_text.setAlpha(255 - delta_alpha);

				function_select_button.invalidate();
				button_text.invalidate();
			}
			else
			{
				function_select_button.setTouchable(false);
				keypad_animation_state = KEYPAD_ANIMATION_IN_STEP_1;
				animation_tick = 0;
			}
		}
		else if (keypad_animation_state == KEYPAD_ANIMATION_IN_STEP_1)
		{
			if (animation_tick < KEYPAD_ANIMATION_DURATION)
			{
				// move the keypad
				keypad_image.moveTo(-418 + delta_x_keypad, keypad_image.getY());
				keypad.moveTo(keypad_image.getX(), keypad.getY());
				delete_button.moveTo(keypad_image.getX() + keypad_image.getWidth()+ keypad.get_button_w_offset(), keypad_image.getY() + keypad.get_text_offset());
				cancel_button.moveTo(delete_button.getX(), delete_button.getY() + delete_button.getHeight()+ keypad.get_button_h_offset());
				enter_button.moveTo(cancel_button.getX(), cancel_button.getY() + cancel_button.getHeight() + keypad.get_button_h_offset());
				command_box.moveTo(keypad_image.getX()- (command_box.getWidth()- keypad_image.getWidth()) / 2, keypad_image.getY());

				dummy_function_name_center.moveTo(25 + delta_x_keypad, delta_y_function_name);
				dummy_function_name_center.setWidthHeight(750 - delta_x_keypad, delta_h_function_name);
				dummy_background_center.moveTo(25 + delta_x_keypad, delta_y_function_background);
				dummy_background_center.setWidthHeight(750 - delta_x_keypad, delta_h_function_background);
				function_title.moveTo(function_title_x, function_title.getY());

				value_title.moveTo(function_title_x - 25, delta_y_value_title);
				value_text.moveTo(function_title_x - 25, 74 + delta_y_value_title);
				command_box_2.moveTo(function_title_x - 25, 80 + delta_y_value_title);
			}
			else
			{
				keypad_animation_state = KEYPAD_ANIMATION_READY;
				animation_tick = 0;
			}
		}
		else if (keypad_animation_state == KEYPAD_ANIMATION_OUT_STEP_0)
		{
			if (animation_tick < KEYPAD_ANIMATION_DURATION)
			{
				keypad_image.moveTo(25 - delta_x_keypad, keypad_image.getY());
				keypad.moveTo(keypad_image.getX(), keypad.getY());
				delete_button.moveTo(keypad_image.getX() + keypad_image.getWidth() + keypad.get_button_w_offset(), keypad_image.getY() + keypad.get_text_offset());
				cancel_button.moveTo(delete_button.getX(), delete_button.getY() + delete_button.getHeight() + keypad.get_button_h_offset());
				enter_button.moveTo(cancel_button.getX(), cancel_button.getY() + cancel_button.getHeight() + keypad.get_button_h_offset());
				command_box.moveTo( keypad_image.getX() - (command_box.getWidth() - keypad_image.getWidth()) / 2, keypad_image.getY());

				dummy_function_name_center.moveTo(468 - delta_x_keypad, 132 + 74 - delta_y_function_name);
				dummy_function_name_center.setWidthHeight(307 + delta_x_keypad, 215 - delta_h_function_name);
				dummy_background_center.moveTo(468 - delta_x_keypad, 129 + 74 - delta_y_function_background);
				dummy_background_center.setWidthHeight(307 + delta_x_keypad, 220 - (delta_h_function_background));
				function_title.moveTo(273 + 494 - function_title_x, function_title.getY());

				value_title.moveTo((273 + 494 - function_title_x) - 25, 264 + (315 - delta_y_value_title));
				value_text.moveTo((273 + 494 - function_title_x) - 25, 338 + (389 - (74 + delta_y_value_title)));
				command_box_2.moveTo((273 + 494 - function_title_x) - 25, 344 + (395 - (80 + delta_y_value_title)));
			}
			else
			{
				keypad_animation_state = KEYPAD_ANIMATION_OUT_STEP_1;
				animation_tick = 0;
			}
		}
		else if (keypad_animation_state == KEYPAD_ANIMATION_OUT_STEP_1)
		{
			if (animation_tick < KEYPAD_ANIMATION_DURATION)
			{
				dummy_background_1.setAlpha(delta_alpha);
				dummy_function_name_1.setAlpha(delta_alpha);
				dummy_background_2.setAlpha(delta_alpha);
				dummy_function_name_2.setAlpha(delta_alpha);

				dummy_background_1.invalidate();
				dummy_function_name_1.invalidate();
				dummy_background_2.invalidate();
				dummy_function_name_2.invalidate();

				function_select_button.setAlpha(delta_alpha);
				button_text.setAlpha(delta_alpha);

				function_select_button.invalidate();
				button_text.invalidate();
			}
			else
			{
				if (!function_wheel.isVisible())
				{
					function_wheel.setVisible(true);
					dummy_function_name_1.setVisible(false);
					dummy_function_name_center.setVisible(false);
					dummy_function_name_2.setVisible(false);

					function_wheel.invalidate();
				}
				function_select_button.setTouchable(true);

				keypad_animation_state = KEYPAD_ANIMATION_READY;
				animation_tick = 0;
			}
		}
		else if (keypad_animation_state == KEYPAD_VALUE_SET_STEP_0)
		{
			if (animation_tick < KEYPAD_SET_ANIMATION_DURATION)
			{
				value_set_background.setAlpha(delta_alpha);
				value_set_background.invalidate();
			}
			else
			{
				keypad_animation_state = KEYPAD_VALUE_SET_STEP_1;
				animation_tick = 0;
			}
		}
		else if (keypad_animation_state == KEYPAD_VALUE_SET_STEP_1)
		{
			if (animation_tick < KEYPAD_ANIMATION_DURATION)
			{
				value_set_background.setAlpha(255 - delta_alpha);
				value_set_background.invalidate();
			}
			else
			{
				value_title.setTypedText(touchgfx::TypedText(T_VALUE_TITLE));
				value_title.invalidate();
				keypad_animation_state = KEYPAD_ANIMATION_OUT_STEP_0;
				animation_tick = 0;
			}
		}
		else if (keypad_animation_state == CALIBRATION_IN_STEP_0)
		{
			if (animation_tick < KEYPAD_ANIMATION_DURATION)
			{
				// Fade out unnecessary objects
				if (function_wheel.isVisible()) {
					function_wheel.setVisible(false);
					dummy_function_name_1.setVisible(true);
					dummy_function_name_center.setVisible(true);
					dummy_function_name_2.setVisible(true);
				}

				dummy_background_1.setAlpha(255 - delta_alpha);
				dummy_function_name_1.setAlpha(255 - delta_alpha);
				dummy_background_2.setAlpha(255 - delta_alpha);
				dummy_function_name_2.setAlpha(255 - delta_alpha);

				dummy_background_1.invalidate();
				dummy_function_name_1.invalidate();
				dummy_background_2.invalidate();
				dummy_function_name_2.invalidate();
			}
			else
			{
				animation_tick = 0;
				keypad_animation_state = CALIBRATION_IN_STEP_1;
			}
		}
		else if (keypad_animation_state == CALIBRATION_IN_STEP_1)
		{
			if (animation_tick < KEYPAD_ANIMATION_DURATION) {
				// Move the value title and box up with the execute function button
				dummy_function_name_center.moveTo(dummy_function_name_center.getX(), 132 - delta_y_calibration_title);
				dummy_background_center.moveTo(dummy_background_center.getX(), 129 - delta_y_calibration_title);
				button_text.moveTo(button_text.getX(), 260 + delta_y_calibration_button);
				function_select_button.moveTo(function_select_button.getX(), 260 + delta_y_calibration_button);
				value_title.moveTo(value_title.getX(), 315 - delta_y_calibration_value);
				value_text.moveTo(value_text.getX(), 389 - delta_y_calibration_value);
				command_box_2.moveTo(command_box_2.getX(), 395 - delta_y_calibration_value);

				dummy_function_name_center.invalidate();
				dummy_background_center.invalidate();
				button_text.invalidate();
				function_select_button.invalidate();
				value_text.invalidate();
				command_box_2.invalidate();
			}
			else
			{
				animation_tick = 0;
				keypad_animation_state = KEYPAD_ANIMATION_READY;
			}
		}
		else if (keypad_animation_state == CALIBRATION_OUT_STEP_0)
		{
			if (animation_tick < KEYPAD_ANIMATION_DURATION)
			{
				// Move the value title and box back to their original position
				dummy_function_name_center.moveTo(dummy_function_name_center.getX(), 90 + delta_y_calibration_title);
				dummy_background_center.moveTo(dummy_background_center.getX(), 87 + delta_y_calibration_title);
				button_text.moveTo(button_text.getX(), 370 - delta_y_calibration_button);
				function_select_button.moveTo(function_select_button.getX(),370 - delta_y_calibration_button);
				value_title.moveTo(value_title.getX(),195 + delta_y_calibration_value);
				value_text.moveTo(value_text.getX(),269 + delta_y_calibration_value);
				command_box_2.moveTo(command_box_2.getX(),275 + delta_y_calibration_value);

				dummy_function_name_center.invalidate();
				dummy_background_center.invalidate();
				button_text.invalidate();
				function_select_button.invalidate();
				value_text.invalidate();
				command_box_2.invalidate();
			}
			else
			{
				animation_tick = 0;
				keypad_animation_state = CALIBRATION_OUT_STEP_1;
			}
		}
		else if (keypad_animation_state == CALIBRATION_OUT_STEP_1)
		{
			if (animation_tick < KEYPAD_ANIMATION_DURATION)
			{
				// Fade in default objects
				dummy_background_1.setAlpha(delta_alpha);
				dummy_function_name_1.setAlpha(delta_alpha);
				dummy_background_2.setAlpha(delta_alpha);
				dummy_function_name_2.setAlpha(delta_alpha);

				dummy_background_1.invalidate();
				dummy_function_name_1.invalidate();
				dummy_background_2.invalidate();
				dummy_function_name_2.invalidate();
			}
			else
			{
				if (!function_wheel.isVisible())
				{
					function_wheel.setVisible(true);
					dummy_function_name_1.setVisible(false);
					dummy_function_name_center.setVisible(false);
					dummy_function_name_2.setVisible(false);
				}
				animation_tick = 0;
				keypad_animation_state = KEYPAD_ANIMATION_READY;
			}
		}
	}
}

void main_screenView::execute_function_pressed()
{
	if(keypad_animation_state == KEYPAD_ANIMATION_READY)
	{
		switch (function_wheel.getSelectedItem())
		{
			case 0:
			{
				// Set throttle sensitivity
				keypad_animation_state = KEYPAD_ANIMATION_IN_STEP_0;

				presenter->set_throttle_sensitivity(keypad.get_input_value_d());
				break;
			}
			case 1:
			{
				// Set brake sensitivity
				keypad_animation_state = KEYPAD_ANIMATION_IN_STEP_0;

				presenter->set_brake_sensitivity(keypad.get_input_value_d());
				break;
			}
			case 2:
			{
				// Calibrate throttle sensor
				if (calibration_mode)
				{
					// Set the high and low point
					if (high_point)
					{
						// Set the high point ADC value
						presenter->set_throttle_high_point();
						value_title.setTypedText(touchgfx::TypedText(T_LOW_POINT));
						value_title.invalidate();
						high_point = false;
					}
					else
					{
						// Set the low point ADC value
						presenter->set_throttle_low_point();
						value_title.setTypedText(touchgfx::TypedText(T_VALUE_TITLE));
						value_title.invalidate();
						keypad_animation_state = CALIBRATION_OUT_STEP_0;
						calibration_mode = false;
						high_point = true;

						// Resume the tasks that depend on the throttle sensor ADC value
#ifndef SIMULATOR
						osThreadResume(motorTaskHandle);
#endif
					}
				}
				else
				{
					value_title.setTypedText(touchgfx::TypedText(T_HIGH_POINT));
					button_text.setTypedText(touchgfx::TypedText(T_SET_ANALOG_VALUE));
					value_title.invalidate();
					button_text.invalidate();
					keypad_animation_state = CALIBRATION_IN_STEP_0;
					calibration_mode = true;

					// Suspend all tasks affected by the throttle sensor ADC value
#ifndef SIMULATOR
					osThreadSuspend(motorTaskHandle);
#endif
				}
				break;
			}
			case 3:
			{
				// Set motor CAN transmit frequency
				keypad_animation_state = KEYPAD_ANIMATION_IN_STEP_0;

				break;
			}
			case 4:
			{
				// Calibrate brake sensor
				if (calibration_mode)
				{
					// set the high and low point
					if (high_point)
					{
						// Set the high point ADC value
						presenter->set_brake_high_point();
						value_title.setTypedText(touchgfx::TypedText(T_LOW_POINT));
						value_title.invalidate();
						high_point = false;
					}
					else
					{
						// Set the low point ADC value
						presenter->set_brake_low_point();
						value_title.setTypedText(touchgfx::TypedText(T_VALUE_TITLE));
						value_title.invalidate();
						keypad_animation_state = CALIBRATION_OUT_STEP_0;
						calibration_mode = false;
						high_point = true;

						// Resume the tasks that depend on the brake sensor ADC value
#ifndef SIMULATOR
						osThreadResume(motorTaskHandle);
#endif
					}
				}
				else
				{
					value_title.setTypedText(touchgfx::TypedText(T_HIGH_POINT));
					button_text.setTypedText(touchgfx::TypedText(T_SET_ANALOG_VALUE));
					value_title.invalidate();
					button_text.invalidate();
					keypad_animation_state = CALIBRATION_IN_STEP_0;
					calibration_mode = true;
					// Suspend all tasks affected by the brake sensor ADC Value
#ifndef SIMULATOR
					osThreadSuspend(motorTaskHandle);
#endif
				}
				break;
			}
			case 5:
			{
				// Create new User
				// stop all control tasks
#ifndef SIMULATOR
				osThreadSuspend(motorTaskHandle);
#endif // SIMULATOR

				// change to user screen
				break;
			}
			case 6:
			{
				// stop all control tasks
#ifndef SIMULATOR
				osThreadSuspend(motorTaskHandle);
#endif // SIMULATOR

				// Edit User
				// change to user screen
				break;
			}
		}
	}
}

void main_screenView::delete_char()
{
	if(keypad_animation_state == KEYPAD_ANIMATION_READY)
	{
		keypad.delete_char();
	}
}

void main_screenView::enter_command()
{
	// define what happens when the enter button is pressed for the keypad
	if (keypad_animation_state == KEYPAD_ANIMATION_READY)
	{

		keypad_animation_state = KEYPAD_VALUE_SET_STEP_0;

		//display the current value of the command in question
		Unicode::strncpy(value_textBuffer, keypad.getBuffer(), VALUE_TEXT_SIZE);
		value_text.invalidate();

		value_title.setTypedText(touchgfx::TypedText(T_VALUE_SET));
	}
}

void main_screenView::cancel_command()
{
	if (keypad_animation_state == KEYPAD_ANIMATION_READY)
	{
		keypad_animation_state = KEYPAD_ANIMATION_OUT_STEP_0;
	}

}

void main_screenView::function_wheelUpdateItem(function_element &item, int16_t itemIndex)
{
	switch (itemIndex)
	{
		case 0:
		{
			item.setupElement(T_FUNCTION_0);
			break;
		}
		case 1:
		{
			item.setupElement(T_FUNCTION_1);
			break;
		}
		case 2:
		{
			item.setupElement(T_FUNCTION_2);
			break;
		}
		case 3:
		{
			item.setupElement(T_FUNCTION_3);
			break;
		}
		case 4:
		{
			item.setupElement(T_FUNCTION_4);
			break;
		}
		case 5:
		{
			item.setupElement(T_FUNCTION_5);
			break;
		}
		case 6:
		{
			item.setupElement(T_FUNCTION_6);
			break;
		}
	}
}

void main_screenView::function_wheelUpdateCenterItem(function_center &item,int16_t itemIndex)
{
	switch (itemIndex)
	{
		case 0:
		{
			item.setupElement(T_FUNCTION_0);
			break;
		}
		case 1:
		{
			item.setupElement(T_FUNCTION_1);
			break;
		}
		case 2:
		{
			item.setupElement(T_FUNCTION_2);
			break;
		}
		case 3:
		{
			item.setupElement(T_FUNCTION_3);
			break;
		}
		case 4:
		{
			item.setupElement(T_FUNCTION_4);
			break;
		}
		case 5:
		{
			item.setupElement(T_FUNCTION_5);
			break;
		}
		case 6:
		{
			item.setupElement(T_FUNCTION_6);
			break;
		}
	}
}

void main_screenView::scrollWheelSelectedItemHandler()
{
	// Show the value of the parameter

	presenter->stop_adc_retrieval();

	switch (function_wheel.getSelectedItem())
	{
		case 0:
		{
			// Set throttle sensitivity
			dummy_function_name_1.setTypedText(touchgfx::TypedText(T_FUNCTION_6));
			dummy_function_name_center.setTypedText(touchgfx::TypedText(T_FUNCTION_0));
			dummy_function_name_2.setTypedText(touchgfx::TypedText(T_FUNCTION_1));

			keypad_value_d = presenter->get_throttle_sensitivity();
			Unicode::snprintf(value_textBuffer, VALUE_TEXT_SIZE, "%d",keypad_value_d);

			dummy_function_name_1.invalidate();
			dummy_function_name_center.invalidate();
			dummy_function_name_2.invalidate();
			value_text.invalidate();
			break;
		}
		case 1:
		{
			// Set brake sensitivity
			dummy_function_name_1.setTypedText(touchgfx::TypedText(T_FUNCTION_0));
			dummy_function_name_center.setTypedText(touchgfx::TypedText(T_FUNCTION_1));
			dummy_function_name_2.setTypedText(touchgfx::TypedText(T_FUNCTION_2));

			keypad_value_d = presenter->get_brake_sensitivity();
			Unicode::snprintf(value_textBuffer, VALUE_TEXT_SIZE, "%d",(uint16_t) keypad_value_d);

			dummy_function_name_1.invalidate();
			dummy_function_name_center.invalidate();
			dummy_function_name_2.invalidate();
			value_text.invalidate();
			break;
		}
		case 2:
		{
			// Calibrate throttle sensor
			dummy_function_name_1.setTypedText(touchgfx::TypedText(T_FUNCTION_1));
			dummy_function_name_center.setTypedText(touchgfx::TypedText(T_FUNCTION_2));
			dummy_function_name_2.setTypedText(touchgfx::TypedText(T_FUNCTION_3));

			// Display the raw throttle sensor analog value
			presenter->start_throttle_adc();

			dummy_function_name_1.invalidate();
			dummy_function_name_center.invalidate();
			dummy_function_name_2.invalidate();
			break;
		}
		case 3:
		{
			// Set motor CAN transmit frequency
			dummy_function_name_1.setTypedText(touchgfx::TypedText(T_FUNCTION_2));
			dummy_function_name_center.setTypedText(touchgfx::TypedText(T_FUNCTION_3));
			dummy_function_name_2.setTypedText(touchgfx::TypedText(T_FUNCTION_4));

			keypad_value_d = presenter->get_CAN_transmit_frequency();
			Unicode::snprintf(value_textBuffer, VALUE_TEXT_SIZE, "%d",(uint16_t) keypad_value_d);

			dummy_function_name_1.invalidate();
			dummy_function_name_center.invalidate();
			dummy_function_name_2.invalidate();
			value_text.invalidate();
			break;
		}
		case 4:
		{
			// Calibrate brake sensor
			dummy_function_name_1.setTypedText(touchgfx::TypedText(T_FUNCTION_3));
			dummy_function_name_center.setTypedText(touchgfx::TypedText(T_FUNCTION_4));
			dummy_function_name_2.setTypedText(touchgfx::TypedText(T_FUNCTION_5));

			presenter->start_brake_adc();

			dummy_function_name_1.invalidate();
			dummy_function_name_center.invalidate();
			dummy_function_name_2.invalidate();

			// Display the raw brake sensor analog value
			break;
		}
		case 5:
		{
			// Create New User
			dummy_function_name_1.setTypedText(touchgfx::TypedText(T_FUNCTION_4));
			dummy_function_name_center.setTypedText(touchgfx::TypedText(T_FUNCTION_5));
			dummy_function_name_2.setTypedText(touchgfx::TypedText(T_FUNCTION_6));

			dummy_function_name_1.invalidate();
			dummy_function_name_center.invalidate();
			dummy_function_name_2.invalidate();

			Unicode::strncpy(value_textBuffer, "N/A", VALUE_TEXT_SIZE);
			value_text.invalidate();
			break;
		}
		case 6:
		{
			// Edit User
			dummy_function_name_1.setTypedText(touchgfx::TypedText(T_FUNCTION_5));
			dummy_function_name_center.setTypedText(touchgfx::TypedText(T_FUNCTION_6));
			dummy_function_name_2.setTypedText(touchgfx::TypedText(T_FUNCTION_0));

			dummy_function_name_1.invalidate();
			dummy_function_name_center.invalidate();
			dummy_function_name_2.invalidate();

			Unicode::strncpy(value_textBuffer, "N/A", VALUE_TEXT_SIZE);
			value_text.invalidate();
			break;
		}
	}
}

void main_screenView::display_adc(unsigned int adc_value)
{
	Unicode::snprintf(value_textBuffer, VALUE_TEXT_SIZE, "%d", adc_value);
	value_text.invalidate();
}

#ifndef SIMULATOR
//For simulator - comment out motorDataStruct and set wildcard data to literal (e.x. replace motorDataStruct.fetTemp with 0)
void main_screenView::motorDataUpdate()
{
	Unicode::snprintf(fet_temp_wildBuffer, FET_TEMP_WILD_SIZE, "%d",motorDataStruct.fetTemp);
	Unicode::snprintf(motor_temp_wildBuffer, MOTOR_TEMP_WILD_SIZE, "%d",motorDataStruct.motorTemp);
	Unicode::snprintf(volt_in_wildBuffer, VOLT_IN_WILD_SIZE, "%d",motorDataStruct.voltIn);
	Unicode::snprintf(curr_in_wildBuffer, CURR_IN_WILD_SIZE, "%d",motorDataStruct.currIn);
	fet_temp_wild.invalidate();
	motor_temp_wild.invalidate();
	volt_in_wild.invalidate();
	curr_in_wild.invalidate();
}
#endif
