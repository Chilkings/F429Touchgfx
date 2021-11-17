#include <gui/main_screen/MainView.hpp>
#include <touchgfx/utils.hpp>

MainView::MainView()
{

}

void MainView::setupScreen()
{
    MainViewBase::setupScreen();
}

void MainView::tearDownScreen()
{
    MainViewBase::tearDownScreen();
}

void MainView::buttonUpClicked()
{
    touchgfx_printf("buttonUpClicked\n");
    counter++;
    Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%d", counter);
    // Invalidate text area, which will result in it being redrawn in next tick.
    textCounter.invalidate();
}
void MainView::buttonDownClicked()
{
    touchgfx_printf("buttonDownClicked\n");

    counter--;
    Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%d", counter);
    // Invalidate text area, which will result in it being redrawn in next tick.
    textCounter.invalidate();
}