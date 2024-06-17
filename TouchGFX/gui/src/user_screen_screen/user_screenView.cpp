#include <gui/user_screen_screen/user_screenView.hpp>
#include <touchgfx/EasingEquations.hpp>

user_screenView::user_screenView():
	animation_state(FADE_IN),
	user_icon_selected(true),
	animation_tick(0),
	user_input_mode(false)
{

}

void user_screenView::setupScreen()
{
	user_screenViewBase::setupScreen();

	keyboard.setPosition(80, 480, 320*2, 240*2);
	add(keyboard);
	bike_logo.setAlpha(0);
	logo_background.setAlpha(0);
	user_button.setAlpha(0);
	password_button.setAlpha(0);
	username.setAlpha(0);
	password.setAlpha(0);
	view_password_title.setAlpha(0);
	view_password_button.setAlpha(0);
	enter_button.setAlpha(0);
	enter_icon.setAlpha(0);
	user_icon.setAlpha(0);
	password_icon.setAlpha(0);

	bike_logo.invalidate();
	logo_background.invalidate();
	user_button.invalidate();
	password_button.invalidate();
	username.invalidate();
	password.invalidate();
	view_password_title.invalidate();
	view_password_button.invalidate();
	enter_button.invalidate();
	enter_icon.invalidate();
	user_icon.invalidate();
	password_icon.invalidate();
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
		int16_t delta_alpha = EasingEquations::cubicEaseInOut(animation_tick, 0, 255, ANIMATION_DURATION);
		int16_t delta_y_keyboard = EasingEquations::cubicEaseInOut(animation_tick, 0, 480, ANIMATION_DURATION);
		int16_t delta_y_user = EasingEquations::cubicEaseInOut(animation_tick, 0, 171, ANIMATION_DURATION);
		int16_t delta_y_password = EasingEquations::cubicEaseInOut(animation_tick, 0, 268, ANIMATION_DURATION);

		int16_t delta_y_enter = EasingEquations::cubicEaseInOut(animation_tick, 0, 267, ANIMATION_DURATION);
		int16_t delta_x_enter = EasingEquations::cubicEaseInOut(animation_tick, 0, 311, ANIMATION_DURATION);
		int16_t delta_w_enter_password_view = EasingEquations::cubicEaseInOut(animation_tick, 0, 250, ANIMATION_DURATION);
		int16_t delta_h_enter = EasingEquations::cubicEaseInOut(animation_tick, 0, 284, ANIMATION_DURATION);

		int16_t delta_y_enter_icon = EasingEquations::cubicEaseInOut(animation_tick, 0, 125, ANIMATION_DURATION);
		int16_t delta_x_enter_icon = EasingEquations::cubicEaseInOut(animation_tick, 0, 186, ANIMATION_DURATION);


		int16_t delta_y_view_password = EasingEquations::cubicEaseInOut(animation_tick, 0, 383, ANIMATION_DURATION);
		int16_t delta_x_view_password = EasingEquations::cubicEaseInOut(animation_tick, 0, 659, ANIMATION_DURATION);
		int16_t delta_h_view_password = EasingEquations::cubicEaseInOut(animation_tick, 0, 36, ANIMATION_DURATION);

		if(animation_state == FADE_IN)
		{
			if(animation_tick < ANIMATION_DURATION)
			{
				// Fade in all objects
				bike_logo.setAlpha(delta_alpha);
				logo_background.setAlpha(delta_alpha);
				user_button.setAlpha(delta_alpha);
				password_button.setAlpha(delta_alpha);
				username.setAlpha(delta_alpha);
				password.setAlpha(delta_alpha);
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
				username.invalidate();
				password.invalidate();
				view_password_title.invalidate();
				view_password_button.invalidate();
				enter_button.invalidate();
				enter_icon.invalidate();
				user_icon.invalidate();
				password_icon.invalidate();
			}
			else
			{
				animation_tick = 0;
				animation_state = ANIMATION_READY;
			}
		}
		else if(animation_state == KEYBOARD_IN_STEP_0)
		{
			if(animation_tick < ANIMATION_DURATION)
			{
				// Fade out objects
				user_button.setAlpha(255 - delta_alpha);
				password_button.setAlpha(255 - delta_alpha);
				bike_logo.setAlpha(255 - delta_alpha);
				logo_background.setAlpha(255 - delta_alpha);
				username.setAlpha(255 - delta_alpha);
				password.setAlpha(255 - delta_alpha);
				view_password_title.setAlpha(255 - delta_alpha);

				user_button.invalidate();
				password_button.invalidate();
				bike_logo.invalidate();
				logo_background.invalidate();
				username.invalidate();
				password.invalidate();
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
			if(animation_tick < ANIMATION_DURATION)
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
			if(animation_tick < ANIMATION_DURATION)
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
			if(animation_tick < ANIMATION_DURATION)
			{
				// Fade in objects
				bike_logo.setAlpha(delta_alpha);
				logo_background.setAlpha(delta_alpha);
				user_button.setAlpha(delta_alpha);
				password_button.setAlpha(delta_alpha);
				username.setAlpha(delta_alpha);
				password.setAlpha(delta_alpha);
				view_password_title.setAlpha(delta_alpha);

				bike_logo.invalidate();
				logo_background.invalidate();
				user_button.invalidate();
				password_button.invalidate();
				username.invalidate();
				password.invalidate();
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
	}
}

void user_screenView:: user_pressed()
{
	keyboard.set_buffer(false);
	keyboard.set_password_mode(false);

	user_icon_selected = true;
	animation_state = KEYBOARD_IN_STEP_0;
	user_input_mode = true;

}

void user_screenView:: password_pressed()
{
	keyboard.set_buffer(true);
	keyboard.set_password_mode(true);

	user_icon_selected = false;
	user_input_mode = true;
	animation_state = KEYBOARD_IN_STEP_0;

}

void user_screenView:: enter_pressed()
{
	if(user_input_mode)
	{
		animation_state = KEYBOARD_OUT_STEP_0;
		if(user_icon_selected)
		{
			Unicode::strncpy(usernameBuffer, keyboard.get_buffer(), USERNAME_SIZE);
			username.invalidate();
		}
		else
		{
			Unicode::strncpy(passwordBuffer, keyboard.get_buffer(), PASSWORD_SIZE);
			password.invalidate();
		}
	}
	else
	{
		// check the credentials by calling get_password and get_buffer
	}
}

void user_screenView:: toggle_password_visibility()
{
	bool password_visible = keyboard.toggle_password_visibility();
	if(!user_input_mode)
	{
		if(password_visible)
		{
			Unicode::strncpy(passwordBuffer, keyboard.get_password(), PASSWORD_SIZE);
		}
		else
		{
			Unicode::strncpy(passwordBuffer, keyboard.get_buffer(), PASSWORD_SIZE);
		}
		password.invalidate();
	}
}
