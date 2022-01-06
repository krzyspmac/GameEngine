//
//  font_bitmap.hpp
//  Engine
//
//  Created by krzysp on 06/01/2022.
//

#ifndef font_bitmap_hpp
#define font_bitmap_hpp

#include "common.h"
#include "font_interface.h"

namespace engine
{
    /**
     Declares a concrete instance for rendering bitmpa fonts
     using a sprite atlas sheet and a .fnt file in text format.
     */
    class FontBitmap: public FontI
    {
        void Prepare();
    public:
        /**
         Create a bitmap bit.
         @param fntFile     - path to a FNT file (in text format)
         @param fontAtlas   - path to the bitmap containing the font sprite sheet.
         */
        FontBitmap(std::string fntFile, std::string fontAtlas);

        void DrawAt(std::string, float, float, int, int, int, int, TEXT_ALIGNMENT);
    };
};

#endif /* font_bitmap_hpp */
