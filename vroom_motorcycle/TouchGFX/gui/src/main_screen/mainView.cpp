#include <gui/main_screen/mainView.hpp>

mainView::mainView()
{

}

void mainView::setupScreen()
{
    mainViewBase::setupScreen();
}

void mainView::tearDownScreen()
{
    mainViewBase::tearDownScreen();
}

void mainView::handleTickEvent()
{
	speedometer.updateValue(speedometer.getValue() + 1, 0);
}
