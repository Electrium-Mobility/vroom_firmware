#ifndef MAIN_SCREENPRESENTER_HPP
#define MAIN_SCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class main_screenView;

class main_screenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    main_screenPresenter(main_screenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~main_screenPresenter() {}


    virtual void display_adc(unsigned int adc_value);

    void set_user_screen_state(Model::UserScreenState state)
    {
    	model->set_user_screen_state(state);
    }

    uint8_t get_num_users()
    {
    	return model->get_num_users();
    }

    void set_throttle_high_point()
    {
    	model->set_throttle_high_point();
    }

    void set_throttle_low_point()
    {
    	model->set_throttle_low_point();
    }

    void set_brake_high_point()
    {
    	model->set_brake_high_point();
    }

    void set_brake_low_point()
    {
    	model->set_brake_low_point();
    }



    uint32_t get_throttle_sensitivity()
    {
    	return model->get_throttle_sensitivity();
    }

    void set_throttle_sensitivity(uint32_t throttle_value)
    {
    	model->set_throttle_sensitivity(throttle_value);
    }

    uint32_t get_brake_sensitivity()
    {
    	return model->get_brake_sensitivity();
    }

    void set_brake_sensitivity(uint32_t brake_value)
    {
    	model->set_brake_sensitivity(brake_value);
    }

    float get_CAN_transmit_frequency()
	{
		return model->get_CAN_transmit_frequency();
	}

    void set_CAN_transmit_frequency(float frequency_value)
    {
    	model->set_CAN_transmit_frequency(frequency_value);
    }

    void start_throttle_adc()
    {
    	return model->start_throttle_adc();
    }

    void start_brake_adc()
    {
    	return model->start_brake_adc();
    }

    void stop_adc_retrieval()
    {
    	model->stop_adc_retrieval();
    }

private:
    main_screenPresenter();

    main_screenView& view;
};

#endif // MAIN_SCREENPRESENTER_HPP
