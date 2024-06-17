#ifndef KEYBOARD_LAYOUT
#define KEYBOARD_LAYOUT

#include <touchgfx/widgets/Keyboard.hpp>
#include <touchgfx/hal/Types.hpp>
#include <fonts/ApplicationFontProvider.hpp>
#include "BitmapDatabase.hpp"

using namespace touchgfx;

/**
 * Array specifying the keys used in the CustomKeyboard.
 */
static const Keyboard::Key keyArray[30] =
{
    { 1, Rect(7*2, 61*2, 26*2, 40*2), BITMAP_TRANS_ID},
    { 2, Rect((7 + 28)*2, 61*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 3, Rect((7 + 28 * 2)*2, 61*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 4, Rect((7 + 28 * 3)*2, 61*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 5, Rect((7 + 28 * 4)*2, 61*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 6, Rect((7 + 28 * 5)*2, 61*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 7, Rect((7 + 28 * 6)*2, 61*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 8, Rect((7 + 28 * 7)*2, 61*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 9, Rect((7 + 28 * 8)*2, 61*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {10, Rect((7 + 28 * 9)*2, 61*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {11, Rect((7 + 28 * 10)*2, 61*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},

    {12, Rect(7*2, 105*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {13, Rect((7 + 28)*2, 105*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {14, Rect((7 + 28 * 2)*2, 105*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {15, Rect((7 + 28 * 3)*2, 105*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {16, Rect((7 + 28 * 4)*2, 105*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {17, Rect((7 + 28 * 5)*2, 105*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {18, Rect((7 + 28 * 6)*2, 105*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {19, Rect((7 + 28 * 7)*2, 105*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {20, Rect((7 + 28 * 8)*2, 105*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {21, Rect((7 + 28 * 9)*2, 105*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {22, Rect((7 + 28 * 10)*2, 105*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},

    {23, Rect(63*2, 149*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {24, Rect((63 + 28)*2, 149*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {25, Rect((63 + 28 * 2)*2, 149*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {26, Rect((63 + 28 * 3)*2, 149*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {27, Rect((63 + 28 * 4)*2, 149*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {28, Rect((63 + 28 * 5)*2, 149*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {29, Rect((63 + 28 * 6)*2, 149*2, 26*2, 40*2), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {30, Rect(62*2, 193*2, 252*2, 40*2), BITMAP_KEYBOARD_SPACE_HIGHLIGHTED_ID}
};

/**
 * Callback areas for the special buttons on the CustomKeyboard.
 */
static Keyboard::CallbackArea callbackAreas[3] =
{
    {Rect(5*2, 149*2, 56*2, 40*2), 0, BITMAP_KEYBOARD_KEY_SHIFT_HIGHLIGHTED_ID},     // caps-lock
    {Rect(258*2, 149*2, 56*2, 40*2), 0, BITMAP_KEYBOARD_KEY_DELETE_HIGHLIGHTED_ID},  // backspace
    {Rect(5*2, 193*2, 56*2, 40*2), 0, BITMAP_KEYBOARD_KEY_NUM_HIGHLIGHTED_ID},       // mode
};

/**
 * The layout for the CustomKeyboard.
 */
static const Keyboard::Layout layout =
{
    BITMAP_KEYBOARD_BACKGROUND_ID,
    keyArray,
    30,
    callbackAreas,
    3,
    Rect(15*2, 10*2, (11 * 28)*2, 40*2),
    TypedText(T_KEYBOARD_ENTERED_TEXT),
    0xFFFFFF,
    Typography::KEYBOARD,
    0
};

#endif
