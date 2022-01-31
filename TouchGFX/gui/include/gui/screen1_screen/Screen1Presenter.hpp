#ifndef SCREEN1PRESENTER_HPP
#define SCREEN1PRESENTER_HPP



#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen1View;

class Screen1Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen1Presenter(Screen1View& v);

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

    virtual ~Screen1Presenter() {};
			
		int getHour()
    {
        return model->getHour();
    }
		
		int getMinute()
    {
        return model->getMinute();
    }

		int getSeconds()
    {
        return model->getSeconds();
    }
		
		int getYear()
    {
        return model->getYear();
    }
		
		int getMouth()
    {
        return model->getMouth();
    }
		
		int getDay()
    {
        return model->getDay();
    }
		
		int getLux()
		{
			return model->getLux();
		}
		
		float getPressure()
		{
			return model->getPressure();
		}
		
		float getTemp()
		{
			return model->getTemp();
		}
		
		float getHum()
		{
			return model->getHum();
		}
private:
    Screen1Presenter();

    Screen1View& view;
};

#endif // SCREEN1PRESENTER_HPP
