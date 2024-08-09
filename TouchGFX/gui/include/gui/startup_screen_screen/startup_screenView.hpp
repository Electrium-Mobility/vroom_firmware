#ifndef STARTUP_SCREENVIEW_HPP
#define STARTUP_SCREENVIEW_HPP

#include <gui_generated/startup_screen_screen/startup_screenViewBase.hpp>
#include <gui/startup_screen_screen/startup_screenPresenter.hpp>

class startup_screenView : public startup_screenViewBase
{
public:
    startup_screenView();
    virtual ~startup_screenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();

	enum AnimationState
	{
		ANIMATION_READY,
		STARTUP_STEP_0,
		STARTUP_STEP_1,
		STARTUP_STEP_2
	};

protected:
	AnimationState animation_state;
	uint32_t animation_tick;
};

#endif // STARTUP_SCREENVIEW_HPP
