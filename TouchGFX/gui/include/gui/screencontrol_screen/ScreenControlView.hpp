#ifndef SCREENCONTROLVIEW_HPP
#define SCREENCONTROLVIEW_HPP

#include <gui_generated/screencontrol_screen/ScreenControlViewBase.hpp>
#include <gui/screencontrol_screen/ScreenControlPresenter.hpp>

class ScreenControlView : public ScreenControlViewBase
{
public:
    ScreenControlView();
    virtual ~ScreenControlView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
			
		virtual void functionRelay1();
		virtual void functionRelay2();
		virtual void functionRelay3();
protected:
};

#endif // SCREENCONTROLVIEW_HPP
