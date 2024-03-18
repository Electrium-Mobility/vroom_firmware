#ifndef KEYBOARD_KEY_MAPPING_H
#define KEYBOARD_KEY_MAPPING_H

#include <touchgfx/widgets/Keyboard.hpp>
using namespace touchgfx;

/**
 * This file contains all the keymappings for the CustomKeyboard.
 */

static const Keyboard::KeyMapping keyMappingsNumLower[12] =
{
    { 1,  49},  // 1
    { 2,  50},  // 2
    { 3,  51},  // 3

    { 4,  52},  // 4
    { 5,  53},  // 5
    { 6,  54},  // 6

    { 7,  55},  // 7
    { 8,  56},  // 8
    { 9,  57},  // 9

    {10,  48},  // 0
    {11,  46},  // .
	{12,  58},  // :
};

static const Keyboard::KeyMappingList keyMappingListNumLower =
{
    keyMappingsNumLower,
    12
};

#endif
