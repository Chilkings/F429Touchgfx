#ifndef DEMO_PRESENTER_HPP
#define DEMO_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class DemoView;

class DemoPresenter : public Presenter, public ModelListener
{
public:
    DemoPresenter(DemoView& v);

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

    virtual ~DemoPresenter() {};

    void buttonClicked();

    virtual void setCurrentValue(int currentValue);

private:
    DemoPresenter();

    DemoView& view;
};

#endif // DEMO_PRESENTER_HPP
