//
//  font_bitmap.cpp
//  Engine
//
//  Created by krzysp on 06/01/2022.
//

#include "font_bitmap.hpp"
#include "key_value.hpp"

using namespace engine;

FontBitmap::FontBitmap(std::string fntFile, std::string fontAtlas)
    : FontI(fntFile)
{
    Prepare(fntFile);
}

void FontBitmap::Prepare(std::string fntFile)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(fntFile.c_str(), "r");
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
    }

    fclose(fp);
    if (line)
    {
        free(line);
    }
}

void FontBitmap::BuildDescriptorFace(KeyValueProperties& properties)
{
    m_sDescriptor.info.face = properties.GetStringValueFor("face");
    m_sDescriptor.info.size = properties.GetNumberValueFor("size");
    m_sDescriptor.info.spacing = properties.GetVectorValueFor("spacing");
}

void FontBitmap::BuildDescriptorCommon(KeyValueProperties& properties)
{
    m_sDescriptor.common.lineHeight = properties.GetNumberValueFor("lineHeight");
    m_sDescriptor.common.base = properties.GetNumberValueFor("base");
    m_sDescriptor.common.scaleW = properties.GetNumberValueFor("scaleW");
    m_sDescriptor.common.scaleH = properties.GetNumberValueFor("scaleH");
}

void FontBitmap::DrawAt(std::string, float, float, int, int, int, int, TEXT_ALIGNMENT)
{

}

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
