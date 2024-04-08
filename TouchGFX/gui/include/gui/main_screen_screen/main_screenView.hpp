#ifndef MAIN_SCREENVIEW_HPP
#define MAIN_SCREENVIEW_HPP

#include <gui_generated/main_screen_screen/main_screenViewBase.hpp>
#include <gui/main_screen_screen/main_screenPresenter.hpp>
#include <gui/common/CustomKeyboard.hpp>
#include <gui/common/commands.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>

#include <touchgfx/Color.hpp>

class main_screenView : public main_screenViewBase
{
public:
    main_screenView();
    virtual ~main_screenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    /*
      * Virtual Action Handlers
      */
     virtual void check_value();
     virtual void check_function();
     virtual void delete_char();
     virtual void enter_command();
     virtual void motorDataUpdate();

protected:
	CustomKeyboard keypad;
};

#endif // MAIN_SCREENVIEW_HPP
