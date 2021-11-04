#include <gui/containers/LabelBox.hpp>

LabelBox::LabelBox()
{
}

void LabelBox::setColor(colortype color)
{
    background.setColor(color);
    border.setColor(0);
    invalidate();
}

void LabelBox::setText(TypedTextId textId)
{
    text.setTypedText(TypedText(textId));
    text.setBaselineY(50);
    invalidate();
}

void LabelBox::setAlpha(uint8_t alpha)
{
    text.setAlpha(alpha);
    background.setAlpha(alpha);
    border.setAlpha(alpha);
}

uint8_t LabelBox::getAlpha()
{
    return text.getAlpha();
}
