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
    , m_texture(GetMainEngine()->getTextureManager().LoadTexture(fontAtlas))
    , m_scale(scale)
{
    EngineProviderI& provider = GetMainEngine()->getProvider();


    for (auto &glyph : m_font.GetGlyphs())
    {
        auto rect = glyph.GetRect();
        auto offset = glyph.GetOffset();

//        float xxx = 40;
//        rect.origin.x -= xxx;
//        rect.origin.y -= xxx;
//        rect.size.width += 2*xxx;
//        rect.size.height += 2*xxx;

        auto atlasItem = new SpriteAtlasItemI(m_texture, rect.origin.x - offset.width, rect.origin.y /*- offset.height*/, rect.size.width, rect.size.height, false, "");
        spriteDescriptors.emplace_back(std::unique_ptr<SpriteAtlasItemI>(atlasItem));

        auto drawable = provider.DrawableCreate(atlasItem, m_scale);
        drawable->SetTexture(m_texture);
        drawable->SetScale(m_scale);
        glyph.SetDrawable(drawable);
    }
}

void FontBitmapRepresentation::DrawAt(std::string text, float xo, float yo, int r, int g, int b, int a, TEXT_ALIGNMENT ta)
{
    if (m_texture != nullptr)
    {
        EngineProviderI& provider = GetMainEngine()->getProvider();
        auto& fontDescriptor = m_font.GetDescriptor();
        auto& charSpacing = fontDescriptor.info.spacing;

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
                Size& offset = glyph->GetOffset();
                auto drawable = glyph->GetDrawable();
                float tx = x + ceil((offset.width * m_scale) - (m_font.GetKerningAmount(previousC, c) * m_scale));
                float ty = y + ceil((offset.height * m_scale * 2));

                provider.DrawableRender(drawable, tx, ty);
                x += ceil((glyph->GetXAdvance()*2 + charSpacing.x) * m_scale);
            }

            previousC = c;
        }
    };
}

SCRIPTING_INTERFACE_IMPL_NAME(FontBitmapRepresentation);

static int lua_FontBitmapRepresentation_DrawText(lua_State *L)
{
    FontBitmapRepresentation *font = ScriptingEngineI::GetScriptingObjectPtr<FontBitmapRepresentation>(L, 1);

    const char *text = lua_tostring(L, 2);
    int x = lua_tonumber(L, 3);
    int y = lua_tonumber(L, 4);
    int r = lua_tonumber(L, 5);
    int g = lua_tonumber(L, 6);
    int b = lua_tonumber(L, 7);
    int a = lua_tonumber(L, 8);
    //const char *align = lua_tostring(L, 9); // not yet supported

    font->DrawAt(text, x, y, r, g, b, a, TEXT_ALIGN_LEFT);
    return 0;
}

std::vector<luaL_Reg> FontBitmapRepresentation::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "DrawAt", &lua_FontBitmapRepresentation_DrawText}
    });
    return result;
}
