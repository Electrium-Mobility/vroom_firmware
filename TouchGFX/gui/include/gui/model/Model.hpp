#ifndef MODEL_HPP
#define MODEL_HPP

#include <stdint.h>

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    enum UserScreenState
	{
    	LOGIN,
		EDIT,
		REMOVE,
		ADD,
	};

    void set_throttle_high_point();
    void set_throttle_low_point();
    void set_brake_high_point();
    void set_brake_low_point();

    uint32_t get_throttle_sensitivity();
    void set_throttle_sensitivity(uint32_t throttle_value);
    uint32_t get_brake_sensitivity();
    void set_brake_sensitivity(uint32_t brake_value);
    float get_CAN_transmit_frequency();
    void set_CAN_transmit_frequency(float frequency_value);

    void start_throttle_adc();
    void start_brake_adc();
    void stop_adc_retrieval();

    void get_username(int8_t user, uint8_t* username, uint8_t size);
    void get_password(int8_t user, uint8_t* password, uint8_t size);
    uint8_t get_num_users();
    void edit_username(uint8_t user, uint8_t* username);
    void edit_password(uint8_t user, uint8_t* password);
    void add_user(uint8_t* username, uint8_t* password);
    void remove_user(uint8_t user);

    UserScreenState get_user_screen_state();
    void set_user_screen_state(UserScreenState state);


    void tick();

protected:
    ModelListener* modelListener;
    unsigned int adc_value;
    UserScreenState user_screen_state;
};

#endif // MODEL_HPP
