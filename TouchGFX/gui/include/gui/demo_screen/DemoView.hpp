#ifndef DEMO_VIEW_HPP
#define DEMO_VIEW_HPP

#include <gui_generated/demo_screen/DemoViewBase.hpp>
#include <gui/demo_screen/DemoPresenter.hpp>
#include <touchgfx/widgets/TouchArea.hpp>

class DemoView : public DemoViewBase
{
public:
    DemoView();
    virtual ~DemoView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void buttonClicked();
    void setCurrentValue(int currentValue);
private:
    TouchArea touchArea;
    touchgfx::Callback<DemoView, const touchgfx::AbstractButton&> touchAreaCallback;
    void touchAreaCallbackHandler(const touchgfx::AbstractButton&);
};

#endif // DEMO_VIEW_HPP
