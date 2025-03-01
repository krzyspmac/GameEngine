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

#include "sprite_representation_text.hpp"

using namespace engine;

SpriteRepresentationText::SpriteRepresentationText(FontI *font)
    : SpriteRepresentationTextI(1.f)
    , m_bitmapFont(font)
    , m_shadowOffset({1.f, 1.f})
    , m_shadowColor({0.f, 0.f, 0.f, 0.f})
    , m_lineMultiplier(1.f)
    , m_alpha(1.f)
    , m_textHorizontalAlignment(TEXT_ALIGN_LEFT)
    , m_textVerticalAlignment(TEXT_ALIGN_TOP)
{
}

void SpriteRepresentationText::SetText(std::string value)
{
    m_text = value;
}

void SpriteRepresentationText::SetScale(float x)
{
    SpriteRepresentationI::SetScale(x);
    m_bitmapFont->SetScale(x);
}

void SpriteRepresentationText::SetPosition(Vector2 pos)
{
    SpriteRepresentationI::SetPosition(pos);
}

void SpriteRepresentationText::SetAlpha(float val)
{
    SpriteRepresentationI::SetAlpha(val);
    m_alpha = val;
    m_bitmapFont->SetAlpha(val);
}

float SpriteRepresentationText::GetAlpha()
{
//    return m_bitmapFont->Ge
    return m_alpha;
}

void SpriteRepresentationText::SetZPosition(float zPos)
{
    m_bitmapFont->SetZPosition(zPos);
}

void SpriteRepresentationText::SetRotation(Rotation)
{
    // do nothing
}

void SpriteRepresentationText::SetAcceptsLight(bool val)
{
    SpriteRepresentationI::SetAcceptsLight(val);
}

void SpriteRepresentationText::SetColorMod(Color4 val)
{
    SpriteRepresentationI::SetColorMod(val);
}

void SpriteRepresentationText::SetShadowColor(Color4 val)
{
    m_shadowColor = val;
}

void SpriteRepresentationText::SetShadowOffset(OriginF val)
{
    m_shadowOffset = val;
}

void SpriteRepresentationText::SetLineHeightMultiplier(float lineMultiplier)
{
    m_lineMultiplier = lineMultiplier;
}

void SpriteRepresentationText::SetHorizontalAlignment(std::string stringValue)
{
    typedef struct { std::string name; TEXT_HORIZONTAL_ALIGNMENT value; } AlignmentInfo;
    static AlignmentInfo values[] =
    {
        {"left", TEXT_ALIGN_LEFT}
      , {"center", TEXT_ALIGN_CENTER}
      , {"right", TEXT_ALIGN_RIGHT}
    };

    for(auto& v : values)
    {   if (v.name.compare(stringValue) == 0)
        {   m_textHorizontalAlignment = v.value;
            break;
        }
    }
}

void SpriteRepresentationText::SetVerticalAlignment(std::string stringValue)
{
    typedef struct { std::string name; TEXT_VERTICAL_ALIGNMENT value; } AlignmentInfo;
    static AlignmentInfo values[] =
    {
        {"top", TEXT_ALIGN_TOP}
      , {"middle", TEXT_ALIGN_MIDDLE}
      , {"bottom", TEXT_ALIGN_BOTTOM}
    };

    for(auto& v : values)
    {   if (v.name.compare(stringValue) == 0)
        {   m_textVerticalAlignment = v.value;
            break;
        }
    }
}

void SpriteRepresentationText::DrawAt(int x, int y)
{
    if (m_shadowColor.a > 0.f)
    {
        m_bitmapFont->DrawAt(m_text, x + m_shadowOffset.x, y + m_shadowOffset.x, 1, 1, 1, 1, m_textHorizontalAlignment, m_textVerticalAlignment , m_shadowColor, m_lineMultiplier);
    }
    m_bitmapFont->DrawAt(m_text, x, y, 1, 1, 1, 1, m_textHorizontalAlignment, m_textVerticalAlignment, GetColorMod(), m_lineMultiplier);
}

void SpriteRepresentationText::Draw()
{
    DrawAt(m_position.x, m_position.y);
}
