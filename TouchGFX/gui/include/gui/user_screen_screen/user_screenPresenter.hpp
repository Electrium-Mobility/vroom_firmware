#ifndef USER_SCREENPRESENTER_HPP
#define USER_SCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class user_screenView;

class user_screenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    user_screenPresenter(user_screenView& v);

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

    virtual ~user_screenPresenter() {}

private:
    user_screenPresenter();

    user_screenView& view;
};

#endif // USER_SCREENPRESENTER_HPP
