/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/topbarContainerBase.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

topbarContainerBase::topbarContainerBase() :
    buttonCallback(this, &topbarContainerBase::buttonCallbackHandler),
    chromARTStateChangedTriggerCallback(0)
{
    setWidth(800);
    setHeight(70);
    bar.setXY(0, 0);
    bar.setBitmap(touchgfx::Bitmap(BITMAP_TRANS_TOP_BAR_ID));

    mcuTitle.setXY(248, 10);
    mcuTitle.setColor(touchgfx::Color::getColorFromRGB(221, 255, 202));
    mcuTitle.setLinespacing(0);
    mcuTitle.setTypedText(touchgfx::TypedText(T___SINGLEUSE_M3UE));

    mcuValue.setPosition(291, 10, 60, 32);
    mcuValue.setColor(touchgfx::Color::getColorFromRGB(221, 255, 202));
    mcuValue.setLinespacing(0);
    Unicode::snprintf(mcuValueBuffer, MCUVALUE_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_TEKI).getText());
    mcuValue.setWildcard(mcuValueBuffer);
    mcuValue.setTypedText(touchgfx::TypedText(T___SINGLEUSE_KQID));

    fpsTite.setXY(448, 10);
    fpsTite.setColor(touchgfx::Color::getColorFromRGB(221, 255, 202));
    fpsTite.setLinespacing(0);
    fpsTite.setTypedText(touchgfx::TypedText(T___SINGLEUSE_KILU));

    fpsValue.setPosition(482, 10, 43, 32);
    fpsValue.setColor(touchgfx::Color::getColorFromRGB(221, 255, 202));
    fpsValue.setLinespacing(0);
    Unicode::snprintf(fpsValueBuffer, FPSVALUE_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_YGS1).getText());
    fpsValue.setWildcard(fpsValueBuffer);
    fpsValue.setTypedText(touchgfx::TypedText(T___SINGLEUSE_AD0A));

    infoButton.setXY(385, 10);
    infoButton.setBitmaps(touchgfx::Bitmap(BITMAP_ICON_INFO_ID), touchgfx::Bitmap(BITMAP_ICON_INFO_ID));

    chromArtButton.setXY(645, -1);
    chromArtButton.setBitmaps(touchgfx::Bitmap(BITMAP_CHROM_ART_OFF_ID), touchgfx::Bitmap(BITMAP_CHROM_ART_ON_ID));
    chromArtButton.forceState(true);
    chromArtButton.setAction(buttonCallback);

    chromArtGradient.setXY(645, -1);
    chromArtGradient.setBitmap(touchgfx::Bitmap(BITMAP_CHROM_ART_ON_LIGHT_ID));
    chromArtGradient.setAlpha(0);

    add(bar);
    add(mcuTitle);
    add(mcuValue);
    add(fpsTite);
    add(fpsValue);
    add(infoButton);
    add(chromArtButton);
    add(chromArtGradient);
}

void topbarContainerBase::initialize()
{

}

void topbarContainerBase::chromARTStateChangedAction(bool value)
{

}

void topbarContainerBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &chromArtButton)
    {
        //ChromARTButtonPressed1
        //When chromArtButton clicked emit chromARTStateChangedTrigger callback
        //Emit callback
        emitChromARTStateChangedTriggerCallback(chromArtButton.getState());

        //ChromARTButtonPressed2
        //When chromArtButton clicked call chromARTStateChangedAction on topbarContainer
        //Call chromARTStateChangedAction
        chromARTStateChangedAction(chromArtButton.getState());
    }
}
