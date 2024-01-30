#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <gui/common/CustomKeyboard.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    // added functions
    virtual void nameClicked();
    virtual void ageClicked();
    virtual void okClicked();
    virtual void exitClicked();
protected:

    CustomKeyboard keyboard;
    int namemod;
    int agemod;
};

#endif // SCREEN1VIEW_HPP
