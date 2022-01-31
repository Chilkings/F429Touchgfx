#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class Screen1View : public Screen1ViewBase
{
		virtual void handleTickEvent();
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
		int tickCounter;
		int hours;
		int minutes;
		int seconds;
		int years;
		int months;
		int days;
		int lux;
    float temp,hum,pressure;
};

#endif // SCREEN1VIEW_HPP
