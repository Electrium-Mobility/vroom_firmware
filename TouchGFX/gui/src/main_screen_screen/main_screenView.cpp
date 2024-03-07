#include <gui/main_screen_screen/main_screenView.hpp>

main_screenView::main_screenView()
{
	keyboard.setPosition(300, 0, 418, 480);
	add(keyboard);
	keyboard.setVisible(false);
	keyboard.invalidate();
}

void main_screenView::setupScreen()
{
    main_screenViewBase::setupScreen();
}

void main_screenView::tearDownScreen()
{
    main_screenViewBase::tearDownScreen();
}

void main_screenView::command_button_clicked()
{
	keyboard.setVisible(true);
	keyboard.invalidate();
}
