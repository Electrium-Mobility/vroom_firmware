#include <gui/common/CustomKeyboard.hpp>
#include <string.h>
#include <touchgfx/Color.hpp>
#include <gui/main_screen_screen/main_screenView.hpp>

CustomKeyboard::CustomKeyboard() : keyboard(),
	backspacePressed(this, &CustomKeyboard::backspacePressedHandler),
	enterPressed(this, &CustomKeyboard::enterPressedHandler),
	equalsPressed(this, &CustomKeyboard::equalsPressedHandler),
	decimalPressed(this, &CustomKeyboard::decimalPressedHandler),
	keyPressed(this, &CustomKeyboard::keyPressedhandler)
{
    //Set the callbacks for the callback areas of the keyboard and set its layout.
	layout.callbackAreaArray[0].callback = &backspacePressed;
	layout.callbackAreaArray[1].callback = &enterPressed;
	layout.callbackAreaArray[2].callback = &equalsPressed;
	layout.callbackAreaArray[3].callback = &decimalPressed;
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
		//Delete the previous entry in the buffer and decrement the position.
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
        //Delete the previous entry in the buffer and decrement the position.
        buffer[pos - 1] = 0;
        keyboard.setBufferPosition(pos - 1);
    }
}

void CustomKeyboard::enterPressedHandler()
{
//	nothing happens, only implemented so that the button gets highlighted when clicked.
}

void CustomKeyboard::equalsPressedHandler()
{
	uint16_t pos = keyboard.getBufferPosition();
	if(pos != 2)
	{
		buffer[pos] = 0;
	}
	else
	{
		buffer[pos] = keyMappingListNumLower.keyMappingArray[11].keyValue;
		keyboard.setBufferPosition(pos + 1);

	}
}

void CustomKeyboard:: decimalPressedHandler()
{
	uint16_t pos = keyboard.getBufferPosition();
	if(decimal_pressed || pos <= 3)
	{
		buffer[pos] = 0;
	}
	else
	{
		if(pos <= BUFFER_SIZE - 2)
		{
			buffer[pos] = keyMappingListNumLower.keyMappingArray[10].keyValue;
			keyboard.setBufferPosition(pos + 1);
			decimal_pressed = 1;
		}
		else
		{
			buffer[pos] = 0;
		}
	}
}

void CustomKeyboard:: keyPressedhandler(Unicode::UnicodeChar char_pressed)
{
	// Commands are 2 characters, make sure you cannot input a larger command than is allowed
	uint16_t pos = keyboard.getBufferPosition();
	if(pos == 3 && (buffer[pos - 1] != keyMappingListNumLower.keyMappingArray[11].keyValue))
	{
		buffer[pos - 1] = 0;
		keyboard.setBufferPosition(pos - 1);
	}
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
