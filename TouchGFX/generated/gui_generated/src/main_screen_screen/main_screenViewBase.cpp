/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/main_screen_screen/main_screenViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

main_screenViewBase::main_screenViewBase() :
    updateItemCallback(this, &main_screenViewBase::updateItemCallbackHandler),
    flexButtonCallback(this, &main_screenViewBase::flexButtonCallbackHandler),
    frameCountMotorDataUpdateInterval(0)
{
    __background.setPosition(0, 0, 800, 480);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    background.setXY(0, 0);
    background.setBitmap(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_BACKGROUNDS_800X480_LINES_ID));
    add(background);

    swipe_container.setXY(0, 0);
    swipe_container.setPageIndicatorBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_SWIPECONTAINER_MEDIUM_OFF_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_SWIPECONTAINER_MEDIUM_ON_ACTIVE_ID));
    swipe_container.setPageIndicatorXY(0, 0);
    swipe_container.setSwipeCutoff(50);
    swipe_container.setEndSwipeElasticWidth(50);

    command_page.setWidth(800);
    command_page.setHeight(480);
    value_set_background.setPosition(445, 240, 355, 239);
    value_set_background.setColor(touchgfx::Color::getColorFromRGB(0, 102, 153));
    value_set_background.setBorderColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    value_set_background.setBorderSize(5);
    value_set_background.setVisible(false);
    command_page.add(value_set_background);

    command_box.setPosition(-429, 6, 330, 70);
    command_box.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    command_box.setBorderColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    command_box.setBorderSize(3);
    command_page.add(command_box);

    command_box_2.setPosition(248, 395, 305, 70);
    command_box_2.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    command_box_2.setBorderColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    command_box_2.setBorderSize(3);
    command_page.add(command_box_2);

    keypad_image.setXY(-418, 0);
    keypad_image.setBitmap(touchgfx::Bitmap(BITMAP_KEYPAD_ID));
    command_page.add(keypad_image);

    function_title.setXY(273, 4);
    function_title.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    function_title.setLinespacing(0);
    function_title.setTypedText(touchgfx::TypedText(T___SINGLEUSE_W5VS));
    command_page.add(function_title);

    delete_button.setBitmaps(Bitmap(BITMAP_KEY_ID), Bitmap(BITMAP_KEY_PRESSED_ID));
    delete_button.setBitmapXY(0, 0);
    delete_button.setAction(flexButtonCallback);
    delete_button.setPosition(-89, 76, 89, 89);
    command_page.add(delete_button);

    value_title.setPosition(248, 315, 305, 72);
    value_title.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    value_title.setLinespacing(0);
    value_title.setTypedText(touchgfx::TypedText(T_VALUE_TITLE));
    command_page.add(value_title);

    cancel_button.setBitmaps(Bitmap(BITMAP_KEY_ID), Bitmap(BITMAP_KEY_PRESSED_ID));
    cancel_button.setBitmapXY(0, 0);
    cancel_button.setAction(flexButtonCallback);
    cancel_button.setPosition(-89, 180, 89, 89);
    command_page.add(cancel_button);

    enter_button.setBitmaps(Bitmap(BITMAP_KEY_2_ID), Bitmap(BITMAP_KEY_2_PRESSED_ID));
    enter_button.setBitmapXY(0, 0);
    enter_button.setAction(flexButtonCallback);
    enter_button.setPosition(-89, 287, 89, 192);
    command_page.add(enter_button);

    value_text.setPosition(248, 389, 305, 76);
    value_text.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    value_text.setLinespacing(0);
    Unicode::snprintf(value_textBuffer, VALUE_TEXT_SIZE, "%s", touchgfx::TypedText(T_VALUE_TEXT).getText());
    value_text.setWildcard(value_textBuffer);
    value_text.setTypedText(touchgfx::TypedText(T___SINGLEUSE_HU9G));
    command_page.add(value_text);

    function_select_button.setBoxWithBorderPosition(0, 0, 379, 55);
    function_select_button.setBorderSize(5);
    function_select_button.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    function_select_button.setAction(flexButtonCallback);
    function_select_button.setPosition(211, 260, 379, 55);
    command_page.add(function_select_button);

    button_text.setPosition(211, 260, 379, 55);
    button_text.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    button_text.setLinespacing(0);
    button_text.setTypedText(touchgfx::TypedText(T___SINGLEUSE_FPGL));
    command_page.add(button_text);

    dummy_background_center.setPosition(25, 129, 750, 55);
    dummy_background_center.setColor(touchgfx::Color::getColorFromRGB(163, 163, 163));
    command_page.add(dummy_background_center);

    dummy_function_name_center.setPosition(25, 132, 750, 50);
    dummy_function_name_center.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    dummy_function_name_center.setLinespacing(0);
    dummy_function_name_center.setTypedText(touchgfx::TypedText(T_FUNCTION_0));
    command_page.add(dummy_function_name_center);

    dummy_background_1.setPosition(25, 74, 750, 55);
    dummy_background_1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    command_page.add(dummy_background_1);

    dummy_background_2.setPosition(25, 184, 750, 55);
    dummy_background_2.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    command_page.add(dummy_background_2);

    dummy_function_name_1.setPosition(25, 73, 750, 50);
    dummy_function_name_1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    dummy_function_name_1.setLinespacing(0);
    dummy_function_name_1.setTypedText(touchgfx::TypedText(T_FUNCTION_6));
    command_page.add(dummy_function_name_1);

    dummy_function_name_2.setPosition(25, 185, 750, 50);
    dummy_function_name_2.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    dummy_function_name_2.setLinespacing(0);
    dummy_function_name_2.setTypedText(touchgfx::TypedText(T_FUNCTION_1));
    command_page.add(dummy_function_name_2);

    function_wheel.setPosition(25, 74, 750, 165);
    function_wheel.setHorizontal(false);
    function_wheel.setCircular(true);
    function_wheel.setEasingEquation(touchgfx::EasingEquations::backEaseOut);
    function_wheel.setSwipeAcceleration(10);
    function_wheel.setDragAcceleration(10);
    function_wheel.setNumberOfItems(7);
    function_wheel.setSelectedItemOffset(55);
    function_wheel.setSelectedItemExtraSize(0, 0);
    function_wheel.setSelectedItemMargin(0, 0);
    function_wheel.setDrawableSize(56, 0);
    function_wheel.setDrawables(function_wheelListItems, updateItemCallback,
    
                          function_wheelSelectedListItems, updateItemCallback);
    function_wheel.animateToItem(0, 0);
    command_page.add(function_wheel);

    swipe_container.add(command_page);

    motor_data.setWidth(800);
    motor_data.setHeight(480);
    diagnostics_title.setXY(221, 35);
    diagnostics_title.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    diagnostics_title.setLinespacing(0);
    diagnostics_title.setTypedText(touchgfx::TypedText(T___SINGLEUSE_L6ZD));
    motor_data.add(diagnostics_title);

    fet_temp_wild.setPosition(500, 138, 150, 36);
    fet_temp_wild.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    fet_temp_wild.setLinespacing(0);
    Unicode::snprintf(fet_temp_wildBuffer, FET_TEMP_WILD_SIZE, "%s", touchgfx::TypedText(T_VOLTIN).getText());
    fet_temp_wild.setWildcard(fet_temp_wildBuffer);
    fet_temp_wild.setTypedText(touchgfx::TypedText(T___SINGLEUSE_RJB5));
    motor_data.add(fet_temp_wild);

    motor_temp_wild.setPosition(500, 195, 150, 36);
    motor_temp_wild.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    motor_temp_wild.setLinespacing(0);
    Unicode::snprintf(motor_temp_wildBuffer, MOTOR_TEMP_WILD_SIZE, "%s", touchgfx::TypedText(T_VOLTIN).getText());
    motor_temp_wild.setWildcard(motor_temp_wildBuffer);
    motor_temp_wild.setTypedText(touchgfx::TypedText(T___SINGLEUSE_PAWH));
    motor_data.add(motor_temp_wild);

    curr_in_wild.setPosition(500, 315, 150, 36);
    curr_in_wild.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    curr_in_wild.setLinespacing(0);
    Unicode::snprintf(curr_in_wildBuffer, CURR_IN_WILD_SIZE, "%s", touchgfx::TypedText(T_VOLTIN).getText());
    curr_in_wild.setWildcard(curr_in_wildBuffer);
    curr_in_wild.setTypedText(touchgfx::TypedText(T___SINGLEUSE_3C6S));
    motor_data.add(curr_in_wild);

    volt_in_wild.setPosition(500, 252, 150, 36);
    volt_in_wild.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    volt_in_wild.setLinespacing(0);
    Unicode::snprintf(volt_in_wildBuffer, VOLT_IN_WILD_SIZE, "%s", touchgfx::TypedText(T_VOLTIN).getText());
    volt_in_wild.setWildcard(volt_in_wildBuffer);
    volt_in_wild.setTypedText(touchgfx::TypedText(T___SINGLEUSE_2KO1));
    motor_data.add(volt_in_wild);

    volt_in.setXY(200, 252);
    volt_in.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    volt_in.setLinespacing(0);
    volt_in.setTypedText(touchgfx::TypedText(T___SINGLEUSE_BX1B));
    motor_data.add(volt_in);

    curr_in.setXY(200, 315);
    curr_in.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    curr_in.setLinespacing(0);
    curr_in.setTypedText(touchgfx::TypedText(T___SINGLEUSE_1WUV));
    motor_data.add(curr_in);

    motor_temp.setXY(200, 195);
    motor_temp.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    motor_temp.setLinespacing(0);
    motor_temp.setTypedText(touchgfx::TypedText(T___SINGLEUSE_DGJ5));
    motor_data.add(motor_temp);

    fet_temp.setXY(200, 138);
    fet_temp.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    fet_temp.setLinespacing(0);
    fet_temp.setTypedText(touchgfx::TypedText(T___SINGLEUSE_5ZT6));
    motor_data.add(fet_temp);

    swipe_container.add(motor_data);

    swipe_container.setSelectedPage(0);
    add(swipe_container);
}

main_screenViewBase::~main_screenViewBase()
{

}

void main_screenViewBase::setupScreen()
{
    function_wheel.initialize();
    for (int i = 0; i < function_wheelListItems.getNumberOfDrawables(); i++)
    {
        function_wheelListItems[i].initialize();
    }
    for (int i = 0; i < function_wheelSelectedListItems.getNumberOfDrawables(); i++)
    {
        function_wheelSelectedListItems[i].initialize();
    }
}

void main_screenViewBase::flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src)
{
    if (&src == &function_select_button)
    {
        //execute_function_interraction
        //When function_select_button clicked call virtual function
        //Call execute_function_pressed
        execute_function_pressed();
    }
    if (&src == &delete_button)
    {
        //delete_interaction
        //When delete_button clicked call virtual function
        //Call delete_char
        delete_char();
    }
    if (&src == &enter_button)
    {
        //enter_interaction
        //When enter_button clicked call virtual function
        //Call enter_command
        enter_command();
    }
    if (&src == &cancel_button)
    {
        //cancel_interaction
        //When cancel_button clicked call virtual function
        //Call cancel_command
        cancel_command();
    }
}

void main_screenViewBase::handleTickEvent()
{
    frameCountMotorDataUpdateInterval++;
    if(frameCountMotorDataUpdateInterval == TICK_MOTORDATAUPDATE_INTERVAL)
    {
        //motorDataUpdate
        //When every N tick call virtual function
        //Call motorDataUpdate
        motorDataUpdate();
        frameCountMotorDataUpdateInterval = 0;
    }
}

void main_screenViewBase::updateItemCallbackHandler(touchgfx::DrawableListItemsInterface* items, int16_t containerIndex, int16_t itemIndex)
{
    if (items == &function_wheelListItems)
    {
        touchgfx::Drawable* d = items->getDrawable(containerIndex);
        function_element* cc = (function_element*)d;
        function_wheelUpdateItem(*cc, itemIndex);
    }
    if (items == &function_wheelSelectedListItems)
    {
        touchgfx::Drawable* d = items->getDrawable(containerIndex);
        function_center* cc = (function_center*)d;
        function_wheelUpdateCenterItem(*cc, itemIndex);
    }
}
