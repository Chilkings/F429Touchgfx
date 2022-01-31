#include <gui/screen1_screen/Screen1View.hpp>
#include <touchgfx/utils.hpp>

Screen1View::Screen1View()
{
		tickCounter=0;
    hours=10;
    minutes=10;
    seconds=0;
		years = 2022;
		months = 1;
		days = 1 ;
		lux =145;
    temp=23.8;hum=87.8;pressure=9.91;
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::handleTickEvent()
{
		tickCounter++;

    if (tickCounter % 10 == 0)
    {
				hours = presenter->getHour();
				minutes = presenter->getMinute();
				seconds = presenter->getSeconds();

			  years = presenter->getYear();
				months = presenter->getMouth();
				days  = presenter->getDay();
			
				Unicode::snprintf(textAreaYearBuffer, TEXTAREAYEAR_SIZE, "%04d", years);
				Unicode::snprintf(textAreaDateBuffer1, TEXTAREADATEBUFFER1_SIZE, "%02d", months);
				Unicode::snprintf(textAreaDateBuffer2, TEXTAREADATEBUFFER2_SIZE, "%02d", days);
				
				textAreaDate.invalidate();
				textAreaYear.invalidate();
        // Update the clocks
        digitalClock1.setTime24Hour(hours, minutes, seconds);
    }
		
		if(tickCounter%60 == 0)
		{
			  lux = presenter->getLux();
				temp = presenter->getTemp();
				hum = presenter->getHum();
				pressure = (presenter->getPressure())/1000;
			
				Unicode::snprintf(textAreaLuxBuffer, TEXTAREALUX_SIZE, "%d", lux);
				Unicode::snprintfFloat(textAreaTempBuffer, TEXTAREATEMP_SIZE, "%4.2f", (float)temp);
//				Unicode::snprintfFloat(textAreaHumBuffer, TEXTAREAHUM_SIZE, "%.1f", hum);
				Unicode::snprintfFloat(textAreaPresssureBuffer, TEXTAREAPRESSSURE_SIZE, "%0.2f", (float)pressure);
				
				textAreaTemp.invalidate();
//				textAreaHum.invalidate();
				textAreaPresssure.invalidate();
				textAreaLux.invalidate();
		}
		
		if(isConnectNetwork)
		{
			imageNetworkFalse.setVisible(false);
			imageNetworkTrue.setVisible(true);
			imageNetworkFalse.invalidate();
			imageNetworkTrue.invalidate();
			isConnectNetwork = 0;
		}
}
