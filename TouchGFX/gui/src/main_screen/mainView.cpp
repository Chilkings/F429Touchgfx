#include <gui/main_screen/mainView.hpp>
#include "BitmapDatabase.hpp"
#include "texts/TextKeysAndLanguages.hpp"
#include "gui/common/constans.hpp"
#include <touchgfx/hal/HAL.hpp>

mainView::mainView() :
    transitionEndedCallback(this, &mainView::transitionEndedHandler),
    buttonFadeAnimationEndedCallback(this, &mainView::buttonFadeAnimationEndedHandler),
    transitionInProgress(false),
    transitionSpeed(TRANSITION_SPEED_FAST),
    fadeDirection(-1),
    transitionMenuTimeoutCounter(0),
    frameSkippedCounter(0),
    frames(0),
    fps(0),
    previousMcuLoadPct(0)
{

}

void mainView::setupScreen()
{
    //Enables framerate compensation, thereby skips frame if it can't render and transfer it in time for next vsync
    HAL::getInstance()->setFrameRateCompensation(true);

    //This function enables/disable Chrom-ART, the DMA2D hardware accelerator
    HAL::getInstance()->enableDMAAcceleration(true);

    for (int i = 0; i < Transitions::NUMBER_OF_TRANSITIONS; i++)
    {
        switch (i)
        {
        case Transitions::FLIP :
            transitions[i] = &flip;
            transitions[i]->setTransitionIconId(BITMAP_TRANSITIONTYPE2_ID);
            transitions[i]->setTransitionTextId(T_FLIPTRANSITION);
            transitions[i]->setTransitionTitleTextId(T_LARGEFLIPTRANSITION);
            break;
        case Transitions::COVER:
            transitions[i] = &cover;
            transitions[i]->setTransitionIconId(BITMAP_TRANSITIONTYPE1_ID);
            transitions[i]->setTransitionTextId(T_COVERTRANSITION);
            transitions[i]->setTransitionTitleTextId(T_LARGECOVERTRANSITION);
            break;
        case Transitions::SLIDE:
            transitions[i] = &slide;
            transitions[i]->setTransitionIconId(BITMAP_TRANSITIONTYPE1_ID);
            transitions[i]->setTransitionTextId(T_SLIDETRANSITION);
            transitions[i]->setTransitionTitleTextId(T_LARGESLIDETRANSITION);
            break;
        case Transitions::CURTAINS:
            transitions[i] = &curtains;
            transitions[i]->setTransitionIconId(BITMAP_TRANSITIONTYPE3_ID);
            transitions[i]->setTransitionTextId(T_CURTAINSTRANSITION);
            transitions[i]->setTransitionTitleTextId(T_LARGECURTAINSTRANSITION);
            break;
        case Transitions::ROLLOUT:
            transitions[i] = &rollout;
            transitions[i]->setTransitionIconId(BITMAP_TRANSITIONTYPE2_ID);
            transitions[i]->setTransitionTextId(T_ROLLOUTTRANSITION);
            transitions[i]->setTransitionTitleTextId(T_LARGEROLLOUTTRANSITION);
            break;
        case Transitions::CUBE:
            transitions[i] = &cube;
            transitions[i]->setTransitionIconId(BITMAP_TRANSITIONTYPE4_ID);
            transitions[i]->setTransitionTextId(T_CUBETRANSITION);
            transitions[i]->setTransitionTitleTextId(T_LARGECUBETRANSITION);
            break;
        case Transitions::SPINOUT:
            transitions[i] = &spinout;
            transitions[i]->setTransitionIconId(BITMAP_TRANSITIONTYPE5_ID);
            transitions[i]->setTransitionTextId(T_SPINOUTTRANSITION);
            transitions[i]->setTransitionTitleTextId(T_LARGESPINOUTTRANSITION);
            break;
        case Transitions::SPIN:
            transitions[i] = &spin;
            transitions[i]->setTransitionIconId(BITMAP_TRANSITIONTYPE5_ID);
            transitions[i]->setTransitionTextId(T_SPINTRANSITION);
            transitions[i]->setTransitionTitleTextId(T_LARGESPINTRANSITION);
            break;
        default:
            break;
        }

        transitions[i]->setPosition(background.getX(), background.getY(), background.getWidth(), background.getHeight());
        transitions[i]->setTransitionEndedCallback(transitionEndedCallback);

        add(*transitions[i]);
    }

    bottombar.setNumberOfTransitionsItems(Transitions::NUMBER_OF_TRANSITIONS);

    mainViewBase::setupScreen();

    startTransitionButton.setFadeAnimationEndedAction(buttonFadeAnimationEndedCallback);
}

void mainView::tearDownScreen()
{
    HAL::getInstance()->setFrameRateCompensation(false);
    mainViewBase::tearDownScreen();
}

void mainView::handleClickEvent(const ClickEvent& evt)
{
    if (transitionMenu.getRect().intersect(evt.getX(), evt.getY()) && transitionMenu.getState() == SlideMenu::EXPANDED)
    {
        if (evt.getType() == ClickEvent::PRESSED)
        {
            bottombar.bottomBarClicked(evt.getX() - transitionMenu.getX(), evt.getY() - transitionMenu.getY());
        }
    }
    mainViewBase::handleClickEvent(evt);
}

void mainView::handleTickEvent()
{
    if (transitionMenu.getState() == SlideMenu::EXPANDED && (transitionMenu.getExpandedStateTimer() + 10) > transitionMenu.getExpandedStateTimeout())
    {
        transitionMenu.resetExpandedStateTimer();
    }
    else if (transitionMenu.getState() == SlideMenu::COLLAPSED)
    {
        transitionMenuTimeoutCounter++;
        if (transitionMenuTimeoutCounter > TRANSITION_MENU_TIMEOUT)
        {
            transitionMenu.animateToState(SlideMenu::EXPANDED);
            bottombar.animateArrow(SlideMenu::EXPANDED);
            transitionMenuTimeoutCounter = 0;
        }
    }

    // -- MCU LOAD -- //
    // This section uses the HAL layer to detect the MCU load and if it is changed the topBar is updated
    uint16_t mcuLoadPct = touchgfx::HAL::getInstance()->getMCULoadPct();
    if (mcuLoadPct != previousMcuLoadPct)
    {
        previousMcuLoadPct = mcuLoadPct;
        updateMCU(previousMcuLoadPct);
    }
    // -- MCU LOAD -- //

    // -- FPS -- //
    // This section uses the HAL layer to detect the LCD Refresh count and calculates the FPS if it is changed the topBar is updated
    (HAL::getInstance()->getLCDRefreshCount() > 1) ? frameSkippedCounter++ : frames++;

    if (frames + frameSkippedCounter >= 60)
    {
        fps = frames;
        updateFPS(fps);
        frameSkippedCounter = 0;
        frames = 0;
    }
    // -- FPS -- //

    if (!transitionInProgress)
    {
        uint8_t startTransitionButtonAlpha = startTransitionButton.getAlpha();
        if (startTransitionButtonAlpha == 255)
        {
            fadeDirection = -2;
        }
        else if (startTransitionButtonAlpha == 55)
        {
            fadeDirection = 2;
        }
        startTransitionButton.setAlpha(startTransitionButtonAlpha + fadeDirection);
        startTransitionButton.invalidate();
    }
}

void mainView::startTransitionPressed()
{
    transitionInProgress = true;

    startTransitionButton.startFadeAnimation(0, FADE_DURATION_CONTROLS);
    selectedTransitionText.startFadeAnimation(0, FADE_DURATION_CONTROLS);
    bottombar.fade(0, FADE_DURATION_CONTROLS);

    if (transitionMenu.getState() == SlideMenu::EXPANDED)
    {
        transitionMenu.animateToState(SlideMenu::COLLAPSED);
        bottombar.animateArrow(SlideMenu::COLLAPSED);
        transitionMenuTimeoutCounter = 0;
    }
}

void mainView::getTransitionInfo(TransitionInfo* value)
{
    value->iconId = transitions[value->transitionId]->getTransitionIconId();
    value->textId = transitions[value->transitionId]->getTransitionTextId();
}

void mainView::scrollWheelPressed()
{
    selectedTransitionText.startFadeAnimation(0, FADE_DURATION_CONTROLS);
}

void mainView::scrollWheelAnimationEnded()
{
    selectedTransitionText.setTypedText(TypedText(transitions[bottombar.getSelectedTransition()]->getTransitionTitleTextId()));
    selectedTransitionText.startFadeAnimation(255, FADE_DURATION_CONTROLS);
}

void mainView::ChromARTPressed(bool value)
{
    HAL::getInstance()->enableDMAAcceleration(value);
}

void mainView::sliderMenuStateChanged(SlideMenu::State value)
{
    if (value == SlideMenu::COLLAPSED)
    {
        transitionMenuTimeoutCounter = 0;
    }
}

void mainView::animationSpeedButtonPressed(bool value)
{
    transitionSpeed = value ? TRANSITION_SPEED_FAST : TRANSITION_SPEED_SLOW;
}

void mainView::updateMCU(uint16_t mcu)
{
    topbar.updateMCU(mcu);
}

void mainView::updateFPS(uint16_t fps)
{
    topbar.updateFPS(fps);
}

void mainView::transitionEndedHandler(uint16_t newBackgroundId)
{
    if (newBackgroundId == BITMAP_BACKGROUND_DAY_FULL_ID)
    {
        currentBackground = DAY;
    }
    else
    {
        currentBackground = NIGHT;
    }

    background.setBitmap(Bitmap(newBackgroundId));
    background.setVisible(true);
    background.invalidate();

    startTransitionButton.startFadeAnimation(255, FADE_DURATION_CONTROLS);
    selectedTransitionText.startFadeAnimation(255, FADE_DURATION_CONTROLS);
    bottombar.fade(255, FADE_DURATION_CONTROLS);
}

void mainView::buttonFadeAnimationEndedHandler(const FadeAnimator<Button>& src)
{
    if (&src == &startTransitionButton && startTransitionButton.getAlpha() == 0)
    {
        if (currentBackground == DAY)
        {
            transitions[bottombar.getSelectedTransition()]->startTransition(Bitmap(BITMAP_BACKGROUND_DAY_FULL_ID), Bitmap(BITMAP_BACKGROUND_NIGHT_FULL_ID), transitionSpeed);
        }
        else
        {
            transitions[bottombar.getSelectedTransition()]->startTransition(Bitmap(BITMAP_BACKGROUND_NIGHT_FULL_ID), Bitmap(BITMAP_BACKGROUND_DAY_FULL_ID), transitionSpeed);
        }
        background.setVisible(false);
        background.invalidate();

        remove(topbar);
        add(topbar);
    }
    else
    {
        transitionMenu.animateToState(SlideMenu::EXPANDED);
        bottombar.animateArrow(SlideMenu::EXPANDED);

        transitionInProgress = false;
    }
}
