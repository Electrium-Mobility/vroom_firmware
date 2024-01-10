/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef MAIN_SCREENVIEWBASE_HPP
#define MAIN_SCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/main_screen_screen/main_screenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/SwipeContainer.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/containers/progress_indicators/CircleProgress.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/containers/progress_indicators/TextProgress.hpp>

class main_screenViewBase : public touchgfx::View<main_screenPresenter>
{
public:
    main_screenViewBase();
    virtual ~main_screenViewBase();
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Image image1;
    touchgfx::SwipeContainer swipe_container;
    touchgfx::Container motor_page;
    touchgfx::Button button1;
    touchgfx::Container main_page;
    touchgfx::CircleProgress battery_circle;
    touchgfx::PainterRGB565 battery_circlePainter;
    touchgfx::TextProgress battery_text;
    touchgfx::Container bms_page;
    touchgfx::Button button2;

private:

    /*
     * Canvas Buffer Size
     */
    static const uint32_t CANVAS_BUFFER_SIZE = 12000;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];

};

#endif // MAIN_SCREENVIEWBASE_HPP