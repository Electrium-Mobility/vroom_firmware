/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/function_elementBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>

function_elementBase::function_elementBase()
{
    setWidth(750);
    setHeight(56);
    background.setPosition(0, 0, 750, 56);
    background.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    add(background);

    function_name.setPosition(0, 0, 750, 56);
    function_name.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    function_name.setLinespacing(0);
    function_name.setTypedText(touchgfx::TypedText(T_FUNCTION_0));
    add(function_name);
}

function_elementBase::~function_elementBase()
{

}

void function_elementBase::initialize()
{

}
