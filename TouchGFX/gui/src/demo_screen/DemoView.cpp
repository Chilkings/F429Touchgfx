#include <gui/demo_screen/DemoView.hpp>

DemoView::DemoView() :
    touchAreaCallback(this, &DemoView::touchAreaCallbackHandler)
{
}

void DemoView::setupScreen()
{
    touchArea.setPosition(0, 0, getRootContainer().getWidth(), getRootContainer().getHeight());
    touchArea.setAction(touchAreaCallback);
    container.insert(&background, touchArea);
}

void DemoView::tearDownScreen()
{
}

void DemoView::buttonClicked()
{
    presenter->buttonClicked();
}

void DemoView::setCurrentValue(int currentValue)
{
    Unicode::snprintf(hw_input_valueBuffer, 10, "%d", currentValue);
    hw_input_value.invalidate();
}

void DemoView::touchAreaCallbackHandler(const touchgfx::AbstractButton&)
{
    application().gotoIntroductionScreenSlideTransitionWest();
}
