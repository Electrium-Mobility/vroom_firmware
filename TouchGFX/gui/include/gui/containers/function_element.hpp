#ifndef FUNCTION_ELEMENT_HPP
#define FUNCTION_ELEMENT_HPP

#include <gui_generated/containers/function_elementBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class function_element : public function_elementBase
{
public:
    function_element();
    virtual ~function_element() {}

    virtual void initialize();

    virtual void setupElement(TEXTS text);

    virtual void resize_widget(int16_t value);
protected:
};

#endif // FUNCTION_ELEMENT_HPP
