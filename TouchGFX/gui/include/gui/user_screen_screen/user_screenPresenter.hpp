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

    void get_password(int8_t user, char* password, uint8_t size)
	{
		model->get_password(user, password, size);
	}

	void get_username(int8_t user, char* username, uint8_t size)
	{
		model->get_username(user, username, size);
	}

	uint8_t get_num_users()
	{
		return model->get_num_users();
	}

private:
    user_screenPresenter();

    user_screenView& view;
};

#endif // USER_SCREENPRESENTER_HPP
