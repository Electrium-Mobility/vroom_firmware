#ifndef STARTUP_SCREENPRESENTER_HPP
#define STARTUP_SCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class startup_screenView;

class startup_screenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    startup_screenPresenter(startup_screenView& v);

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

    virtual ~startup_screenPresenter() {}

private:
    startup_screenPresenter();

    startup_screenView& view;
};

#endif // STARTUP_SCREENPRESENTER_HPP
