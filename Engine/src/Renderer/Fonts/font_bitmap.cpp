//
//  font_bitmap.cpp
//  Engine
//
//  Created by krzysp on 06/01/2022.
//

#include "font_bitmap.hpp"
#include "key_value.hpp"
#include "engine.hpp"

using namespace engine;

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

    std::unique_ptr<FileStreamI> stream(GetMainEngine()->getFileAccess().GetAccess(fntFile.c_str()));

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
    , m_textureRect({ {x, }, {w, h} })
    , m_Offset({ xO, yO })
    , m_xAdvance(xA)
    , m_letterName(letterName)
{
}

FontBitmapGlyph::FontBitmapGlyph(KeyValueProperties& properties)
    : m_characterId(properties.GetNumberValueFor("id"))
    , m_xAdvance(properties.GetNumberValueFor("xadvance"))
    , m_letterName(properties.GetStringValueFor("letter"))
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

FontBitmapRepresentation::FontBitmapRepresentation(std::string fntFile, std::string fontAtlas)
    : FontI(fntFile)
    , m_font(FontBitmapDescriptor(fntFile, fontAtlas))
    , m_texture(GetMainEngine()->getTextureManager().LoadTexture(fontAtlas))
{

}

void FontBitmapRepresentation::DrawAt(std::string text, float xo, float yo, int r, int g, int b, int a, TEXT_ALIGNMENT ta)
{
    if (m_texture != nullptr)
    {
        EngineProviderI& provider = GetMainEngine()->getProvider();
        auto& fontDescriptor = m_font.GetDescriptor();
        auto& charSpacing = fontDescriptor.info.spacing;
        float scale = 0.75;

//        SDL_SetTextureColorMod((SDL_Texture*)m_texture->getTextureHandle(), (Uint8)200, (Uint8)0, (Uint8)0);

        int x = xo;
        int y = yo;

        int previousC = -1;
        for (auto& c: text)
        {
            if (c == '\n')
            {
                x = xo;
                y += fontDescriptor.common.lineHeight;
                previousC = -1;
                continue;
            }

            if (auto glyph = m_font.GetGlyph(c))
            {
                Rect& r = glyph->GetRect();
                Size& offset = glyph->GetOffset();

                provider.DrawTexture(m_texture,
                                     x + (offset.width * scale) - (m_font.GetKerningAmount(previousC, c) * scale),
                                     y + (offset.height * scale),
                                     r.origin.x,
                                     r.origin.y,
                                     r.size.width,
                                     r.size.height,
                                     scale);

                x += (glyph->GetXAdvance() + charSpacing.x) * scale;
            }

            previousC = c;
        }
    };
}
