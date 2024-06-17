#ifndef MAIN_SCREENVIEW_HPP
#define MAIN_SCREENVIEW_HPP

#include <gui_generated/main_screen_screen/main_screenViewBase.hpp>
#include <gui/main_screen_screen/main_screenPresenter.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <gui/common/CustomKeyboard.hpp>

#include <touchgfx/Color.hpp>

class main_screenView : public main_screenViewBase
{
public:
    main_screenView();
    virtual ~main_screenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();

    enum KeypadAnimationState
    {
    	KEYPAD_ANIMATION_READY,
		KEYPAD_ANIMATION_IN_STEP_0,
		KEYPAD_ANIMATION_IN_STEP_1,
		KEYPAD_ANIMATION_OUT_STEP_0,
		KEYPAD_ANIMATION_OUT_STEP_1,
		KEYPAD_VALUE_SET_STEP_0,
		KEYPAD_VALUE_SET_STEP_1,
		CALIBRATION_IN_STEP_0,
		CALIBRATION_IN_STEP_1,
		CALIBRATION_OUT_STEP_0,
		CALIBRATION_OUT_STEP_1
    };

    // Command Page
    static const int KEYPAD_ANIMATION_DURATION = 40;
    static const int KEYPAD_ANIMATION_X_SIZE = 1;
    static const int KEYPAD_SET_ANIMATION_DURATION = 100;

	virtual void delete_char();
	virtual void enter_command();
	virtual void cancel_command();

	virtual void function_wheelUpdateItem(function_element& item, int16_t itemIndex);
	virtual void function_wheelUpdateCenterItem(function_center& item, int16_t itemIndex);
	virtual void execute_function_pressed();


    virtual void display_adc(unsigned int adc_value);


#ifndef SIMULATOR
     // Motor Data
     virtual void motorDataUpdate();
#endif

protected:
    // Command Page
    bool high_point;
    bool calibration_mode;
	float keypad_value_f;
	uint32_t keypad_value_d;


	uint32_t animation_tick;
	int8_t keypad_animation_state; // also defines the animation direction (-1, 1)

	Callback<main_screenView> scrollWheelSelectedItemCallback;
	void scrollWheelSelectedItemHandler();

	// Other Pages
	CustomKeyboard keypad;

};

#endif // MAIN_SCREENVIEW_HPP
