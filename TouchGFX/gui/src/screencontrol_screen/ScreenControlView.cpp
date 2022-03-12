#include <gui/screencontrol_screen/ScreenControlView.hpp>

#ifndef	SIMULATOR
extern "C" {
	#include "main.h"
}
#else
//#include <gui/simulator/system_sim.hpp>
//int time_hours,time_minutes,time_seconds,time_years,time_mouths,time_days;
#endif

ScreenControlView::ScreenControlView()
{

}

void ScreenControlView::setupScreen()
{
    ScreenControlViewBase::setupScreen();
}

void ScreenControlView::tearDownScreen()
{
    ScreenControlViewBase::tearDownScreen();
}

void ScreenControlView::functionRelay1()
{
	int state = toggleButtonRelay1.getState();
	RELAY1(state);
	
	toggleButtonRelay1.forceState(state);
  bulbYellow1.setVisible(state);
	bulpWhite1.setVisible(1^state); 
	
  toggleButtonRelay1.invalidate();
  bulbYellow1.invalidate();
	bulpWhite1.invalidate();
}

void ScreenControlView::functionRelay2()
{
	int state = toggleButtonRelay2.getState();
	RELAY2(state);
	
	toggleButtonRelay2.forceState(state);
  bulbYellow2.setVisible(state);
	bulpWhite2.setVisible(1^state);
	
  toggleButtonRelay2.invalidate();
  bulbYellow2.invalidate();
	bulpWhite2.invalidate();
}


void ScreenControlView::functionRelay3()
{
	int state = toggleButtonRelay3.getState();
//	RELAY2(state);
	
	toggleButtonRelay3.forceState(state);
  bulbYellow3.setVisible(state);
	bulpWhite3.setVisible(1^state);
	
  toggleButtonRelay3.invalidate();
  bulbYellow3.invalidate();
	bulpWhite3.invalidate();
}