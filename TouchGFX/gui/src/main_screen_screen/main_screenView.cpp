#include <gui/main_screen_screen/main_screenView.hpp>

#ifndef SIMULATOR
#include "motor.h"
#endif

main_screenView::main_screenView()
{
	keypad.setPosition(keypad_image.getX(), keypad_image.getY(), keypad_image.getWidth(), keypad_image.getHeight());
	command_page.add(keypad);
	keypad.setVisible(true);
	keypad.invalidate();
}

void main_screenView::setupScreen()
{
    main_screenViewBase::setupScreen();
}

void main_screenView::tearDownScreen()
{
    main_screenViewBase::tearDownScreen();
}

void main_screenView::check_value()
{
	//display the current value of the command in question
	Unicode::strncpy(value_textBuffer, keypad.getBuffer(), VALUE_TEXT_SIZE);
	value_text.invalidate();
}
void main_screenView::check_function()
{
	//clear the buffer
	//display the command name to the user
	Unicode::strncpy(function_textBuffer, keypad_command_names[keypad.get_command()], strlen(keypad_command_names[keypad.get_command()]));
	function_text.invalidate();

}

void main_screenView::delete_char()
{
	keypad.delete_char();
}

void main_screenView::enter_command()
{
	// define what happens when the enter button is pressed for the keypad
}

#ifndef SIMULATOR
//MotorDataStruct is for hardware
extern MotorData motorDataStruct;
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
