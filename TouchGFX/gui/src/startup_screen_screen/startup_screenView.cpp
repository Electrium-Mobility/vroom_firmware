#include <gui/startup_screen_screen/startup_screenView.hpp>
#include <touchgfx/EasingEquations.hpp>

startup_screenView::startup_screenView() :
		animation_state(STARTUP_STEP_0),
		animation_tick(0)
{

}

void startup_screenView::setupScreen()
{
	startup_screenViewBase::setupScreen();

	logo_cover.setVisible(true);
	logo_cover.setWidth(0);
}

void startup_screenView::tearDownScreen()
{
	startup_screenViewBase::tearDownScreen();
}

void startup_screenView::handleTickEvent()
{
	if (animation_state != ANIMATION_READY)
	{
		animation_tick++;

		if (animation_state == STARTUP_STEP_0)
		{
			if (animation_tick < ANIMATION_DURATION)
			{
				// Do nothing, Wait for a bit
			}
			else
			{
				animation_tick = 0;
				animation_state = STARTUP_STEP_1;
			}
		}
		else if (animation_state == STARTUP_STEP_1)
		{
			int16_t delta_x_bike = EasingEquations::cubicEaseInOut(animation_tick, 0, 775, MOTORCYCLE_ANIMATION_DURATION);
			uint8_t delta_color_16 = EasingEquations::cubicEaseInOut(animation_tick, 0, 0xFF - 0x49, MOTORCYCLE_ANIMATION_DURATION);
			uint8_t delta_color_8 = EasingEquations::cubicEaseInOut(animation_tick, 0, 0xFF - 0xB8, MOTORCYCLE_ANIMATION_DURATION);
			uint8_t delta_color_0 = EasingEquations::cubicEaseInOut(animation_tick, 0, 0xFF - 48, MOTORCYCLE_ANIMATION_DURATION);

			uint32_t color = ((0xFF - delta_color_16) << 16) + ((0xFF - delta_color_8) << 8) + (0xFF - delta_color_0);
			if (animation_tick < MOTORCYCLE_ANIMATION_DURATION)
			{
				// Move the bike across the screen and fade out the name
				bike_logo.moveTo(25 + delta_x_bike, bike_logo.getY());
				logo_cover.setWidth(delta_x_bike);
				logo_cover.invalidate();

				background.setColor(color);
				logo_cover.setColor(color);
				background.invalidate();
				logo_cover.invalidate();
			}
			else
			{
				// Change to the username password screen
				to_user_screen();
			}
		}
	}
}
