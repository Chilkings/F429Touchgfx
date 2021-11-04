#ifndef LABELBOX_HPP
#define LABELBOX_HPP

#include <gui_generated/containers/LabelBoxBase.hpp>
#include <touchgfx/hal/Types.hpp>
#include <touchgfx/TypedText.hpp>

class LabelBox : public LabelBoxBase
{
public:
    LabelBox();
    virtual ~LabelBox() {}

    virtual void setColor(colortype color);
    virtual void setText(TypedTextId text);
    virtual void setAlpha(uint8_t);
    virtual uint8_t getAlpha();
protected:
};

#endif // LABELBOX_HPP
