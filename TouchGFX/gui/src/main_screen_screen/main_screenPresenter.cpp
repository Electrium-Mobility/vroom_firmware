#include <gui/main_screen_screen/main_screenView.hpp>
#include <gui/main_screen_screen/main_screenPresenter.hpp>

main_screenPresenter::main_screenPresenter(main_screenView& v)
    : view(v)
{

}

void main_screenPresenter::activate()
{

}

void main_screenPresenter::deactivate()
{

}

void main_screenPresenter::display_adc(unsigned int adc_value)
{
	view.display_adc(adc_value);
}
