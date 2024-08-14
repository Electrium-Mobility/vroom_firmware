#ifndef USER_SCREENVIEW_HPP
#define USER_SCREENVIEW_HPP

#include <gui_generated/user_screen_screen/user_screenViewBase.hpp>
#include <gui/user_screen_screen/user_screenPresenter.hpp>
#include <gui/common/CharKeyboard.hpp>

class user_screenView : public user_screenViewBase
{
public:
    user_screenView();
    virtual ~user_screenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();

    virtual void user_pressed();
    virtual void password_pressed();
    virtual void enter_pressed();
    virtual void toggle_password_visibility();
    int8_t check_usernames();
    void handle_valid_username_password();
    void handle_valid_username_invalid_password();
    void handle_invalid_username_password();

    void set_all_objects_alpha(uint8_t delta_alpha);

    enum AnimationState
	{
		ANIMATION_READY,
		FADE_IN,
		KEYBOARD_IN_STEP_0,
		KEYBOARD_IN_STEP_1,
		KEYBOARD_OUT_STEP_0,
		KEYBOARD_OUT_STEP_1,
		FADE_OUT,
	};

protected:
	CharKeyboard keyboard;
	AnimationState animation_state;
	bool user_icon_selected;
	uint32_t animation_tick;
	bool user_input_mode;
	int8_t user;
	uint8_t edit_user;
};

#endif // USER_SCREENVIEW_HPP
