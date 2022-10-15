// Copyright (c) 2022 Krzysztof Pawłowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef font_interface_h
#define font_interface_h

#include "common.h"
#include "size.hpp"

namespace engine
{
    typedef enum {
        TEXT_ALIGN_LEFT     = 0,
        TEXT_ALIGN_CENTER   = 1,
        TEXT_ALIGN_RIGHT    = 2
    } TEXT_HORIZONTAL_ALIGNMENT;

    typedef enum {
        TEXT_ALIGN_TOP      = 0,
        TEXT_ALIGN_MIDDLE   = 1,
        TEXT_ALIGN_BOTTOM   = 2
    } TEXT_VERTICAL_ALIGNMENT;

    class FontI
    {
    public:
        FontI(std::string filename): m_fontName(filename) { }
        virtual ~FontI() { };
        
        /**
         Retrieve the font name. Usually the name of the defining the font.
         */
        std::string &getFontName() { return m_fontName; };

        /** Set the scale */
        virtual void SetScale(float) = 0;

        /** Set alpha */
        virtual void SetAlpha(float) = 0;
        
        /** Set z-position */
        virtual void SetZPosition(float) = 0;

        /**
         Draw the font. Uses the current engine provider.
         */
        virtual void DrawAt(std::string text,
                            float x,
                            float y,
                            int r,
                            int g,
                            int b,
                            int a,
                            TEXT_HORIZONTAL_ALIGNMENT hAlign,
                            TEXT_VERTICAL_ALIGNMENT vAlign,
                            Color4 colorMod,
                            float lineMultiplier
                            ) = 0;

    private:
        std::string m_fontName;
    };

}

#endif /* font_interface_h */
