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
#include "texture_interface.h"
#include "scripting_engine_provider_interface.h"
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
        
        /** Set Z-position */
        void SetZPosition(float);

        /**
         Draw the font at a given position with a given color.

         @param r       - red; 0-255
         @param g       - green; 0-255
         @param b       - blue; 0-255
         @param a       - alpha; 0-255
         @param align   - left|center|right (string)

         \code{lua}
         local font = FontManager:LoadFont("someFont.fnt", "someFont.png")
         font:DrawAt("Sample Text", 0, 0, 255, 0, 0, 255, "left")
         \endcode
         */
        void DrawAt(std::string text, float x, float y, int r, int g, int b, int a, TEXT_ALIGNMENT align, Color4 colorMod, float lineMultiplier);

    private:
        void LineRunner(std::string& text, int from, int to, Origin position, float lineMultiplier, std::function<void(DrawableI*, float, float)> drawLabmda, std::function<void(float)> lineWidth);

    private: /** scripting */
        /** @private */
        SCRIPTING_INTERFACE_HEADERS(FontBitmapRepresentation);
    };
};

#endif /* font_bitmap_hpp */
