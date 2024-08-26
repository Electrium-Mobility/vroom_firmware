#include <gui/main_screen_screen/main_screenView.hpp>
#include <gui/main_screen_screen/main_screenPresenter.hpp>

main_screenPresenter::main_screenPresenter(main_screenView &v) :
		view(v)
{

}

void main_screenPresenter::activate()
{

}

void main_screenPresenter::deactivate()
{

}

void main_screenPresenter::display_adc(volatile uint16_t* adc_data)
{
	view.display_adc(adc_data);
}

void main_screenPresenter::update_motor_data(motor_data_t *motor_data)
{
	view.update_motor_data(motor_data);
}
