#include <gui/main_screen_screen/main_screenView.hpp>
// #include "commands.hpp"

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
	//display the command name to the user
	Unicode::strncpy(function_textBuffer, keypad.getBuffer(), FUNCTION_TEXT_SIZE);
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
