#ifndef INTRODUCTION_PRESENTER_HPP
#define INTRODUCTION_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class IntroductionView;

class IntroductionPresenter : public Presenter, public ModelListener
{
public:
    IntroductionPresenter(IntroductionView& v);

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

    virtual ~IntroductionPresenter() {};

private:
    IntroductionPresenter();

    IntroductionView& view;
};

#endif // INTRODUCTION_PRESENTER_HPP
