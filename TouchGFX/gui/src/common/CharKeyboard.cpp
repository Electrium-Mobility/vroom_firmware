#include <gui/common/CharKeyboard.hpp>
#include <string.h>
#include <touchgfx/Color.hpp>

CharKeyboard::CharKeyboard() : keyboard(),
    modeBtnTextArea(),
    capslockPressed(this, &CharKeyboard::capslockPressedHandler),
    backspacePressed(this, &CharKeyboard::backspacePressedHandler),
    modePressed(this, &CharKeyboard::modePressedHandler),
    keyPressed(this, &CharKeyboard::keyPressedhandler),
    alphaKeys(true),
    uppercaseKeys(false),
    firstCharacterEntry(false),
	passwordMode(false),
	password_visibility(false)
{
    //Set the callbacks for the callback areas of the keyboard and set its layout.
    layout.callbackAreaArray[0].callback = &capslockPressed;
    layout.callbackAreaArray[1].callback = &backspacePressed;
    layout.callbackAreaArray[2].callback = &modePressed;
    keyboard.setLayout(&layout);
    keyboard.setKeyListener(keyPressed);
    keyboard.setPosition(0, 0, 320*2, 240*2);
    keyboard.setTextIndentation();
    //Allocate the buffer associated with keyboard.
    memset(buffer, 0, sizeof(buffer));
    keyboard.setBuffer(buffer, BUFFER_SIZE);

    uppercaseKeys = true;
    firstCharacterEntry = true;

    modeBtnTextArea.setPosition(5*2, 196*2, 56*2, 40*2);
    modeBtnTextArea.setColor(Color::getColorFromRGB(0xFF, 0xFF, 0xFF));

    setKeyMappingList();

    add(keyboard);
    add(modeBtnTextArea);
}

void CharKeyboard::setKeyMappingList()
{
    if (alphaKeys)
    {
        modeBtnTextArea.setTypedText(TypedText(T_ALPHAMODE));
        if (uppercaseKeys)
        {
            keyboard.setKeymappingList(&keyMappingListAlphaUpper);
        }
        else
        {
            keyboard.setKeymappingList(&keyMappingListAlphaLower);
        }
    }
    else
    {
        modeBtnTextArea.setTypedText(TypedText(T_NUMMODE));
        if (uppercaseKeys)
        {
            keyboard.setKeymappingList(&keyMappingListNumUpper);
        }
        else
        {
            keyboard.setKeymappingList(&keyMappingListNumLower);
        }
    }
}

void CharKeyboard::backspacePressedHandler()
{
    uint16_t pos = keyboard.getBufferPosition();
    if (pos > 0)
    {
        //Delete the previous entry in the buffer and decrement the position.
    	if(passwordMode)
    	{
    		password_buffer[pos - 1] = 0;
    		password_buffer_position = pos - 1;
    	}
    	else
    	{
    		username_buffer[pos - 1] = 0;
    		username_buffer_position = pos - 1;
    	}
        buffer[pos - 1] = 0;
        keyboard.setBufferPosition(pos - 1);

        //Change keymappings if we have reached the first position.
        if (1 == pos)
        {
            firstCharacterEntry = true;
            uppercaseKeys = true;
            setKeyMappingList();
        }
    }
}

void CharKeyboard::capslockPressedHandler()
{
    uppercaseKeys = !uppercaseKeys;
    setKeyMappingList();
}

void CharKeyboard::modePressedHandler()
{
    alphaKeys = !alphaKeys;

    // if we have changed back to alpha and still has no chars in the buffer,
    // we show upper case letters.
    if (firstCharacterEntry && alphaKeys)
    {
        uppercaseKeys = true;
    }
    else
    {
        uppercaseKeys = false;
    }
    setKeyMappingList();
}

void CharKeyboard::keyPressedhandler(Unicode::UnicodeChar keyChar)
{
	if(keyChar != 0)
	{
		if(passwordMode)
		{
			password_buffer_position = keyboard.getBufferPosition();
			password_buffer[password_buffer_position - 1] = buffer[keyboard.getBufferPosition() - 1];

			if(password_visibility == false)
			{
				// Hide the characters
				buffer[keyboard.getBufferPosition() - 1] = 8226;
			}
		}
		else
		{
			username_buffer_position = keyboard.getBufferPosition();
			username_buffer[username_buffer_position - 1] = buffer[keyboard.getBufferPosition() - 1];
		}
	}

    // After the first keypress, the keyboard will shift to lowercase.
    if (firstCharacterEntry && keyChar != 0)
    {
        firstCharacterEntry = false;
        uppercaseKeys = false;
        setKeyMappingList();
    }
}

void CharKeyboard::setTouchable(bool touch)
{
    Container::setTouchable(touch);
    keyboard.setTouchable(touch);
}

void CharKeyboard::set_password_mode(bool password_mode)
{
	passwordMode = password_mode;
}

void CharKeyboard::set_buffer(bool password_mode)
{
	memset(buffer, 0, BUFFER_SIZE + 1);
	if(password_mode)
	{
		if(password_visibility == false)
		{
			for(int i = 0; i < password_buffer_position; i++)
			{
				buffer[i] = 8226; // this is the value for a dot
			}
		}
		else
		{
			for(int i = 0; i < BUFFER_SIZE; i++)
			{
				buffer[i] = password_buffer[i];
			}
		}
		keyboard.setBufferPosition(password_buffer_position);
		if(password_buffer_position == 0)
		{
			firstCharacterEntry = true;
			uppercaseKeys = true;
			setKeyMappingList();
		}
	}
	else
	{
		for(int i = 0; i < BUFFER_SIZE; i++)
		{
			buffer[i] = username_buffer[i];
		}
		keyboard.setBufferPosition(username_buffer_position);
		if(username_buffer_position == 0)
		{
			firstCharacterEntry = true;
			uppercaseKeys = true;
			setKeyMappingList();
		}
	}
}

touchgfx::Unicode::UnicodeChar* CharKeyboard::get_password()
{
	return password_buffer;
}

void CharKeyboard::clear_password()
{
	memset(password_buffer, 0, BUFFER_SIZE +1);
	password_buffer_position = 0;
}

touchgfx::Unicode::UnicodeChar* CharKeyboard::get_username()
{
	return username_buffer;
}

void CharKeyboard::clear_username()
{
	memset(username_buffer, 0, BUFFER_SIZE +1);
	username_buffer_position = 0;
}

touchgfx::Unicode::UnicodeChar* CharKeyboard::get_buffer()
{
	return buffer;
}

void CharKeyboard::reset_keyMappingList()
{
	alphaKeys = true;
	if(firstCharacterEntry)
	{
		uppercaseKeys = true;
	}
	else
	{
		uppercaseKeys = false;
	}
	setKeyMappingList();
}

bool CharKeyboard::toggle_password_visibility()
{
	password_visibility = !password_visibility;
	if(password_visibility == true)
	{
		for(int i = 0; i < BUFFER_SIZE; i++)
		{
			buffer[i] = password_buffer[i];
		}
	}
	else
	{
		for(int i = 0; i < password_buffer_position; i++)
		{
			buffer[i] = 8226;
		}
	}
	keyboard.invalidate();

	return password_visibility;
}

