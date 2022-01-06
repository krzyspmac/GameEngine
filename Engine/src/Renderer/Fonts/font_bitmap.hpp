//
//  font_bitmap.hpp
//  Engine
//
//  Created by krzysp on 06/01/2022.
//

#ifndef font_bitmap_hpp
#define font_bitmap_hpp

#include "common.h"
#include "key_value.hpp"
#include "font_interface.h"
#include "common_engine_impl.h"
#include "vector2.hpp"

namespace engine
{
    /**
     Defines the bitmap font properties.
     Not all properties are supported atm.
     \see https://www.angelcode.com/products/bmfont/doc/file_format.html
     */
    typedef struct
    {
        std::string face;
        size_t size;
        Vector2 spacing;
    } FontBitmapDescriptorInfo;

    typedef struct
    {
        int lineHeight;
        int base;
        int scaleW;
        int scaleH;
    } FontBitmapDescriptorCommon;

    typedef struct
    {
        FontBitmapDescriptorInfo info;
        FontBitmapDescriptorCommon common;
    } FontBitmapDescriptor;

    class FontBitmapGlyph
    {
        int m_characterId;
        Rect m_textureRect;
        Size m_Offset;
        int m_xAdvance;
        std::string m_letterName;

    public:
        FontBitmapGlyph(int id, int x, int y, int w, int h, int xO, int yO, int xA, std::string letterName);
        FontBitmapGlyph(KeyValueProperties& properties);

        auto& GetId() { return m_characterId; };
        auto& GetRect() { return m_textureRect; };
        auto& GetOffset() { return m_Offset; };
        auto& GetXAdvance() { return m_xAdvance; };
    };

    /**
     Declares a concrete instance for rendering bitmpa fonts
     using a sprite atlas sheet and a .fnt file in text format.
     */
    class FontBitmap: public FontI
    {
        FontBitmapDescriptor m_sDescriptor;
        std::vector<FontBitmapGlyph> m_glyphs;

        void Prepare(std::string fntFile);
        void BuildDescriptorFace(KeyValueProperties&);
        void BuildDescriptorCommon(KeyValueProperties&);
    public:
        /**
         Create a bitmap bit.
         @param fntFile     - path to a FNT file (in text format)
         @param fontAtlas   - path to the bitmap containing the font sprite sheet.
         */
        FontBitmap(std::string fntFile, std::string fontAtlas);

        auto& GetDescriptor() { return m_sDescriptor; };

        void DrawAt(std::string, float, float, int, int, int, int, TEXT_ALIGNMENT);
    };
};

#endif /* font_bitmap_hpp */
