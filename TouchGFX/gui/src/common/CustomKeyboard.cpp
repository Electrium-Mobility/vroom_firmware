#include <gui/common/CustomKeyboard.hpp>
#include <string.h>
#include <touchgfx/Color.hpp>
#include <gui/main_screen_screen/main_screenView.hpp>
#include <stdlib.h>

CustomKeyboard::CustomKeyboard() : keyboard(),
	backspacePressed(this, &CustomKeyboard::backspacePressedHandler),
	decimalPressed(this, &CustomKeyboard::decimalPressedHandler),
	keyPressed(this, &CustomKeyboard::keyPressedhandler)
{
    //Set the callbacks for the callback areas of the keyboard and set its layout.
	layout.callbackAreaArray[0].callback = &backspacePressed;
	layout.callbackAreaArray[1].callback = &decimalPressed;

    keyboard.setKeyListener(keyPressed);
    keyboard.setLayout(&layout);
    keyboard.setPosition(0, 0, 308, 480);
    keyboard.setTextIndentation();

    //Allocate the buffer associated with keyboard.
    memset(buffer, 0, sizeof(buffer));
    keyboard.setBuffer(buffer, BUFFER_SIZE);
    setKeyMappingList();
    add(keyboard);
}

void CustomKeyboard::setKeyMappingList()
{
	keyboard.setKeymappingList(&keyMappingListNumLower);

}

void CustomKeyboard::delete_char()
{
	uint16_t pos = keyboard.getBufferPosition();
	if (pos > 0)
	{
		if(buffer[pos - 1] == keyMappingListNumLower.keyMappingArray[10].keyValue)
		{
			decimal_pressed = 0;
		}
		// Delete the previous entry in the buffer and decrement the position.
		buffer[pos - 1] = 0;
		keyboard.setBufferPosition(pos - 1);
	}
}

void CustomKeyboard::backspacePressedHandler()
{
    uint16_t pos = keyboard.getBufferPosition();
    if (pos > 0)
    {
    	if(buffer[pos - 1] == keyMappingListNumLower.keyMappingArray[10].keyValue)
    	{
    		decimal_pressed = 0;
    	}
        // Delete the previous entry in the buffer and decrement the position.
        buffer[pos - 1] = 0;
        keyboard.setBufferPosition(pos - 1);
    }
}

void CustomKeyboard:: decimalPressedHandler()
{
	uint16_t pos = keyboard.getBufferPosition();
	if(decimal_pressed || pos <= 0)
	{
		buffer[pos] = 0;
	}
	else
	{
		if(pos <= BUFFER_SIZE)
		{
			buffer[pos] = keyMappingListNumLower.keyMappingArray[10].keyValue;
			keyboard.setBufferPosition(pos + 1);
			decimal_pressed = 1;
		}
	}
}

void CustomKeyboard:: keyPressedhandler(Unicode::UnicodeChar char_pressed)
{
}

void CustomKeyboard::setTouchable(bool touch)
{
    Container::setTouchable(touch);
    keyboard.setTouchable(touch);
}

Unicode:: UnicodeChar* CustomKeyboard::getBuffer ()
{
	return keyboard.getBuffer();
}

uint16_t CustomKeyboard:: getBufferPosition()
{
	return keyboard.getBufferPosition();
}

void CustomKeyboard::clearBuffer ()
{
	memset(buffer, 0, BUFFER_SIZE+1);
	keyboard.setBufferPosition(0);
    setKeyMappingList();
}

void CustomKeyboard::set_keyboard_visible(bool visibility)
{
	keyboard.setVisible(visibility);
	keyboard.invalidate();
}

uint8_t CustomKeyboard:: get_command()
{
	Unicode::UnicodeChar command[2] = {buffer[0], buffer[1]};
	return Unicode::atoi(command);
}

float CustomKeyboard:: get_command_input()
{
	Unicode::UnicodeChar command[2] = {buffer[3], buffer[4]};
	return std::atof(reinterpret_cast<char*>(command));
}


uint16_t CustomKeyboard:: get_button_w_offset()
{
	return BUTTON_SPACE_W;
}

uint16_t CustomKeyboard:: get_button_h_offset()
{
	return BUTTON_SPACE_H;
}

uint16_t CustomKeyboard:: get_text_offset()
{
	return TEXT_OFFSET;
}
