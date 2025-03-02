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

#ifndef font_bitmap_hpp
#define font_bitmap_hpp

#include "common.h"
#include "key_value.hpp"
#include "font_interface.h"
#include "interfaces.h"
#include "vector2.hpp"
#include "texture_interface.h"
#include "drawable_interface.h"

namespace engine
{
    /**
     Defines the bitmap font properties.
     Not all properties are supported atm.
     \see https://www.angelcode.com/products/bmfont/doc/file_format.html
     @private
     */
    typedef struct
    {
        std::string face;
        size_t size;
        Vector2 spacing;
    } FontBitmapDescriptorInfo;

    /** @private
     */
    typedef struct
    {
        int lineHeight;
        int base;
        int scaleW;
        int scaleH;
    } FontBitmapDescriptorCommon;

    /** @private
     */
    typedef struct
    {
        std::string m_textureFilename;
        FontBitmapDescriptorInfo info;
        FontBitmapDescriptorCommon common;
    } FontBitmapInfo;

    /** @private
     */
    class FontBitmapGlyph
    {
        int m_characterId;
        Rect m_textureRect;
        Size m_Offset;
        int m_xAdvance;
        std::string m_letterName;
        std::unique_ptr<DrawableSpriteI> m_drawable;
    public:
        FontBitmapGlyph(int id, int x, int y, int w, int h, int xO, int yO, int xA, std::string letterName);
        FontBitmapGlyph(KeyValueProperties& properties);

        auto& GetId() { return m_characterId; };
        auto& GetRect() { return m_textureRect; };
        auto& GetOffset() { return m_Offset; };
        auto& GetXAdvance() { return m_xAdvance; };

        void SetDrawable(std::unique_ptr<DrawableSpriteI> &drawable)
        {
            m_drawable = std::unique_ptr<DrawableSpriteI>(std::move(drawable));
        };
        auto *GetDrawable() { return m_drawable.get(); };
    };

    /** @private
     */
    typedef struct
    {
        int first;
        int second;
        int amount;
    } FontBitmapGlyphKerning;

    /**
     Declares a concrete instance for rendering bitmpa fonts
     using a sprite atlas sheet and a .fnt file in text format.
     @private
     */
    class FontBitmapDescriptor
    {
        FontBitmapInfo m_sDescriptor;
        std::vector<FontBitmapGlyph> m_glyphs;
        std::vector<FontBitmapGlyphKerning> m_kerning;

        void Prepare(std::string fntFile);
        void BuildDescriptorFace(KeyValueProperties&);
        void BuildDescriptorCommon(KeyValueProperties&);
        void BuildDescriptorKerning(KeyValueProperties&);
    public:
        /**
         Create a bitmap bit.
         @private
         @param fntFile     - path to a FNT file (in text format)
         @param fontAtlas   - path to the bitmap containing the font sprite sheet.
         */
        FontBitmapDescriptor(std::string fntFile, std::string fontAtlas);
        ~FontBitmapDescriptor() { };
        
        auto& GetDescriptor() { return m_sDescriptor; };

        FontBitmapGlyph *GetGlyph(char&);

        std::vector<FontBitmapGlyph> &GetGlyphs() { return m_glyphs; };

        int GetKerningAmount(int first, int second);
    };

    /**
     Declares the rendering engine for the font.
     */
    class FontBitmapRepresentation: public FontI
    {
        FontBitmapDescriptor m_font;
        TextureI *m_texture;
        float m_scale;
        float m_alpha;
    public:
        /**
         Create a bitmap bit.
         @param fntFile     - path to a FNT file (in text format)
         @param fontAtlas   - path to the bitmap containing the font sprite sheet.
         */
        FontBitmapRepresentation(std::string fntFile, std::string fontAtlas, float scale);

        /** @private */
        virtual ~FontBitmapRepresentation() { };

        /** Set Scale */
        void SetScale(float);
        
        /** Set Alpha */
        void SetAlpha(float);

        /** Get */
        float GetAlpha();
        
        /** Set Z-position */
        void SetZPosition(float);

        /**
         Draw the font at a given position with a given color.

         @param r       - red; 0-255
         @param g       - green; 0-255
         @param b       - blue; 0-255
         @param a       - alpha; 0-255
         @param hAlign   - left|center|right (string)
         @param vAlign   - top|middle|bottom (string)

         \code{lua}
         local font = FontManager:LoadFont("someFont.fnt", "someFont.png")
         font:DrawAt("Sample Text", 0, 0, 255, 0, 0, 255, "left")
         \endcode
         */
        void DrawAt(std::string text, float x, float y, int r, int g, int b, int a, TEXT_HORIZONTAL_ALIGNMENT hAlign, TEXT_VERTICAL_ALIGNMENT vAlign, Color4 colorMod, float lineMultiplier);

    private:
        void LineRunner(std::string& text, int from, int to, Origin position, float lineMultiplier, std::function<void(DrawableI*, float, float)> drawLabmda, std::function<void(float)> lineWidth);
    };
};

#endif /* font_bitmap_hpp */
