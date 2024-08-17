#include <gui/containers/function_element.hpp>

function_element::function_element() {

}

void function_element::initialize() {
	function_elementBase::initialize();
}

void function_element::setupElement(TEXTS text)
{
	function_name.setTypedText(TypedText(text));
	function_name.setWideTextAction(WIDE_TEXT_WORDWRAP);
	//function_name.setBaselineY(26);
	function_name.invalidate();
}

void function_element::set_alpha(uint8_t alpha)
{
	function_name.setAlpha(alpha);
	background.setAlpha(alpha);

	function_name.invalidate();
	background.invalidate();
}
