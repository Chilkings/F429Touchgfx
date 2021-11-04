#include <gui/demo_screen/DemoView.hpp>
#include <gui/demo_screen/DemoPresenter.hpp>

DemoPresenter::DemoPresenter(DemoView& v)
    : view(v)
{
}

void DemoPresenter::buttonClicked()
{
    model->increaseDesiredValue();
}

void DemoPresenter::setCurrentValue(int currentValue)
{
    view.setCurrentValue(currentValue);
}

void DemoPresenter::activate()
{
    view.setCurrentValue(model->readCurrentValue());
}

void DemoPresenter::deactivate()
{
}
