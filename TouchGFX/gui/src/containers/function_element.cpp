#include <gui/containers/function_element.hpp>

function_element::function_element()
{

}

void function_element::initialize()
{
    function_elementBase::initialize();
}

void function_element::setupElement(TEXTS text)
{
    function_name.setTypedText(TypedText(text));
    function_name.setWideTextAction(WIDE_TEXT_WORDWRAP);
    //function_name.setBaselineY(26);
    function_name.invalidate();
}

void function_element::resize_widget(int16_t value)
{
	function_name.setWidth(value);
	background.setWidth(value);
}
