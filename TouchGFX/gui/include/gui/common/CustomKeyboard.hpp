#ifndef TGFXKEYBOARD_HPP_
#define TGFXKEYBOARD_HPP_

#include <touchgfx/widgets/Keyboard.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/KeyboardLayout.hpp>
#include <fonts/ApplicationFontProvider.hpp>
#include <gui/common/KeyboardKeyMapping.hpp>

#include <touchgfx/widgets/TextAreaWithWildcard.hpp>


using namespace touchgfx;


/**
 * An alphanumeric keyboard with backspace, space-bar and delete functionality.
 * Keyboard mappings for the keyboard are defined in gui/include/gui/common/KeyboardKeyMapping.hpp.
 * Keyboard layout for the keyboard is defined in gui/include/gui/common/KeyboardLayout.hpp.
 * Please note that the ApplicationFontProvider is initialized and set with the FontManager in main.cpp
 * The fonts and the characters used by the keyboard have to be defined in the assets/texts/texts.xlsx file.
 */

class CustomKeyboard : public Container
{
public:
    CustomKeyboard();
    virtual ~CustomKeyboard() { }

    /*
     * Override setTouchable to also affect the keyboard object inside this
     * CustomKeyboard.
     */
    void setTouchable(bool touch);

    Unicode::UnicodeChar *getBuffer ();
    virtual void clearBuffer ();
    void set_keyboard_visible(bool visibility);
    uint16_t getBufferPosition();
	void delete_char();
	uint8_t get_command();
	float get_command_input();


    /*
     * The size of the buffer that is used by the keyboard.
     * The size determines how much text the keyboard can contain in its textfield.
     */
    static const uint8_t BUFFER_SIZE = 9;

private:


    uint8_t decimal_pressed = 0;

    /**
     * The keyboard which this CustomKeyboard wraps.
     */
    Keyboard keyboard;

    /**
     * The buffer used by the keyboard for text input.
     */
    Unicode::UnicodeChar buffer[BUFFER_SIZE];

    /**
     * Callback for the backspace button.
     */
    Callback<CustomKeyboard> backspacePressed;
    /**
     * Callback for the enter button.
     */
    Callback<CustomKeyboard> enterPressed;
    /**
	 * Callback for the enter button.
	 */
	Callback<CustomKeyboard> equalsPressed;
	/**
	 * Callback for the enter button.
	 */
	Callback<CustomKeyboard> decimalPressed;
	/**
	 * Callback for when keys are pressed on the keyboard.
	 */
	Callback<CustomKeyboard, Unicode::UnicodeChar> keyPressed;

    /*
     * Sets the correct key mappings of the keyboard according to alpha/numeric and upper-case/lower-case.
     */
    void setKeyMappingList();

    /**
     * Callback handler for the backspace button.
     */
    void backspacePressedHandler();

    /**
     * Callback handler for the enter button.
     */
    void enterPressedHandler();

    /**
	 * Callback handler for the enter button.
	 */
	void equalsPressedHandler();

	/**
	 * Callback handler for the decimal button
	 */
	void decimalPressedHandler();

	/**
	 * Callback handler for key presses.
	 * @param keyChar The UnicodeChar for the key that was pressed.
	 */
	void keyPressedhandler(Unicode::UnicodeChar char_pressed);
};

#endif /* TGFXKEYBOARD_HPP_ */
