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

#ifndef sprite_representation_text_hpp
#define sprite_representation_text_hpp

#include "sprite_draw_interface.h"
#include "sprite_atlas_interface.h"
#include "sprite_representation_static.hpp"
#include "font_interface.h"

#include "sprite_representation_text_interface.h"

namespace engine
{
    class SpriteRepresentationText: public SpriteRepresentationTextI
    {
        FontI* m_bitmapFont;
        std::string m_text;
        OriginF m_shadowOffset;
        Color4 m_shadowColor;
        float m_lineMultiplier;
        float m_alpha;
        TEXT_HORIZONTAL_ALIGNMENT m_textHorizontalAlignment;
        TEXT_VERTICAL_ALIGNMENT m_textVerticalAlignment;
    public:
        SpriteRepresentationText(FontI*);

        void SetText(std::string);
        
        /** Get text */
        std::string GetText() { return m_text; };

        /** Scale setter */
        void SetScale(float x);

        /** Position this sprite in game coordinates */
        void SetPosition(Vector2 pos);

        void SetAlpha(float val);

        float GetAlpha();
        
        void SetZPosition(float zPos);

        void SetAcceptsLight(bool val);

        void SetShadowColor(Color4);

        void SetShadowOffset(OriginF);

        void SetLineHeightMultiplier(float);

        void SetHorizontalAlignment(std::string);
        
        void SetVerticalAlignment(std::string);

        void SetRotation(Rotation);

    public:
        void DrawAt(int x, int y);
        void Draw();
        void SetColorMod(Color4 val);
    };
};

#endif /* sprite_representation_text_hpp */
