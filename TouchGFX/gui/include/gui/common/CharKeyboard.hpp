#ifndef CHARKEYBOARD_HPP_
#define CHARKEYBOARD_HPP_

#include <touchgfx/widgets/Keyboard.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/CharKeyboardLayout.hpp>
#include <fonts/ApplicationFontProvider.hpp>
#include <gui/common/CharKeyboardKeyMapping.hpp>
#include <gui/common/definitions.h>

using namespace touchgfx;

/**
 * An alphanumeric keyboard with backspace, space-bar and delete functionality.
 * Keyboard mappings for the keyboard are defined in gui/include/gui/common/KeyboardKeyMapping.hpp.
 * Keyboard layout for the keyboard is defined in gui/include/gui/common/KeyboardLayout.hpp.
 * Please note that the ApplicationFontProvider is initialized and set with the FontManager in main.cpp
 * The fonts and the characters used by the keyboard have to be defined in the assets/texts/texts.xlsx file.
 */
class CharKeyboard : public Container
{
public:
    CharKeyboard();
    virtual ~CharKeyboard() { }

    /*
     * Override setTouchable to also affect the keyboard object inside this
     * CharKeyboard.
     */
    void setTouchable(bool touch);
    void set_password_mode(bool password_mode);

    void set_buffer(bool password_buffer);
    touchgfx::Unicode::UnicodeChar* get_password();
    void clear_password();
    touchgfx::Unicode::UnicodeChar* get_username();
    void clear_username();

    touchgfx::Unicode::UnicodeChar* get_buffer();

    void reset_keyMappingList();
    bool toggle_password_visibility();
    bool get_password_visibility();


private:
    /**
     * The keyboard which this CharKeyboard wraps.
     */
    Keyboard keyboard;

    /**
     * The buffer used by the keyboard for text input.
     */
    Unicode::UnicodeChar buffer[MIN_BUFFER_SIZE];

    /**
     * Used to display text on top of the button for changing keyboard mode.
     */
    TextArea modeBtnTextArea;

    /**
     * Callback for the capslock button.
     */
    Callback<CharKeyboard> capslockPressed;

    /**
     * Callback for the backspace button.
     */
    Callback<CharKeyboard> backspacePressed;

    /**
     * Callback for the keyboard mode button.
     */
    Callback<CharKeyboard> modePressed;

    /**
     * Callback for when keys are pressed on the keyboard.
     */
    Callback<CharKeyboard, Unicode::UnicodeChar> keyPressed;

    /**
     * True if the keyboard should show alpha keys, false for numeric.
     */
    bool alphaKeys;

    /**
     * True if the keyboard should show upper-case keys.
     */
    bool uppercaseKeys;

    /**
     * True if the input position in the text field, and hence the buffer, is at the beginning.
     */
    bool firstCharacterEntry;

    bool passwordMode;
    bool password_visibility;

    uint16_t password_buffer_position;
    Unicode::UnicodeChar password_buffer[PASSWORD_SIZE];

    uint16_t username_buffer_position;
    Unicode::UnicodeChar username_buffer[USERNAME_SIZE];

    /*
     * Sets the correct key mappings of the keyboard according to alpha/numeric and upper-case/lower-case.
     */
    void setKeyMappingList();

    /**
     * Callback handler for the backspace button.
     */
    void backspacePressedHandler();

    /**
     * Callback handler for the caps-lock button.
     */
    void capslockPressedHandler();

    /**
     * Callback handler for the mode button.
     */
    void modePressedHandler();

    /**
     * Callback handler for key presses.
     * @param keyChar The UnicodeChar for the key that was pressed.
     */
    void keyPressedhandler(Unicode::UnicodeChar keyChar);

};

#endif /* TGFXKEYBOARD_HPP_ */
