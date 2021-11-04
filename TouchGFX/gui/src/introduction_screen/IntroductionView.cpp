#include <gui/introduction_screen/IntroductionView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/hal/HAL.hpp>

#define O4 {0,0,0,TYPED_TEXT_INVALID}
#define O4x2 O4,O4
#define O4x3 O4x2,O4
#define O4x4 O4x3,O4
#define O4x5 O4x4,O4
#define O3 {0,0,0}

IntroductionView::IntroductionView() :
    currentStateId(STATE_INTRODUCTION),
    gesture(false)
{
    State s1 =
    {
        {-300, 0, 255}, { -300, 0, 255 }, { -300, 0, 255 }, { -300, 0, 255 }, { 1300, 0, 255 },
        O4x4,
        { 0, 50, 255, T_INTRODUCTION },
        0
    };
    states[STATE_INTRODUCTION] = s1;

    State s2 =
    {
        { -300, 0, 255 }, { 300, 230 - 1, 255 }, { 330, 310 - 2, 255 }, { 270, 150, 255 }, { 1300, 0, 255 },
        O4x4,
        { 0, 50, 255, T_UNDERSTANDING },
        60
    };
    states[STATE_INTRODUCTION_WITH_MVP] = s2;

    State s3 =
    {
        { 30, 230 - 1, 255 }, { 300, 230 - 1, 255 }, { 330, 310 - 2, 255 }, { 270, 150, 255 }, { 570, 230 - 1, 255 },
        O4x4,
        { 0, 50, 255, T_MVP_IN_SHORT },
        60
    };
    states[STATE_MVP_UI_AND_SYSTEM] = s3;

    State s4 =
    {
        { -300, 0, 255 }, { 20, 20, 255 }, { 20, 120, 25 }, { 20, 220, 25 }, { 20, 320, 25 },
        { 240, 20, 255, T_VIEW_DESCRIPTION }, { 240, 120, 25, T_PRESENTER_DESCRIPTION }, { 240, 220, 25, T_MODEL_DESCRIPTION }, { 240, 320, 25, T_SYSTEM_DESCRIPTION },
        { 0, 200, 0, TYPED_TEXT_INVALID },
        60
    };
    states[STATE_MVP_DESCRIPTION_1] = s4;

    State s5 =
    {
        { -300, 0, 255 }, { 20, 20, 255 }, { 20, 120, 255 }, { 20, 220, 25 }, { 20, 320, 25 },
        { 240, 20, 255, T_VIEW_DESCRIPTION }, { 240, 120, 255, T_PRESENTER_DESCRIPTION }, { 240, 220, 25, T_MODEL_DESCRIPTION }, { 240, 320, 25, T_SYSTEM_DESCRIPTION },
        { 0, 200, 0, TYPED_TEXT_INVALID },
        60
    };
    states[STATE_MVP_DESCRIPTION_2] = s5;

    State s6 =
    {
        { -300, 0, 255 }, { 20, 20, 255 }, { 20, 120, 255 }, { 20, 220, 255 }, { 20, 320, 25 },
        { 240, 20, 255, T_VIEW_DESCRIPTION }, { 240, 120, 255, T_PRESENTER_DESCRIPTION }, { 240, 220, 255, T_MODEL_DESCRIPTION }, { 240, 320, 25, T_SYSTEM_DESCRIPTION },
        { 0, 200, 0, TYPED_TEXT_INVALID },
        60
    };
    states[STATE_MVP_DESCRIPTION_3] = s6;

    State s7 =
    {
        { -300, 0, 255 }, { 20, 20, 255 }, { 20, 120, 255 }, { 20, 220, 255 }, { 20, 320, 255 },
        { 240, 20, 255, T_VIEW_DESCRIPTION }, { 240, 120, 255, T_PRESENTER_DESCRIPTION }, { 240, 220, 255, T_MODEL_DESCRIPTION }, { 240, 320, 255, T_SYSTEM_DESCRIPTION },
        { 0, 200, 0, TYPED_TEXT_INVALID },
        60
    };
    states[STATE_MVP_DESCRIPTION_4] = s7;

    State s8 =
    {
        { -300, 0, 25 }, { 20, 20, 25 }, { 20, 120, 25 }, { 20, 220, 25 }, { 20, 320, 25 },
        { 240, 20, 25, T_VIEW_DESCRIPTION }, { 240, 120, 25, T_PRESENTER_DESCRIPTION }, { 240, 220, 25, T_MODEL_DESCRIPTION }, { 240, 320, 25, T_SYSTEM_DESCRIPTION },
        { 0, 200, 255, T_OUTPUT },
        60
    };
    states[STATE_OUTPUT_TO_SYSTEM] = s8;

    State s9 =
    {
        { -300, 0, 255 }, { 20, 20, 255 }, { 20, 120, 25 }, { 20, 220, 25 }, { 20, 320, 25 },
        { 240, 20, 255, T_VIEW_OUTPUT_CODE }, { 240, 120, 25, T_PRESENTER_OUTPUT_CODE }, { 240, 220, 25, T_MODEL_OUTPUT_CODE }, { 240, 320, 25, T_SYSTEM_OUTPUT_CODE },
        { 0, 200, 0, T_OUTPUT },
        60
    };
    states[STATE_OUTPUT_CODE_1] = s9;

    State s10 =
    {
        { -300, 0, 255 }, { 20, 20, 255 }, { 20, 120, 255 }, { 20, 220, 25 }, { 20, 320, 25 },
        { 240, 20, 255, T_VIEW_OUTPUT_CODE }, { 240, 120, 255, T_PRESENTER_OUTPUT_CODE }, { 240, 220, 25, T_MODEL_OUTPUT_CODE }, { 240, 320, 25, T_SYSTEM_OUTPUT_CODE },
        { 0, 200, 0, T_OUTPUT },
        60
    };
    states[STATE_OUTPUT_CODE_2] = s10;

    State s11 =
    {
        { -300, 0, 255 }, { 20, 20, 255 }, { 20, 120, 255 }, { 20, 220, 255 }, { 20, 320, 25 },
        { 240, 20, 255, T_VIEW_OUTPUT_CODE }, { 240, 120, 255, T_PRESENTER_OUTPUT_CODE }, { 240, 220, 255, T_MODEL_OUTPUT_CODE }, { 240, 320, 25, T_SYSTEM_OUTPUT_CODE },
        { 0, 200, 0, T_OUTPUT },
        60
    };
    states[STATE_OUTPUT_CODE_3] = s11;

    State s12 =
    {
        { -300, 0, 255 }, { 20, 20, 255 }, { 20, 120, 255 }, { 20, 220, 255 }, { 20, 320, 255 },
        { 240, 20, 255, T_VIEW_OUTPUT_CODE }, { 240, 120, 255, T_PRESENTER_OUTPUT_CODE }, { 240, 220, 255, T_MODEL_OUTPUT_CODE }, { 240, 320, 255, T_SYSTEM_OUTPUT_CODE },
        { 0, 200, 0, T_OUTPUT },
        60
    };
    states[STATE_OUTPUT_CODE_4] = s12;

    State s13 =
    {
        { -300, 0, 25 }, { 20, 20, 25 }, { 20, 120, 25 }, { 20, 220, 25 }, { 20, 320, 25 },
        { 240, 20, 25, T_VIEW_OUTPUT_CODE }, { 240, 120, 25, T_PRESENTER_OUTPUT_CODE }, { 240, 220, 25, T_MODEL_OUTPUT_CODE }, { 240, 320, 25, T_SYSTEM_OUTPUT_CODE },
        { 0, 200, 255, T_INPUT },
        60
    };
    states[STATE_INPUT_FROM_SYSTEM] = s13;

    State s14 =
    {
        { -300, 0, 255 }, { 20, 20, 25 }, { 20, 120, 25 }, { 20, 220, 255 }, { 20, 320, 25 },
        { 240, 20, 25, T_VIEW_INPUT_CODE }, { 240, 120, 25, T_PRESENTER_INPUT_CODE }, { 240, 220, 255, T_MODEL_INPUT_CODE }, { 240, 320, 25, T_SYSTEM_INPUT_CODE },
        { 0, 200, 0, T_INPUT },
        60
    };
    states[STATE_INPUT_CODE_1] = s14;

    State s15 =
    {
        { -300, 0, 255 }, { 20, 20, 25 }, { 20, 120, 25 }, { 20, 220, 255 }, { 20, 320, 255 },
        { 240, 20, 25, T_VIEW_INPUT_CODE }, { 240, 120, 25, T_PRESENTER_INPUT_CODE }, { 240, 220, 255, T_MODEL_INPUT_CODE }, { 240, 320, 255, T_SYSTEM_INPUT_CODE },
        { 0, 200, 0, T_INPUT },
        60
    };
    states[STATE_INPUT_CODE_2] = s15;

    State s16 =
    {
        { -300, 0, 255 }, { 20, 20, 25 }, { 20, 120, 255 }, { 20, 220, 255 }, { 20, 320, 255 },
        { 240, 20, 25, T_VIEW_INPUT_CODE }, { 240, 120, 255, T_PRESENTER_INPUT_CODE }, { 240, 220, 255, T_MODEL_INPUT_CODE }, { 240, 320, 255, T_SYSTEM_INPUT_CODE },
        { 0, 200, 0, T_INPUT },
        60
    };
    states[STATE_INPUT_CODE_3] = s16;

    State s17 =
    {
        { -300, 0, 255 }, { 20, 20, 255 }, { 20, 120, 255 }, { 20, 220, 255 }, { 20, 320, 255 },
        { 240, 20, 255, T_VIEW_INPUT_CODE }, { 240, 120, 255, T_PRESENTER_INPUT_CODE }, { 240, 220, 255, T_MODEL_INPUT_CODE }, { 240, 320, 255, T_SYSTEM_INPUT_CODE },
        { 0, 200, 0, T_INPUT },
        60
    };
    states[STATE_INPUT_CODE_4] = s17;

    State s18 =
    {
        { -300, 0, 25 }, { 20, 20, 25 }, { 20, 120, 25 }, { 20, 220, 25 }, { 20, 320, 25 },
        { 240, 20, 25, T_VIEW_INPUT_CODE }, { 240, 120, 25, T_PRESENTER_INPUT_CODE }, { 240, 220, 25, T_MODEL_INPUT_CODE }, O4,
        { 0, 200, 255, T_DEMO },
        60
    };
    states[STATE_DEMO] = s18;
}

void IntroductionView::setupScreen()
{
    ui.setColor(Color::getColorFrom24BitRGB(255, 0, 255));
    ui.setText(T_UI);
    ui.setXY(10, 20);
    add(ui);

    view.setColor(Color::getColorFrom24BitRGB(112, 48, 160));
    view.setText(T_VIEW);
    view.setXY(10, 20);
    add(view);

    presenter.setColor(Color::getColorFrom24BitRGB(0, 176, 240));
    presenter.setText(T_PRESENTER);
    presenter.setXY(10, 140);
    add(presenter);

    model.setColor(Color::getColorFrom24BitRGB(0, 176, 80));
    model.setText(T_MODEL);
    model.setXY(10, 270);
    add(model);

    system.setColor(Color::getColorFrom24BitRGB(197, 90, 17));
    system.setText(T_SYSTEM);
    system.setXY(10, 380);
    add(system);

    viewText.setColor(0);
    viewText.setTypedText(TypedText(TYPED_TEXT_INVALID));
    viewText.setXY(0, 0);
    add(viewText);

    presenterText.setColor(0);
    presenterText.setTypedText(TypedText(TYPED_TEXT_INVALID));
    presenterText.setXY(0, 0);
    add(presenterText);

    modelText.setColor(0x0);
    modelText.setTypedText(TypedText(TYPED_TEXT_INVALID));
    modelText.setXY(0, 0);
    add(modelText);

    systemText.setColor(0x0);
    systemText.setTypedText(TypedText(TYPED_TEXT_INVALID));
    systemText.setXY(0, 0);
    add(systemText);

    gotoState(STATE_INTRODUCTION);

    HAL::getInstance()->setFrameRateCompensation(true);
}

void IntroductionView::tearDownScreen()
{
}

void IntroductionView::handleClickEvent(const ClickEvent& evt)
{
    if (evt.getType() == ClickEvent::PRESSED || evt.getType() == ClickEvent::CANCEL)
    {
        gesture = false;
    }
    else if (evt.getType() == ClickEvent::RELEASED)
    {
        if (!gesture)
        {
            go(evt.getX() > getRootContainer().getWidth() / 2);
        }
    }
}

void IntroductionView::handleGestureEvent(const GestureEvent& evt)
{
    gesture = true;
    if (evt.getType() == GestureEvent::SWIPE_HORIZONTAL)
    {
        go(evt.getVelocity() < 0);
    }
}

void IntroductionView::handleDragEvent(const DragEvent& evt)
{
}

void IntroductionView::handleKeyEvent(uint8_t key)
{
    if (key == 'l')
    {
        go(false);
    }
    else if (key == 'r')
    {
        go(true);
    }
}

void IntroductionView::go(bool forward)
{
    if (forward)
    {
        if (currentStateId == NUMBER_OF_STATES - 1)
        {
            application().gotoDemoScreenSlideTransitionWest();
        }
        else
        {
            gotoState((StateId)(currentStateId + 1));
        }
    }
    else
    {
        if (currentStateId > 0)
        {
            gotoState((StateId)(currentStateId - 1));
        }
        else
        {
            application().gotoDemoScreenSlideTransitionWest();
        }
    }
}

void IntroductionView::gotoState(StateId id)
{
    currentStateId = id;
    State state = states[currentStateId];

    ui.startFadeAnimation(state.ui.alpha, state.duration, EasingEquations::cubicEaseOut);
    view.startFadeAnimation(state.view.alpha, state.duration, EasingEquations::cubicEaseOut);
    presenter.startFadeAnimation(state.presenter.alpha, state.duration, EasingEquations::cubicEaseOut);
    model.startFadeAnimation(state.model.alpha, state.duration, EasingEquations::cubicEaseOut);
    system.startFadeAnimation(state.system.alpha, state.duration, EasingEquations::cubicEaseOut);

    ui.startMoveAnimation(state.ui.x, state.ui.y, state.duration, EasingEquations::cubicEaseOut, EasingEquations::cubicEaseOut);
    view.startMoveAnimation(state.view.x, state.view.y, state.duration, EasingEquations::cubicEaseOut, EasingEquations::cubicEaseOut);
    presenter.startMoveAnimation(state.presenter.x, state.presenter.y, state.duration, EasingEquations::cubicEaseOut, EasingEquations::cubicEaseOut);
    model.startMoveAnimation(state.model.x, state.model.y, state.duration, EasingEquations::cubicEaseOut, EasingEquations::cubicEaseOut);
    system.startMoveAnimation(state.system.x, state.system.y, state.duration, EasingEquations::cubicEaseOut, EasingEquations::cubicEaseOut);

    viewText.invalidate();
    viewText.setTypedText(TypedText(state.viewText.textId));
    viewText.resizeToCurrentText();
    viewText.invalidate();

    presenterText.invalidate();
    presenterText.setTypedText(TypedText(state.presenterText.textId));
    presenterText.resizeToCurrentText();
    presenterText.invalidate();

    modelText.invalidate();
    modelText.setTypedText(TypedText(state.modelText.textId));
    modelText.resizeToCurrentText();
    modelText.invalidate();

    systemText.invalidate();
    systemText.setTypedText(TypedText(state.systemText.textId));
    systemText.resizeToCurrentText();
    systemText.invalidate();

    viewText.startFadeAnimation(state.viewText.alpha, state.duration, EasingEquations::cubicEaseOut);
    presenterText.startFadeAnimation(state.presenterText.alpha, state.duration, EasingEquations::cubicEaseOut);
    modelText.startFadeAnimation(state.modelText.alpha, state.duration, EasingEquations::cubicEaseOut);
    systemText.startFadeAnimation(state.systemText.alpha, state.duration, EasingEquations::cubicEaseOut);

    viewText.startMoveAnimation(state.viewText.x, state.viewText.y, state.duration, EasingEquations::cubicEaseOut, EasingEquations::cubicEaseOut);
    presenterText.startMoveAnimation(state.presenterText.x, state.presenterText.y, state.duration, EasingEquations::cubicEaseOut, EasingEquations::cubicEaseOut);
    modelText.startMoveAnimation(state.modelText.x, state.modelText.y, state.duration, EasingEquations::cubicEaseOut, EasingEquations::cubicEaseOut);
    systemText.startMoveAnimation(state.systemText.x, state.systemText.y, state.duration, EasingEquations::cubicEaseOut, EasingEquations::cubicEaseOut);

    headline.invalidate();
    headline.setTypedText(TypedText(state.headlineText.textId));
    headline.resizeHeightToCurrentText();
    headline.invalidate();
    headline.startFadeAnimation(state.headlineText.alpha, state.duration, EasingEquations::cubicEaseOut);
    headline.startMoveAnimation(state.headlineText.x, state.headlineText.y, state.duration, EasingEquations::cubicEaseOut, EasingEquations::cubicEaseOut);
}
