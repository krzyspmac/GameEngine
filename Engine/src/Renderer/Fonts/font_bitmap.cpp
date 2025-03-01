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

#include "font_bitmap.hpp"
#include "key_value.hpp"
#include "engine.hpp"

using namespace engine;

static Origin zeroPoint = {0, 0};
static Origin point = {0, 0};

#pragma mark - Font Bitmap

FontBitmapDescriptor::FontBitmapDescriptor(std::string fntFile, std::string fontAtlas)
{
    Prepare(fntFile);
    m_sDescriptor.m_textureFilename = fontAtlas;
}

void FontBitmapDescriptor::Prepare(std::string fntFile)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    std::unique_ptr<FileStreamI> stream(ENGINE().getFileAccess().GetAccess(fntFile.c_str()));

    fp = stream->GetFP(); //fopen(fntFile.c_str(), "r");
    if (fp == NULL)
    {
        return;
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        KeyValueProperties properties(line);

        std::string type = properties.GetType();
        if (type == "info")
        {
            BuildDescriptorFace(properties);
            continue;
        }
        else if (type == "common")
        {
            BuildDescriptorCommon(properties);
            continue;
        }
        else if (type == "char")
        {
            m_glyphs.push_back(FontBitmapGlyph(properties));
        }
        else if (type == "kerning")
        {
            BuildDescriptorKerning(properties);
        }
    }

    if (line)
    {
        free(line);
    }
}

void FontBitmapDescriptor::BuildDescriptorFace(KeyValueProperties& properties)
{
    m_sDescriptor.info.face = properties.GetStringValueFor("face");
    m_sDescriptor.info.size = properties.GetNumberValueFor("size");
    m_sDescriptor.info.spacing = properties.GetVectorValueFor("spacing");
}

void FontBitmapDescriptor::BuildDescriptorCommon(KeyValueProperties& properties)
{
    m_sDescriptor.common.lineHeight = properties.GetNumberValueFor("lineHeight");
    m_sDescriptor.common.base = properties.GetNumberValueFor("base");
    m_sDescriptor.common.scaleW = properties.GetNumberValueFor("scaleW");
    m_sDescriptor.common.scaleH = properties.GetNumberValueFor("scaleH");
}

void FontBitmapDescriptor::BuildDescriptorKerning(KeyValueProperties& properties)
{
    FontBitmapGlyphKerning kerning;
    kerning.first = properties.GetNumberValueFor("first");
    kerning.second = properties.GetNumberValueFor("second");
    kerning.amount = properties.GetNumberValueFor("amount");
    m_kerning.push_back(kerning);
}

FontBitmapGlyph *FontBitmapDescriptor::GetGlyph(char& c)
{
    for (auto& glyph : m_glyphs)
    {
        if (glyph.GetId() == c)
        {
            return &glyph;
        }
    }
    return nullptr;
}

int FontBitmapDescriptor::GetKerningAmount(int first, int second)
{
    for (auto& kerning :m_kerning)
    {
        if (kerning.first == first && kerning.second == second)
        {
            printf("Kerning = %d\n", kerning.amount);
            return kerning.amount;
        }
    }
    return 0;
}

#pragma mark - FontBitmapGlyph

FontBitmapGlyph::FontBitmapGlyph(int id, int x, int y, int w, int h, int xO, int yO, int xA, std::string letterName)
    : m_characterId(id)
    , m_textureRect({ {x, y}, {w, h} })
    , m_Offset({ xO, yO })
    , m_xAdvance(xA)
    , m_letterName(letterName)
    , m_drawable(nullptr)
{
}

FontBitmapGlyph::FontBitmapGlyph(KeyValueProperties& properties)
    : m_characterId(properties.GetNumberValueFor("id"))
    , m_xAdvance(properties.GetNumberValueFor("xadvance"))
    , m_letterName(properties.GetStringValueFor("letter"))
    , m_drawable(nullptr)
{
    int x = properties.GetNumberValueFor("x");
    int y = properties.GetNumberValueFor("y");
    int w = properties.GetNumberValueFor("width");
    int h = properties.GetNumberValueFor("height");
    m_textureRect = { {x, y}, {w, h} };

    int ox = properties.GetNumberValueFor("xoffset");
    int oy = properties.GetNumberValueFor("yoffset");
    m_Offset = {ox, oy};
}

#pragma mark - FontBitmapRepresentation

std::vector<std::unique_ptr<SpriteAtlasItemI>> spriteDescriptors;

FontBitmapRepresentation::FontBitmapRepresentation(std::string fntFile, std::string fontAtlas, float scale)
    : FontI(fntFile)
    , m_font(FontBitmapDescriptor(fntFile, fontAtlas))
    , m_texture(ENGINE().getTextureManager().LoadTexture(fontAtlas))
    , m_scale(scale)
    , m_alpha(1.0f)
{
    EngineProviderI& provider = ENGINE().getProvider();


    for (auto &glyph : m_font.GetGlyphs())
    {
        auto rect = glyph.GetRect();
        auto offset = glyph.GetOffset();

        auto atlasItem = new SpriteAtlasItemI(m_texture, rect.origin.x - offset.width, rect.origin.y /*- offset.height*/, rect.size.width, rect.size.height, false, "");
        spriteDescriptors.emplace_back(std::unique_ptr<SpriteAtlasItemI>(atlasItem));

        auto drawable = provider.DrawableCreate(atlasItem, m_scale);
        drawable->SetTexture(m_texture);
        drawable->SetScale(m_scale);
        drawable->GetAcceptsLight() = false;
        drawable->SetRotateable(false);
        glyph.SetDrawable(drawable);
    }
}

void FontBitmapRepresentation::SetScale(float value)
{
    m_scale = value;
    for (auto& it : m_font.GetGlyphs())
    {
        it.GetDrawable()->SetScale(value);
    }
}

void FontBitmapRepresentation::SetAlpha(float value)
{
    m_alpha = value;
    for (auto& it : m_font.GetGlyphs())
    {
        it.GetDrawable()->SetAlpha(value);
    }
}

float FontBitmapRepresentation::GetAlpha()
{
    return m_alpha;
}

void FontBitmapRepresentation::SetZPosition(float value)
{
    for (auto& it : m_font.GetGlyphs())
    {
        it.GetDrawable()->SetZPosition(value);
    }
}

void FontBitmapRepresentation::LineRunner(std::string& text, int from, int to, Origin position, float lineMultiplier, std::function<void(DrawableI*, float, float)> drawLabmda, std::function<void(float)> lineWidth)
{
    size_t len = text.length();

    if (len <= 0 && from < len && to < len)
    {
        return;
    };

    float viewportScale = ENGINE().GetViewportScale();
    auto& fontDescriptor = m_font.GetDescriptor();
    auto& charSpacing = fontDescriptor.info.spacing;
    int x = position.x;
    int y = position.y;

    int previousC = -1;
    for (int i = from; i < to; i++)
    {
        auto& c = text.at(i);

        if (auto glyph = m_font.GetGlyph(c))
        {
            Size& offset = glyph->GetOffset();
            auto drawable = glyph->GetDrawable();
            float tx = x + (viewportScale * ceil((offset.width * m_scale) - (m_font.GetKerningAmount(previousC, c) * m_scale)));
            float ty = y + ceil((offset.height * m_scale * viewportScale));

            drawLabmda(drawable, tx, ty);
            x += ceil((glyph->GetXAdvance() + charSpacing.x)) * m_scale * viewportScale;
        }

        previousC = c;
    }

    lineWidth(x);
}

void FontBitmapRepresentation::DrawAt(std::string text, float xo, float yo, int r, int g, int b, int a, TEXT_HORIZONTAL_ALIGNMENT hta, TEXT_VERTICAL_ALIGNMENT vta, Color4 colorMod, float lineMultiplier)
{
    size_t len = text.length();
    
    if (m_texture != nullptr && len > 0)
    {
        EngineProviderI& provider = ENGINE().getProvider();
        auto& fontDescriptor = m_font.GetDescriptor();

        int lineCount = 1;
        for (int i = 0; i < len; i++)
        {
            if (text.at(i) == '\n')
            {
                lineCount++;
            }
        }
        
        int x = xo;
        int y = yo;
        
        int totalHeight = lineCount * fontDescriptor.common.lineHeight * lineMultiplier * m_scale;
        
        switch (vta)
        {
            case TEXT_ALIGN_TOP:
                break;
            case TEXT_ALIGN_MIDDLE:
                y -= round(totalHeight/2);
                break;
            case TEXT_ALIGN_BOTTOM:
                y -= totalHeight;
                break;
        }

        int from = 0;
        int to = 0;

        for (int i = 0; i < len; i++)
        {
            auto& c = text.at(i);

            // Get line boundaries
            if (c == '\n')
            {
                to = i;
            }
            else if (i == len -1)
            {
                to = i + 1;
            }
            else
            {
                continue;
            }

            float lineWidth = 0;
            LineRunner(text, from, to, zeroPoint, lineMultiplier, [&](DrawableI *drawable, float tx, float ty){
            }, [&](float width){
                lineWidth = width;
            });

            point.x = x;
            point.y = y;

            switch (hta)
            {
                case TEXT_ALIGN_LEFT:
                    break;
                case TEXT_ALIGN_CENTER:
                    point.x -= lineWidth / 2.f;
                    break;
                case TEXT_ALIGN_RIGHT:
                    point.x -= lineWidth;
                    break;
            };

            LineRunner(text, from, to, point, lineMultiplier, [&](DrawableI *drawable, float tx, float ty){
                provider.DrawableRender(drawable, nullptr, tx, ty, colorMod);
            }, [&](float width) {
            });

            x = xo;
            from = to;

            y += fontDescriptor.common.lineHeight * lineMultiplier * m_scale;
        }
    };
}
