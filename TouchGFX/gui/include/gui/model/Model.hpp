#ifndef MODEL_HPP
#define MODEL_HPP

#ifndef	SIMULATOR
extern "C" {
	#include "system.h"
}
#else
//#include <gui/simulator/system_sim.hpp>
//int time_hours,time_minutes,time_seconds,time_years,time_mouths,time_days;
#endif


class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
		
		
		int getHour()
    {
        return time_hours;
    }
		
		int getMinute()
    {
        return time_minutes;
    }
		
		int getSeconds()
    {
        return time_seconds;
    }
		
		int getYear()
    {
        return time_years;
    }
		
		int getMouth()
    {
        return time_mouths;
    }
		
		int getDay()
    {
        return time_days;
    }
		
		
		int getLux()
		{
			return bh1750_lux;
		}
		
		float getPressure()
		{
			return bmp280_pressure;
		}
		
		float getTemp()
		{
			return bmp280_temperature;
		}
		
		float getHum()
		{
			return dht_humidty;
		}
protected:
    ModelListener* modelListener;
};

#endif // MODEL_HPP
