#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void set_throttle_high_point();
    void set_throttle_low_point();
    void set_brake_high_point();
    void set_brake_low_point();

    unsigned int get_throttle_sensitivity();
    void set_throttle_sensitivity(unsigned int throttle_value);
    unsigned int get_brake_sensitivity();
    void set_brake_sensitivity(unsigned int brake_value);
    unsigned int get_CAN_transmit_frequency();

    void start_throttle_adc();
    void start_brake_adc();
    void stop_adc_retrieval();

    void tick();

protected:
    ModelListener* modelListener;
    unsigned int adc_value;
};

#endif // MODEL_HPP
