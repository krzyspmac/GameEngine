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

#ifndef sprite_draw_interface_h
#define sprite_draw_interface_h

#include "drawable_interface.h"
#include "animation_interface.hpp"

namespace engine
{

    typedef enum
    {
        SPRITE_DRAW_TYPE_BACKGROUND     = 0     // background sprites do not receive lights
      , SPRITE_DRAW_TYPE_FOREGROUND     = 1     // foreground sprites receive lights
    } SpriteDrawType;

    /** Declares interface for sprite properties that are not animatable
        but can be changed */
    class SpritePropertyManipulatorsI: public AnimatablePropertiesI
    {
    public:
        /** Control whether the object receives lights or not. If false it's
            completely lit up. */
        virtual void SetAcceptsLight(bool) = 0;
        virtual float GetAcceptsLight() = 0;

        /** Set the color mod */
        virtual void SetColorMod(Color4) = 0;
        virtual Color4& GetColorMod() = 0;
    };

    class SpriteRepresentationI: public SpritePropertyManipulatorsI
    {
    public:
        SpriteRepresentationI(int scale)
            : m_scale(scale)
            , m_position(Vector2Zero)
            , m_zPosition(0.0f)
            , m_rotation(Rotation::empty())
            , m_isDrawable(true)
            , m_colorMod({1.f, 1.f, 1.f})
            , m_type(SPRITE_DRAW_TYPE_FOREGROUND)
        { };
        
        virtual ~SpriteRepresentationI() { };
        
    public:
        /** Draws the sprite at a given coordinates. */
        virtual void DrawAt(int x, int y) = 0;

        /** Draws the sprite at the stored coorindates that were previously set.
         */
        virtual void Draw() = 0;

    public: // AnimatablePropertiesI
        float       GetScale() { return m_scale; }
        void        SetScale(float x) { m_scale = x; };
        void        SetPosition(Vector2 pos) { m_position = pos; };
        Vector2&    GetPosition() { return m_position; };
        void        SetZPosition(float zPos) { m_zPosition = zPos; };
        float&      GetZPosition() { return m_zPosition; };
        void        SetAlpha(float val) { if(m_drawable.get() != nullptr) m_drawable.get()->SetAlpha(val); };
        float       GetAlpha() { return *m_drawable.get()->GetAlpha(); };
        void        SetRotation(Rotation rotation) { m_rotation = rotation; };
        Rotation    &GetRotation() { return m_rotation; }

    public: // SpritePropertyManipulatorsI
        void SetAcceptsLight(bool val) { m_acceptsLight = val; if(m_drawable.get() != nullptr) m_drawable.get()->GetAcceptsLight() = val; };
        float GetAcceptsLight() { return m_acceptsLight; };
        void SetColorMod(Color4 val) { m_colorMod = val; if(m_drawable.get() != nullptr) m_drawable.get()->SetColorMod(val); };
        Color4& GetColorMod() { return m_colorMod; };

    public: // Drawable related

        /** Controls wheather this sprite is drawable at all. Default is yes. */
        auto& GetIsDrawable() { return m_isDrawable; };

        /** Controls the sprite type. Default is SPRITE_DRAW_TYPE_FOREGROUND */
        auto& GetType() { return m_type; };

        /** Set the main drawable for this sprite */
        void SetDrawable(std::unique_ptr<DrawableSpriteI> val) { m_drawable = std::unique_ptr<DrawableSpriteI>(std::move(val)); };

        /** The main drawable for this sprite */
        DrawableSpriteI* GetDrawable() { return m_drawable.get(); };
        
    protected:
        int m_scale;
        Vector2 m_position;
        float m_zPosition;
        Rotation m_rotation;
        bool m_acceptsLight;
        SpriteDrawType m_type;
        Color4 m_colorMod;
        bool m_isDrawable;
        std::unique_ptr<DrawableSpriteI> m_drawable;
    };
};

#endif /* sprite_draw_interface_h */
