#ifndef INTRODUCTION_VIEW_HPP
#define INTRODUCTION_VIEW_HPP

#include <gui_generated/introduction_screen/IntroductionViewBase.hpp>
#include <gui/introduction_screen/IntroductionPresenter.hpp>
#include <gui/containers/LabelBox.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>
#include <touchgfx/widgets/TextArea.hpp>

class IntroductionView : public IntroductionViewBase
{
public:
    IntroductionView();
    virtual ~IntroductionView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleClickEvent(const ClickEvent& evt);
    virtual void handleGestureEvent(const GestureEvent& evt);
    virtual void handleDragEvent(const DragEvent& evt);
    virtual void handleKeyEvent(uint8_t key);
private:
    typedef enum
    {
        STATE_INTRODUCTION = 0,
        STATE_INTRODUCTION_WITH_MVP,
        STATE_MVP_UI_AND_SYSTEM,
        STATE_MVP_DESCRIPTION_1,
        STATE_MVP_DESCRIPTION_2,
        STATE_MVP_DESCRIPTION_3,
        STATE_MVP_DESCRIPTION_4,
        STATE_OUTPUT_TO_SYSTEM,
        STATE_OUTPUT_CODE_1,
        STATE_OUTPUT_CODE_2,
        STATE_OUTPUT_CODE_3,
        STATE_OUTPUT_CODE_4,
        STATE_INPUT_FROM_SYSTEM,
        STATE_INPUT_CODE_1,
        STATE_INPUT_CODE_2,
        STATE_INPUT_CODE_3,
        STATE_INPUT_CODE_4,
        STATE_DEMO,
        NUMBER_OF_STATES
    } StateId;

    typedef struct
    {
        int16_t x;
        int16_t y;
        uint8_t alpha;
    } ElementConfiguration;

    typedef struct
    {
        int16_t x;
        int16_t y;
        uint8_t alpha;
        TypedTextId textId;
    } TextConfiguration;

    typedef struct
    {
        ElementConfiguration ui;
        ElementConfiguration view;
        ElementConfiguration presenter;
        ElementConfiguration model;
        ElementConfiguration system;
        TextConfiguration viewText;
        TextConfiguration presenterText;
        TextConfiguration modelText;
        TextConfiguration systemText;
        TextConfiguration headlineText;
        uint8_t duration;
    } State;

    void go(bool forward);
    void gotoState(StateId id);

    FadeAnimator<MoveAnimator<LabelBox> > system;
    FadeAnimator<MoveAnimator<LabelBox> > model;
    FadeAnimator<MoveAnimator<LabelBox> > presenter;
    FadeAnimator<MoveAnimator<LabelBox> > view;
    FadeAnimator<MoveAnimator<LabelBox> > ui;

    FadeAnimator<MoveAnimator<TextArea> > systemText;
    FadeAnimator<MoveAnimator<TextArea> > modelText;
    FadeAnimator<MoveAnimator<TextArea> > presenterText;
    FadeAnimator<MoveAnimator<TextArea> > viewText;

    State states[NUMBER_OF_STATES];
    StateId currentStateId;

    bool gesture;
};

#endif // INTRODUCTION_VIEW_HPP
