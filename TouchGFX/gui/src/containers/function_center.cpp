#include <gui/containers/function_center.hpp>

function_center::function_center() {

}

void function_center::initialize() {
	function_centerBase::initialize();
}

void function_center::setupElement(TEXTS text)
{
	function_name.setTypedText(TypedText(text));
	function_name.setWideTextAction(WIDE_TEXT_WORDWRAP);
	//function_name.setBaselineY(26);
	function_name.invalidate();
}

void function_center::set_alpha(uint8_t alpha)
{
	function_name.setAlpha(alpha);
	background.setAlpha(alpha);

	function_name.invalidate();
	background.invalidate();
}
