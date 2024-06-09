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

	//Parameters to be set by touchGFX Task
	extern uint16_t threshold;						// For throttle sensitivity
	extern uint16_t throttle_min;		// For throttle calibration
	extern uint16_t throttle_max;		// For throttle calibration
	// Add brake sensor Calibration parameters
	// Add motor transmit frequency variable

	//MotorDataStruct is for hardware
	extern MotorData motorDataStruct;
}
#endif

main_screenView::main_screenView() :
	animation_tick(0),
	keypad_animation_state(KEYPAD_ANIMATION_READY),
	scrollWheelSelectedItemCallback(this, &main_screenView::scrollWheelSelectedItemHandler)
{

}

void main_screenView::setupScreen()
{
    main_screenViewBase::setupScreen();
    HAL::getInstance()->setFrameRateCompensation(true);
    function_wheel.setAnimationEndedCallback(scrollWheelSelectedItemCallback);

    keypad.setPosition(keypad_image.getX(), keypad_image.getY(), keypad_image.getWidth(), keypad_image.getHeight());
	delete_button.setPosition(keypad_image.getX() + keypad_image.getWidth() + keypad.get_button_w_offset(), keypad_image.getY() + keypad.get_text_offset(), delete_button.getWidth(), delete_button.getHeight());
	cancel_button.setPosition(delete_button.getX(), delete_button.getY() + delete_button.getHeight() + keypad.get_button_h_offset(), cancel_button.getWidth(), cancel_button.getHeight());
	enter_button.setPosition(cancel_button.getX(), cancel_button.getY() + cancel_button.getHeight() + keypad.get_button_h_offset(), enter_button.getWidth(), enter_button.getHeight());
	command_box.setPosition(keypad_image.getX() - (command_box.getWidth() - keypad_image.getWidth())/2, keypad_image.getY(), command_box.getWidth(), command_box.getHeight());

	dummy_function_name_center.setWideTextAction(WIDE_TEXT_WORDWRAP);
	dummy_function_name_1.setVisible(false);
	dummy_function_name_center.setVisible(false);
	dummy_function_name_2.setVisible(false);

	command_page.add(keypad);
	keypad.setVisible(true);
	keypad.invalidate();
}

void main_screenView::tearDownScreen()
{
    main_screenViewBase::tearDownScreen();
    HAL::getInstance()->setFrameRateCompensation(false);
}

void main_screenView:: handleTickEvent()
{
	if(keypad_animation_state != 0)
	{
		animation_tick++;

		int16_t delta_alpha = EasingEquations::cubicEaseInOut(animation_tick, 0, 255, KEYPAD_ANIMATION_DURATION);
		int16_t delta_x_keypad = EasingEquations::cubicEaseInOut(animation_tick, 0, 443, KEYPAD_ANIMATION_DURATION);
		int16_t function_title_x = EasingEquations::cubicEaseInOut(animation_tick, 273, 494 - 273, KEYPAD_ANIMATION_DURATION);
		int16_t delta_y_function_name = EasingEquations::cubicEaseInOut(animation_tick, 132, function_wheel.getY() - 132, KEYPAD_ANIMATION_DURATION);
		int16_t delta_h_function_name = EasingEquations::cubicEaseInOut(animation_tick, 50, function_wheel.getHeight() - 50, KEYPAD_ANIMATION_DURATION);
		int16_t delta_y_function_background = EasingEquations::cubicEaseInOut(animation_tick, 129, function_wheel.getY() - 129, KEYPAD_ANIMATION_DURATION);
		int16_t delta_h_function_background = EasingEquations::cubicEaseInOut(animation_tick, 55, function_wheel.getHeight() - 55, KEYPAD_ANIMATION_DURATION);

				if(keypad_animation_state == KEYPAD_ANIMATION_IN_STEP_0)
		{
			if(animation_tick < KEYPAD_ANIMATION_DURATION)
			{
				if(function_wheel.isVisible())
				{
					function_wheel.setVisible(false);
					dummy_function_name_1.setVisible(true);
					dummy_function_name_center.setVisible(true);
					dummy_function_name_2.setVisible(true);
				}

				dummy_background_1.setAlpha(255-delta_alpha);
				dummy_function_name_1.setAlpha(255-delta_alpha);
				dummy_background_2.setAlpha(255-delta_alpha);
				dummy_function_name_2.setAlpha(255-delta_alpha);

				dummy_background_1.invalidate();
				dummy_function_name_1.invalidate();
				dummy_background_2.invalidate();
				dummy_function_name_2.invalidate();

				function_select_button.setAlpha(255-delta_alpha);
				button_text.setAlpha(255-delta_alpha);

				function_select_button.invalidate();
				button_text.invalidate();
			}
			else
			{
				keypad_animation_state = KEYPAD_ANIMATION_IN_STEP_1;
				animation_tick = 0;
			}
		}
		else if(keypad_animation_state == KEYPAD_ANIMATION_IN_STEP_1)
		{
			if(animation_tick < KEYPAD_ANIMATION_DURATION)
			{
				keypad_image.moveTo(-418 + delta_x_keypad, keypad_image.getY());
				keypad.moveTo(keypad_image.getX(), keypad.getY());
				delete_button.moveTo(keypad_image.getX() + keypad_image.getWidth() + keypad.get_button_w_offset(), keypad_image.getY() + keypad.get_text_offset());
				cancel_button.moveTo(delete_button.getX(), delete_button.getY() + delete_button.getHeight() + keypad.get_button_h_offset());
				enter_button.moveTo(cancel_button.getX(), cancel_button.getY() + cancel_button.getHeight() + keypad.get_button_h_offset());
				command_box.moveTo(keypad_image.getX() - (command_box.getWidth() - keypad_image.getWidth()) / 2 , keypad_image.getY());

				dummy_function_name_center.moveTo(25 + delta_x_keypad, delta_y_function_name);
				dummy_function_name_center.setWidthHeight(750 - delta_x_keypad, delta_h_function_name);
				dummy_background_center.moveTo(25 + delta_x_keypad, delta_y_function_background);
				dummy_background_center.setWidthHeight(750 - delta_x_keypad, delta_h_function_background);
				function_title.moveTo(function_title_x, function_title.getY());

				value_title.moveTo(45 + function_title_x, value_title.getY());
				value_text.moveTo(function_title_x - 25, value_text.getY());
				command_box_2.moveTo(function_title_x -25, command_box_2.getY());
			}
			else
			{
				keypad_animation_state = KEYPAD_ANIMATION_READY;
				animation_tick = 0;
			}
		}
		else if(keypad_animation_state == KEYPAD_ANIMATION_OUT_STEP_0)
		{
			if(animation_tick < KEYPAD_ANIMATION_DURATION)
			{
				keypad_image.moveTo(25 - delta_x_keypad, keypad_image.getY());
				keypad.moveTo(keypad_image.getX(), keypad.getY());
				delete_button.moveTo(keypad_image.getX() + keypad_image.getWidth() + keypad.get_button_w_offset(), keypad_image.getY() + keypad.get_text_offset());
				cancel_button.moveTo(delete_button.getX(), delete_button.getY() + delete_button.getHeight() + keypad.get_button_h_offset());
				enter_button.moveTo(cancel_button.getX(), cancel_button.getY() + cancel_button.getHeight() + keypad.get_button_h_offset());
				command_box.moveTo(keypad_image.getX() - (command_box.getWidth() - keypad_image.getWidth()) / 2 , keypad_image.getY());

				dummy_function_name_center.moveTo(468 - delta_x_keypad, 132 + 74 - delta_y_function_name);
				dummy_function_name_center.setWidthHeight(307 + delta_x_keypad, 215 - delta_h_function_name);
				dummy_background_center.moveTo(468 - delta_x_keypad, 129 + 74 - delta_y_function_background);
				dummy_background_center.setWidthHeight(307 + delta_x_keypad, 220 - (delta_h_function_background));
				function_title.moveTo(273 + 494 - function_title_x, function_title.getY());

				value_title.moveTo(45 + (273 + 494 - function_title_x), value_title.getY());
				value_text.moveTo((273 + 494 - function_title_x) - 25, value_text.getY());
				command_box_2.moveTo((273 + 494 - function_title_x) - 25, command_box_2.getY());
			}
			else
			{
				keypad_animation_state = KEYPAD_ANIMATION_OUT_STEP_1;
				animation_tick = 0;
			}
		}
		else if(keypad_animation_state == KEYPAD_ANIMATION_OUT_STEP_1)
		{
			if(animation_tick < KEYPAD_ANIMATION_DURATION)
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
				if(!function_wheel.isVisible())
				{
					function_wheel.setVisible(true);
					dummy_function_name_1.setVisible(false);
					dummy_function_name_center.setVisible(false);
					dummy_function_name_2.setVisible(false);

					function_wheel.invalidate();
				}
				keypad_animation_state = KEYPAD_ANIMATION_READY;
				animation_tick = 0;
			}
		}
	}
}

void main_screenView::execute_function_pressed()
{
	switch(function_wheel.getSelectedItem())
	{
	case 0:
		// Set throttle sensitivity
		keypad_animation_state = KEYPAD_ANIMATION_IN_STEP_0;
		break;
	case 1:
		// Set brake sensitivity
		keypad_animation_state = KEYPAD_ANIMATION_IN_STEP_0;
		break;
	case 2:
		// Calibrate throttle sensor
		// change to calibration screen
		break;
	case 3:
		// Set motor CAN transmit frequency
		keypad_animation_state = KEYPAD_ANIMATION_IN_STEP_0;
		break;
	case 4:
		// Calibrate brake sensor
		// change to calibration screen
		break;
	case 5:
		// Create new User
		// change to user screen
		break;
	case 6:
		// Edit User
		// change to user screen
		break;
	default:
		break;
	}
}

// ease_out_keypad (keypad_animation_state = -1;

void main_screenView::delete_char()
{
	keypad.delete_char();
}

void main_screenView::enter_command()
{
	// define what happens when the enter button is pressed for the keypad
	//display the current value of the command in question
	keypad_animation_state = KEYPAD_ANIMATION_OUT_STEP_0;
	Unicode::strncpy(value_textBuffer, keypad.getBuffer(), VALUE_TEXT_SIZE);
	value_text.invalidate();
}

void main_screenView::cancel_command()
{
	//display the current value of the command in question
	keypad_animation_state = KEYPAD_ANIMATION_OUT_STEP_0;
	Unicode::strncpy(value_textBuffer, keypad.getBuffer(), VALUE_TEXT_SIZE);
	value_text.invalidate();
}

void main_screenView::function_wheelUpdateItem(function_element& item, int16_t itemIndex)
{
    switch (itemIndex)
    {
    case 0:
        item.setupElement(T_FUNCTION_0);
        break;
    case 1:
    	item.setupElement(T_FUNCTION_1);
        break;
    case 2:
    	item.setupElement(T_FUNCTION_2);
        break;
    case 3:
    	item.setupElement(T_FUNCTION_3);
        break;
    case 4:
    	item.setupElement(T_FUNCTION_4);
        break;
    case 5:
    	item.setupElement(T_FUNCTION_5);
        break;
    case 6:
    	item.setupElement(T_FUNCTION_6);
        break;
    default:
        break;
    }
}

void main_screenView::function_wheelUpdateCenterItem(function_center& item, int16_t itemIndex)
{
    switch (itemIndex)
    {
    case 0:
        item.setupElement(T_FUNCTION_0);

        break;
    case 1:
    	item.setupElement(T_FUNCTION_1);

        break;
    case 2:
		item.setupElement(T_FUNCTION_2);

		break;
	case 3:
		item.setupElement(T_FUNCTION_3);

		break;
	case 4:
		item.setupElement(T_FUNCTION_4);

		break;
	case 5:
		item.setupElement(T_FUNCTION_5);

		break;
	case 6:
		item.setupElement(T_FUNCTION_6);
		break;
	default:
		break;
	}
}

void main_screenView::scrollWheelSelectedItemHandler()
{
	// Show the value of the parameter
    switch (function_wheel.getSelectedItem())
    {
    case 0:
    	// Set throttle sensitivity
    	dummy_function_name_1.setTypedText(touchgfx::TypedText(T_FUNCTION_6));
    	dummy_function_name_center.setTypedText(touchgfx::TypedText(T_FUNCTION_0));
    	dummy_function_name_2.setTypedText(touchgfx::TypedText(T_FUNCTION_1));

    	dummy_function_name_1.invalidate();
        dummy_function_name_center.invalidate();
        dummy_function_name_2.invalidate();
#ifndef SIMULATOR
    	Unicode::snprintf(value_textBuffer, VALUE_TEXT_SIZE, "%i", threshold);
#endif //SIMULATOR
        break;
    case 1:
    	// Set brake sensitivity
    	dummy_function_name_1.setTypedText(touchgfx::TypedText(T_FUNCTION_0));
    	dummy_function_name_center.setTypedText(touchgfx::TypedText(T_FUNCTION_1));
    	dummy_function_name_2.setTypedText(touchgfx::TypedText(T_FUNCTION_2));

    	dummy_function_name_1.invalidate();
		dummy_function_name_center.invalidate();
		dummy_function_name_2.invalidate();
        break;
    case 2:
    	// Calibrate throttle sensitivity
    	dummy_function_name_1.setTypedText(touchgfx::TypedText(T_FUNCTION_1));
		dummy_function_name_center.setTypedText(touchgfx::TypedText(T_FUNCTION_2));
		dummy_function_name_2.setTypedText(touchgfx::TypedText(T_FUNCTION_3));

    	dummy_function_name_1.invalidate();
		dummy_function_name_center.invalidate();
		dummy_function_name_2.invalidate();

		// Display the raw throttle sensor analog value
        break;
    case 3:
    	// Set motor CAN transmit frequency
    	dummy_function_name_1.setTypedText(touchgfx::TypedText(T_FUNCTION_2));
		dummy_function_name_center.setTypedText(touchgfx::TypedText(T_FUNCTION_3));
		dummy_function_name_2.setTypedText(touchgfx::TypedText(T_FUNCTION_4));

    	dummy_function_name_1.invalidate();
		dummy_function_name_center.invalidate();
		dummy_function_name_2.invalidate();
        break;
    case 4:
    	// Calibrate brake sensor
    	dummy_function_name_1.setTypedText(touchgfx::TypedText(T_FUNCTION_3));
		dummy_function_name_center.setTypedText(touchgfx::TypedText(T_FUNCTION_4));
		dummy_function_name_2.setTypedText(touchgfx::TypedText(T_FUNCTION_5));

    	dummy_function_name_1.invalidate();
		dummy_function_name_center.invalidate();
		dummy_function_name_2.invalidate();

		// Display the raw brake sensor analog value
        break;
    case 5:
    	// Create New User
    	dummy_function_name_1.setTypedText(touchgfx::TypedText(T_FUNCTION_4));
		dummy_function_name_center.setTypedText(touchgfx::TypedText(T_FUNCTION_5));
		dummy_function_name_2.setTypedText(touchgfx::TypedText(T_FUNCTION_6));

    	dummy_function_name_1.invalidate();
		dummy_function_name_center.invalidate();
		dummy_function_name_2.invalidate();

		Unicode::strncpy(value_textBuffer, "N/A", VALUE_TEXT_SIZE);
        break;
    case 6:
    	// Edit User
    	dummy_function_name_1.setTypedText(touchgfx::TypedText(T_FUNCTION_5));
		dummy_function_name_center.setTypedText(touchgfx::TypedText(T_FUNCTION_6));
		dummy_function_name_2.setTypedText(touchgfx::TypedText(T_FUNCTION_0));

    	dummy_function_name_1.invalidate();
		dummy_function_name_center.invalidate();
		dummy_function_name_2.invalidate();

		Unicode::strncpy(value_textBuffer, "N/A", VALUE_TEXT_SIZE);
        break;
    default:
        break;
    }
    value_text.invalidate();
}













#ifndef SIMULATOR
//For simulator - comment out motorDataStruct and set wildcard data to literal (e.x. replace motorDataStruct.fetTemp with 0)
void main_screenView::motorDataUpdate()
{
	Unicode::snprintf(fet_temp_wildBuffer, FET_TEMP_WILD_SIZE, "%d", motorDataStruct.fetTemp) ;
	Unicode::snprintf(motor_temp_wildBuffer, MOTOR_TEMP_WILD_SIZE, "%d", motorDataStruct.motorTemp);
	Unicode::snprintf(volt_in_wildBuffer, VOLT_IN_WILD_SIZE, "%d", motorDataStruct.voltIn);
	Unicode::snprintf(curr_in_wildBuffer, CURR_IN_WILD_SIZE, "%d", motorDataStruct.currIn);
	fet_temp_wild.invalidate();
	motor_temp_wild.invalidate();
	volt_in_wild.invalidate();
	curr_in_wild.invalidate();
}
#endif
