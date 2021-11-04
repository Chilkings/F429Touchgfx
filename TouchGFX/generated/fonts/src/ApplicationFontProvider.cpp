/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#include <fonts/ApplicationFontProvider.hpp>
#include <fonts/GeneratedFont.hpp>
#include <texts/TypedTextDatabase.hpp>

touchgfx::Font* ApplicationFontProvider::getFont(touchgfx::FontId typography)
{
    switch (typography)
    {
    case Typography::OUTPUT:
        // SourceSansPro_Bold_128_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[0]);
    case Typography::MAIN:
        // SourceSansPro_Bold_30_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[1]);
    case Typography::CODE:
        // SourceCodePro_Regular_16_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[2]);
    case Typography::DESCRIPTION:
        // SourceCodePro_Regular_10_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[3]);
    default:
        return 0;
    }
}