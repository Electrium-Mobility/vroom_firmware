#ifndef FUNCTION_CENTER_HPP
#define FUNCTION_CENTER_HPP

#include <gui_generated/containers/function_centerBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class function_center : public function_centerBase
{
public:
    function_center();
    virtual ~function_center() {}

    virtual void initialize();

    virtual void setupElement(TEXTS text);

    void set_alpha(uint8_t alpha);

protected:
};

#endif // FUNCTION_CENTER_HPP
