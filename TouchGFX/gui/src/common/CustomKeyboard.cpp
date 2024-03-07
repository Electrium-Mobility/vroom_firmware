#include <gui/common/CustomKeyboard.hpp>
#include <string.h>
#include <touchgfx/Color.hpp>

CustomKeyboard::CustomKeyboard() : keyboard(),
	backspacePressed(this, &CustomKeyboard::backspacePressedHandler),
	enterPressed(this, &CustomKeyboard::enterPressedHandler)
{
    //Set the callbacks for the callback areas of the keyboard and set its layout.
	layout.callbackAreaArray[0].callback = &backspacePressed;
	layout.callbackAreaArray[1].callback = &enterPressed;
    keyboard.setLayout(&layout);
    keyboard.setPosition(0, 0, 418, 480);
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
void CustomKeyboard::backspacePressedHandler()
{
    uint16_t pos = keyboard.getBufferPosition();
    if (pos > 0)
    {
        //Delete the previous entry in the buffer and decrement the position.
        buffer[pos - 1] = 0;
        keyboard.setBufferPosition(pos - 1);

        //Change keymappings if we have reached the first position.
        if (1 == pos)
        {

        }
    }
}

void CustomKeyboard::enterPressedHandler()
{
	keyboard.setVisible(false);
	keyboard.invalidate();
}

// Implement keypressed handler to identify when a command has been input

void CustomKeyboard::setTouchable(bool touch)
{
    Container::setTouchable(touch);
    keyboard.setTouchable(touch);
}

Unicode:: UnicodeChar* CustomKeyboard::getBuffer ()
{
	return keyboard.getBuffer();
}

void CustomKeyboard::clearBuffer ()
{
	memset(buffer, 0, BUFFER_SIZE+1);
	keyboard.setBufferPosition(0);
    setKeyMappingList();
}
