/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Screen1ViewBase::Screen1ViewBase() :
    buttonCallback(this, &Screen1ViewBase::buttonCallbackHandler)
{

    __background.setPosition(0, 0, 800, 480);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    image1.setXY(0, 0);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_BLUE_BACKGROUNDS_MAIN_BG_800X480PX_ID));

    digitalClock1.setPosition(451, 36, 244, 65);
    digitalClock1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    digitalClock1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_KV0D));
    digitalClock1.displayLeadingZeroForHourIndicator(true);
    digitalClock1.setDisplayMode(touchgfx::DigitalClock::DISPLAY_24_HOUR);
    digitalClock1.setTime24Hour(10, 10, 0);

    textAreaDate.setXY(188, 36);
    textAreaDate.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textAreaDate.setLinespacing(0);
    touchgfx::Unicode::snprintf(textAreaDateBuffer1, TEXTAREADATEBUFFER1_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_WQ25).getText());
    textAreaDate.setWildcard1(textAreaDateBuffer1);
    touchgfx::Unicode::snprintf(textAreaDateBuffer2, TEXTAREADATEBUFFER2_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_SZDE).getText());
    textAreaDate.setWildcard2(textAreaDateBuffer2);
    textAreaDate.resizeToCurrentText();
    textAreaDate.setTypedText(touchgfx::TypedText(T___SINGLEUSE_IQ9Q));

    textAreaYear.setXY(11, 36);
    textAreaYear.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textAreaYear.setLinespacing(0);
    Unicode::snprintf(textAreaYearBuffer, TEXTAREAYEAR_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_YQUF).getText());
    textAreaYear.setWildcard(textAreaYearBuffer);
    textAreaYear.resizeToCurrentText();
    textAreaYear.setTypedText(touchgfx::TypedText(T___SINGLEUSE_P4UU));

    imageNetworkFalse.setXY(712, 37);
    imageNetworkFalse.setBitmap(touchgfx::Bitmap(BITMAP_NOWIFI_ID));

    imageNetworkTrue.setXY(712, 36);
    imageNetworkTrue.setVisible(false);
    imageNetworkTrue.setBitmap(touchgfx::Bitmap(BITMAP_WIFI_ID));

    textArea1.setXY(400, 240);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_L1NF));

    textArea2.setXY(40, 417);
    textArea2.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea2.setLinespacing(0);
    textArea2.setTypedText(touchgfx::TypedText(T___SINGLEUSE_KEIF));

    textArea3.setXY(40, 240);
    textArea3.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea3.setLinespacing(0);
    textArea3.setTypedText(touchgfx::TypedText(T___SINGLEUSE_B5SM));

    textArea4.setXY(400, 417);
    textArea4.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea4.setLinespacing(0);
    textArea4.setTypedText(touchgfx::TypedText(T___SINGLEUSE_IREN));

    imageTEMP.setXY(16, 112);
    imageTEMP.setBitmap(touchgfx::Bitmap(BITMAP_TEMP_ID));

    imageHUM.setXY(375, 112);
    imageHUM.setBitmap(touchgfx::Bitmap(BITMAP_HUM_ID));

    imagepreesure.setXY(16, 303);
    imagepreesure.setBitmap(touchgfx::Bitmap(BITMAP_PRESSURE_ID));

    textAreaTemp.setXY(150, 150);
    textAreaTemp.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textAreaTemp.setLinespacing(0);
    Unicode::snprintf(textAreaTempBuffer, TEXTAREATEMP_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_YJRI).getText());
    textAreaTemp.setWildcard(textAreaTempBuffer);
    textAreaTemp.resizeToCurrentText();
    textAreaTemp.setTypedText(touchgfx::TypedText(T___SINGLEUSE_G3XM));

    textAreaHum.setXY(524, 150);
    textAreaHum.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textAreaHum.setLinespacing(0);
    Unicode::snprintf(textAreaHumBuffer, TEXTAREAHUM_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_EZDK).getText());
    textAreaHum.setWildcard(textAreaHumBuffer);
    textAreaHum.resizeToCurrentText();
    textAreaHum.setTypedText(touchgfx::TypedText(T___SINGLEUSE_A89S));

    textAreaPresssure.setXY(150, 308);
    textAreaPresssure.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textAreaPresssure.setLinespacing(0);
    Unicode::snprintf(textAreaPresssureBuffer, TEXTAREAPRESSSURE_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_KFEL).getText());
    textAreaPresssure.setWildcard(textAreaPresssureBuffer);
    textAreaPresssure.resizeToCurrentText();
    textAreaPresssure.setTypedText(touchgfx::TypedText(T___SINGLEUSE_C1Y0));

    textArea7.setXY(290, 191);
    textArea7.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea7.setLinespacing(0);
    textArea7.setTypedText(touchgfx::TypedText(T___SINGLEUSE_PV86));

    textArea8.setXY(274, 392);
    textArea8.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea8.setLinespacing(0);
    textArea8.setTypedText(touchgfx::TypedText(T___SINGLEUSE_79ER));

    textArea9.setXY(605, 191);
    textArea9.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea9.setLinespacing(0);
    textArea9.setTypedText(touchgfx::TypedText(T___SINGLEUSE_UA88));

    textAreaLux.setXY(524, 308);
    textAreaLux.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textAreaLux.setLinespacing(0);
    Unicode::snprintf(textAreaLuxBuffer, TEXTAREALUX_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_E4VB).getText());
    textAreaLux.setWildcard(textAreaLuxBuffer);
    textAreaLux.resizeToCurrentText();
    textAreaLux.setTypedText(touchgfx::TypedText(T___SINGLEUSE_DMOZ));

    textArea11.setXY(590, 398);
    textArea11.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea11.setLinespacing(0);
    textArea11.setTypedText(touchgfx::TypedText(T___SINGLEUSE_1VUL));

    image2.setXY(375, 289);
    image2.setBitmap(touchgfx::Bitmap(BITMAP_LUX_ID));

    buttonWithIconControl.setXY(712, 233);
    buttonWithIconControl.setBitmaps(touchgfx::Bitmap(BITMAP_CONTROL_ID), touchgfx::Bitmap(BITMAP_CONTROL_ID), touchgfx::Bitmap(BITMAP_CONTROL_ID), touchgfx::Bitmap(BITMAP_CONTROL_ID));
    buttonWithIconControl.setIconXY(0, 0);
    buttonWithIconControl.setAction(buttonCallback);

    add(__background);
    add(image1);
    add(digitalClock1);
    add(textAreaDate);
    add(textAreaYear);
    add(imageNetworkFalse);
    add(imageNetworkTrue);
    add(textArea1);
    add(textArea2);
    add(textArea3);
    add(textArea4);
    add(imageTEMP);
    add(imageHUM);
    add(imagepreesure);
    add(textAreaTemp);
    add(textAreaHum);
    add(textAreaPresssure);
    add(textArea7);
    add(textArea8);
    add(textArea9);
    add(textAreaLux);
    add(textArea11);
    add(image2);
    add(buttonWithIconControl);
}

void Screen1ViewBase::setupScreen()
{

}

void Screen1ViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &buttonWithIconControl)
    {
        //Interaction1
        //When buttonWithIconControl clicked change screen to ScreenControl
        //Go to ScreenControl with screen transition towards East
        application().gotoScreenControlScreenSlideTransitionEast();
    }
}
