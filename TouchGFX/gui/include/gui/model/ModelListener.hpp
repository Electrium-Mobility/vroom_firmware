#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }
    virtual void display_adc(volatile uint16_t* adc_value) {}
    virtual void update_motor_data(motor_data_t* motor_data) {}

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
