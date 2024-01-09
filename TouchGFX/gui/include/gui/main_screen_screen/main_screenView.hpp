#ifndef MAIN_SCREENVIEW_HPP
#define MAIN_SCREENVIEW_HPP

#include <gui_generated/main_screen_screen/main_screenViewBase.hpp>
#include <gui/main_screen_screen/main_screenPresenter.hpp>

class main_screenView : public main_screenViewBase
{
public:
    main_screenView();
    virtual ~main_screenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // MAIN_SCREENVIEW_HPP
