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

#ifndef text_sprite_representation_interface_h
#define text_sprite_representation_interface_h

#include "sprite_draw_interface.h"

namespace engine
{
    class SpriteRepresentationTextI: public SpriteRepresentationI
    {
        using SpriteRepresentationI::SpriteRepresentationI;
    public:

        /** Text */
        virtual void SetText(std::string) = 0;

        /** Shadow color. If alpha is <= 0 shadow is disabled. Default is clear color. */
        virtual void SetShadowColor(Color4) = 0;

        /** Set shadow offset. Default is { 1, 1 } */
        virtual void SetShadowOffset(OriginF) = 0;

        /** Set the line multiplier. Default is 1.f and is based on what was initially
            defined in the .fnt file */
        virtual void SetLineHeightMultiplier(float) = 0;

        /** Set the horizontal alignment. "left"|"center"|"right"
            */
        virtual void SetHorizontalAlignment(std::string) = 0;

        /** Set the vertical alignment. "top"|"middle"|"bottom"
            */
        virtual void SetVerticalAlignment(std::string) = 0;

    };
};

#endif /* text_sprite_representation_interface_h */
