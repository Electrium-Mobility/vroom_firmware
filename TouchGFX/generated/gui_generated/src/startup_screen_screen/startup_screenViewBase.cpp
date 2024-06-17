/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/startup_screen_screen/startup_screenViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>

startup_screenViewBase::startup_screenViewBase()
{
    __background.setPosition(0, 0, 800, 480);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    background.setPosition(0, 0, 800, 480);
    background.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    add(background);

    name_logo.setXY(184, 193);
    name_logo.setBitmap(touchgfx::Bitmap(BITMAP_ELECTRIUM_NAME_ID));
    add(name_logo);

    logo_cover.setPosition(184, 193, 591, 94);
    logo_cover.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    logo_cover.setVisible(false);
    add(logo_cover);

    bike_logo.setXY(25, 193);
    bike_logo.setBitmap(touchgfx::Bitmap(BITMAP_ELECTRIUM_BIKE_ID));
    add(bike_logo);
}

startup_screenViewBase::~startup_screenViewBase()
{

}

void startup_screenViewBase::setupScreen()
{

}

void startup_screenViewBase::to_user_screen()
{
    //to_user_screen_interaction
    //When to_user_screen is called change screen to user_screen
    //Go to user_screen with no screen transition
    application().gotouser_screenScreenNoTransition();
}