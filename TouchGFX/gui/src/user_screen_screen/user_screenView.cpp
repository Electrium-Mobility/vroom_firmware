#include <gui/user_screen_screen/user_screenView.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <gui/common/definitions.h>

user_screenView::user_screenView():
	animation_state(FADE_IN),
	user_icon_selected(true),
	animation_tick(0),
	user_input_mode(false),
	user(-1)
{

}

void user_screenView::setupScreen()
{
	user_screenViewBase::setupScreen();

	login_error_window.setVisible(true);
	login_error_window.hide();

	keyboard.setPosition(80, 480, 320*2, 240*2);
	add(keyboard);

	set_all_objects_alpha(0);
}

void user_screenView::tearDownScreen()
{
	user_screenViewBase::tearDownScreen();
}

void user_screenView:: handleTickEvent()
{
	if(animation_state != ANIMATION_READY)
	{
		animation_tick++;
		int16_t delta_alpha = EasingEquations::cubicEaseInOut(animation_tick, 0, 255, KEYBOARD_ANIMATION_DURATION);
		int16_t delta_y_keyboard = EasingEquations::cubicEaseInOut(animation_tick, 0, 480, KEYBOARD_ANIMATION_DURATION);
		int16_t delta_y_user = EasingEquations::cubicEaseInOut(animation_tick, 0, 171, KEYBOARD_ANIMATION_DURATION);
		int16_t delta_y_password = EasingEquations::cubicEaseInOut(animation_tick, 0, 268, KEYBOARD_ANIMATION_DURATION);

		int16_t delta_y_enter = EasingEquations::cubicEaseInOut(animation_tick, 0, 267, KEYBOARD_ANIMATION_DURATION);
		int16_t delta_x_enter = EasingEquations::cubicEaseInOut(animation_tick, 0, 311, KEYBOARD_ANIMATION_DURATION);
		int16_t delta_w_enter_password_view = EasingEquations::cubicEaseInOut(animation_tick, 0, 250, KEYBOARD_ANIMATION_DURATION);
		int16_t delta_h_enter = EasingEquations::cubicEaseInOut(animation_tick, 0, 284, KEYBOARD_ANIMATION_DURATION);

		int16_t delta_y_enter_icon = EasingEquations::cubicEaseInOut(animation_tick, 0, 125, KEYBOARD_ANIMATION_DURATION);
		int16_t delta_x_enter_icon = EasingEquations::cubicEaseInOut(animation_tick, 0, 186, KEYBOARD_ANIMATION_DURATION);


		int16_t delta_y_view_password = EasingEquations::cubicEaseInOut(animation_tick, 0, 383, KEYBOARD_ANIMATION_DURATION);
		int16_t delta_x_view_password = EasingEquations::cubicEaseInOut(animation_tick, 0, 659, KEYBOARD_ANIMATION_DURATION);
		int16_t delta_h_view_password = EasingEquations::cubicEaseInOut(animation_tick, 0, 36, KEYBOARD_ANIMATION_DURATION);

		if(animation_state == FADE_IN)
		{
			uint8_t fade_alpha = (uint8_t) EasingEquations::cubicEaseInOut(animation_tick, 0, 255, FADE_ANIMATION_DURATION);
			if(animation_tick < FADE_ANIMATION_DURATION)
			{
				set_all_objects_alpha(fade_alpha);
			}
			else
			{
				animation_tick = 0;
				animation_state = ANIMATION_READY;
			}
		}
		else if(animation_state == KEYBOARD_IN_STEP_0)
		{
			if(animation_tick < KEYBOARD_ANIMATION_DURATION)
			{
				// Fade out objects
				user_button.setAlpha(255 - delta_alpha);
				password_button.setAlpha(255 - delta_alpha);
				bike_logo.setAlpha(255 - delta_alpha);
				logo_background.setAlpha(255 - delta_alpha);
				username_text.setAlpha(255 - delta_alpha);
				password_text.setAlpha(255 - delta_alpha);
				view_password_title.setAlpha(255 - delta_alpha);

				user_button.invalidate();
				password_button.invalidate();
				bike_logo.invalidate();
				logo_background.invalidate();
				username_text.invalidate();
				password_text.invalidate();
				view_password_title.invalidate();

				// Fade out the necessary icon
				if(user_icon_selected)
				{
					password_icon.setAlpha(255 - delta_alpha);
					view_password_button.setAlpha(255 - delta_alpha);

					password_icon.invalidate();
					view_password_button.invalidate();
				}
				else
				{
					user_icon.setAlpha(255 - delta_alpha);
					user_icon.invalidate();
				}
			}
			else
			{
				user_button.setTouchable(false);
				password_button.setTouchable(false);
				animation_tick = 0;
				animation_state = KEYBOARD_IN_STEP_1;
			}
		}
		else if (animation_state == KEYBOARD_IN_STEP_1)
		{
			if(animation_tick < KEYBOARD_ANIMATION_DURATION)
			{
				// Move in the keyboard
				keyboard.moveTo(keyboard.getX(), 480 - delta_y_keyboard);

				// Move the enter button to the side
				enter_button.moveTo(409 + delta_x_enter, 383 - delta_y_enter);
				enter_button.setWidthHeight(330 - delta_w_enter_password_view, 80 + delta_h_enter);
				enter_button.setBoxWithBorderWidth(330 - delta_w_enter_password_view);
				enter_button.setBoxWithBorderHeight(80 + delta_h_enter);
				enter_button.invalidate();
				enter_icon.moveTo(544 + delta_x_enter_icon, 400 - delta_y_enter_icon);

				// Move up the icon
				if(user_icon_selected)
				{
					user_icon.moveTo(user_icon.getX(), 188 - delta_y_user);
				}
				else
				{
					password_icon.moveTo(password_icon.getX(), 285 - delta_y_password);

					// Move up the password_visibility button
					view_password_button.moveTo(61 + delta_x_view_password, 383 - delta_y_view_password);
					view_password_button.setWidthHeight(330 - delta_w_enter_password_view, 80 + delta_h_view_password);
					view_password_button.setBoxWithBorderWidth(330 - delta_w_enter_password_view);
					view_password_button.setBoxWithBorderHeight(80 + delta_h_view_password);
					view_password_button.invalidate();
				}
			}
			else
			{
				if(!user_icon_selected)
				{
					view_password_button.setTouchable(true);
				}
				animation_tick = 0;
				animation_state = ANIMATION_READY;
			}
		}
		else if (animation_state == KEYBOARD_OUT_STEP_0)
		{
			if(animation_tick < KEYBOARD_ANIMATION_DURATION)
			{
				// Move out the keyboard
				keyboard.moveTo(keyboard.getX(), delta_y_keyboard);

				// Move the enter button to the center
				enter_button.moveTo(720 - delta_x_enter, 116 + delta_y_enter);
				enter_button.setWidthHeight(80 + delta_w_enter_password_view, 364 - delta_h_enter);
				enter_button.setBoxWithBorderWidth(80 + delta_w_enter_password_view);
				enter_button.setBoxWithBorderHeight(364 - delta_h_enter);
				enter_button.invalidate();
				enter_icon.moveTo(730 - delta_x_enter_icon, 275 + delta_y_enter_icon);

				// Move down the icon
				if(user_icon_selected)
				{
					user_icon.moveTo(user_icon.getX(), 17 + delta_y_user);
				}
				else
				{
					password_icon.moveTo(password_icon.getX(), 17 + delta_y_password);

					// Move up the password_visibility button
					view_password_button.moveTo(720 - delta_x_view_password, 0 + delta_y_view_password);
					view_password_button.setWidthHeight(80 + delta_w_enter_password_view, 116 - delta_h_view_password);
					view_password_button.setBoxWithBorderWidth(80 + delta_w_enter_password_view);
					view_password_button.setBoxWithBorderHeight(116 - delta_h_view_password);
					view_password_button.invalidate();
				}
			}
			else
			{
				keyboard.reset_keyMappingList();
				animation_tick = 0;
				animation_state = KEYBOARD_OUT_STEP_1;
			}
		}
		else if (animation_state == KEYBOARD_OUT_STEP_1)
		{
			if(animation_tick < KEYBOARD_ANIMATION_DURATION)
			{
				// Fade in objects
				bike_logo.setAlpha(delta_alpha);
				logo_background.setAlpha(delta_alpha);
				user_button.setAlpha(delta_alpha);
				password_button.setAlpha(delta_alpha);
				username_text.setAlpha(delta_alpha);
				password_text.setAlpha(delta_alpha);
				view_password_title.setAlpha(delta_alpha);

				bike_logo.invalidate();
				logo_background.invalidate();
				user_button.invalidate();
				password_button.invalidate();
				username_text.invalidate();
				password_text.invalidate();
				view_password_title.invalidate();

				// Fade in the necessary icon
				if(user_icon_selected)
				{
					password_icon.setAlpha(delta_alpha);
					view_password_button.setAlpha(delta_alpha);
					password_icon.invalidate();
					view_password_button.invalidate();
				}
				else
				{
					user_icon.setAlpha(delta_alpha);
					user_icon.invalidate();
				}
			}
			else
			{
				user_button.setTouchable(true);
				password_button.setTouchable(true);
				user_input_mode = false;
				animation_tick = 0;
				animation_state = ANIMATION_READY;
			}

		}
		else if (animation_state == FADE_OUT)
		{
			uint8_t fade_alpha = (uint8_t) EasingEquations::cubicEaseInOut(animation_tick, 0, 255, FADE_ANIMATION_DURATION);
			if(animation_tick < KEYBOARD_ANIMATION_DURATION)
			{
				set_all_objects_alpha(255 - fade_alpha);
				background.setAlpha(255 - fade_alpha);
				background.invalidate();
			}
			else
			{
				to_main_screen();
			}
		}
	}
}

void user_screenView:: user_pressed()
{
	if(animation_state == ANIMATION_READY)
	{
		keyboard.set_buffer(false);
		keyboard.set_password_mode(false);

		user_icon_selected = true;
		animation_state = KEYBOARD_IN_STEP_0;
		user_input_mode = true;
	}
}

void user_screenView:: password_pressed()
{
	if(animation_state == ANIMATION_READY)
	{
		keyboard.set_buffer(true);
		keyboard.set_password_mode(true);

		user_icon_selected = false;
		user_input_mode = true;
		animation_state = KEYBOARD_IN_STEP_0;
	}
}

void user_screenView:: enter_pressed()
{
	if(animation_state == ANIMATION_READY)
	{
		if(user_input_mode)
		{
			animation_state = KEYBOARD_OUT_STEP_0;
			if(user_icon_selected)
			{
				Unicode::strncpy(username_textBuffer, keyboard.get_buffer(), USERNAME_TEXT_SIZE);
				username_text.invalidate();

				// This will increment the user variable accordingly
				user = check_usernames();
			}
			else
			{
				Unicode::strncpy(password_textBuffer, keyboard.get_buffer(), PASSWORD_TEXT_SIZE);
				password_text.invalidate();
			}
		}
		else
		{
			if(user != -1)
			{
				// check the credentials by calling get_password and get_buffer
				char char_password[16] = {};
				presenter->get_password(user, char_password, 16);
				Unicode::UnicodeChar password[16] = {};
				Unicode::strncpy(password, char_password, 16);
				if(Unicode::strncmp(keyboard.get_password(), password, 16) == 0)
				{
					// password successful
					animation_state = FADE_OUT;
				}
				else
				{
					// flag error
					login_error_window.show();
				}
			}
			else
			{
				// flag error
				login_error_window.show();
			}
		}
	}
}

void user_screenView:: toggle_password_visibility()
{
	bool password_visible = keyboard.toggle_password_visibility();
	if(!user_input_mode)
	{
		if(password_visible)
		{
			Unicode::strncpy(password_textBuffer, keyboard.get_password(), PASSWORD_TEXT_SIZE);
		}
		else
		{
			Unicode::strncpy(password_textBuffer, keyboard.get_buffer(), PASSWORD_TEXT_SIZE);
		}
		password_text.invalidate();
	}
}

unsigned short user_screenView:: check_usernames()
{
	for(uint8_t i = 0; i < presenter->get_num_users(); i++)
	{
		char char_username[16] = {};
		presenter->get_username(i, char_username, 16);
		Unicode::UnicodeChar username[16] = {};
		Unicode::strncpy(username, char_username, 16);

		if(Unicode::strncmp(keyboard.get_username(), username, 16) == 0)
		{
			return i;
		}
	}
	return -1;
}

void user_screenView:: set_all_objects_alpha(uint8_t delta_alpha)
{
	bike_logo.setAlpha(delta_alpha);
	logo_background.setAlpha(delta_alpha);
	user_button.setAlpha(delta_alpha);
	password_button.setAlpha(delta_alpha);
	username_text.setAlpha(delta_alpha);
	password_text.setAlpha(delta_alpha);
	view_password_title.setAlpha(delta_alpha);
	view_password_button.setAlpha(delta_alpha);
	enter_button.setAlpha(delta_alpha);
	enter_icon.setAlpha(delta_alpha);
	user_icon.setAlpha(delta_alpha);
	password_icon.setAlpha(delta_alpha);

	bike_logo.invalidate();
	logo_background.invalidate();
	user_button.invalidate();
	password_button.invalidate();
	username_text.invalidate();
	password_text.invalidate();
	view_password_title.invalidate();
	view_password_button.invalidate();
	enter_button.invalidate();
	enter_icon.invalidate();
	user_icon.invalidate();
	password_icon.invalidate();
}
