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

    enum AnimationState
	{
    	ANIMATION_READY,
    	FADE_IN,
		FADE_OUT,
	};

    enum KeypadAnimationState
    {
    	KEYPAD_ANIMATION_READY,
		KEYPAD_ANIMATION_IN_STEP_0,
		KEYPAD_ANIMATION_IN_STEP_1,
		KEYPAD_ANIMATION_OUT_STEP_0,
		KEYPAD_ANIMATION_OUT_STEP_1,
		KEYPAD_VALUE_SET_STEP_0,
		KEYPAD_VALUE_SET_STEP_1,
    };

    enum CalibrationAnimationState
	{
    	CALIBRATION_ANIMATION_READY,
    	CALIBRATION_IN_STEP_0,
		CALIBRATION_IN_STEP_1,
		CALIBRATION_OUT_STEP_0,
		CALIBRATION_OUT_STEP_1,
	};

    enum TransitionAnimationState
	{
    	TRANSITION_ANIMATION_READY,
    	FADE_VALUE_OBJECTS_IN,
		FADE_VALUE_OBJECTS_OUT,
		CHANGE_VALUE_WIDTH,
	};

    enum ListAnimationState
	{
    	LIST_ANIMATION_READY,
		LIST_IN_STEP_0,
		LIST_IN_STEP_1,
		LIST_OUT_STEP_0,
		LIST_OUT_STEP_1,
		LIST_VALUE_SET_STEP_0,
		LIST_VALUE_SET_STEP_1,

	};

    enum ListType
	{
    	DEFAULT,
		LANGUAGE,
	};

    // Command Page
	virtual void delete_char();
	virtual void enter_command();
	virtual void cancel_command();

	virtual void function_wheelUpdateItem(function_element& item, int16_t itemIndex);
	virtual void function_wheelUpdateCenterItem(function_center& item, int16_t itemIndex);
	TEXTS get_default_text(int16_t itemIndex);
	TEXTS get_language_text(int16_t itemIndex);

	virtual void execute_function_pressed();
	void execute_default_function();

	void set_diagnostic_objects_alpha(uint8_t delta_alpha);
	void set_function_objects_alpha(uint8_t delta_alpha);
	void handle_dummy_function_names(const TEXTS top_function, const TEXTS center_function, const TEXTS lower_function);
	void set_dummy_objects_alpha(uint8_t delta_alpha);
	void set_dummy_objects_visibility(bool visible);
	void set_value_objects(bool visible, uint16_t text_width);
	void display_current_language();
	void handle_list_type();

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
	uint16_t value_text_width;
	uint16_t prev_value_text_width;
	ListType list_type;

	uint32_t animation_tick;
	AnimationState animation_state;
	KeypadAnimationState keypad_animation_state; // also defines the animation direction (-1, 1)
	CalibrationAnimationState calibration_animation_state;
	TransitionAnimationState transition_animation_state;
	ListAnimationState list_animation_state;

	Callback<main_screenView> scrollWheelSelectedItemCallback;
	void scrollWheelSelectedItemHandler();
	void show_default_value();

	void refresh_function_wheel();

	// Other Pages
	CustomKeyboard keypad;

};

#endif // MAIN_SCREENVIEW_HPP
