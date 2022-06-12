//
//  sprite_draw_interface.h
//  RendererAppSDL
//
//  Created by krzysp on 22/12/2021.
//

#ifndef sprite_draw_interface_h
#define sprite_draw_interface_h

#include "sprite_atlas_interface.h"
#include "drawable_interface.h"
#include "common_engine_impl.h"

namespace engine
{

    typedef enum
    {
        SPRITE_DRAW_TYPE_BACKGROUND     = 0     // background sprites do not receive lights
      , SPRITE_DRAW_TYPE_FOREGROUND     = 1     // foreground sprites receive lights
    } SpriteDrawType;

    class SpriteRepresentationI
    {
    public:
        SpriteRepresentationI(int scale)
            : m_scale(scale)
            , m_position(Vector2Zero)
            , m_zPosition(0.0f)
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

    public:
        /** Scale getter */
        float GetScale() { return m_scale; }

        /** Scale setter */
        void SetScale(float x) { m_scale = x; };

        /** Position this sprite in x,y axis game coordinates */
        void SetPosition(Vector2 pos) { m_position = pos; };
        
        /** Get this sprite's position in game coordinates */
        Vector2& GetPosition() { return m_position; };
        
        /** Set the z-axis position.
            Possible values range from 0.0 to 1.0, 0.0 being closest to the "camera" and
            1.0 being further away. Of two object: one being at 1.0 and one being at 0.0
            the one at 0.0 will overlap the one at 1.0.
            */
        void SetZPosition(float zPos) { m_zPosition = zPos; };

        /** Get the z-axis position */
        float& GetZPosition() { return m_zPosition; };

        /** Sets the alpha. Values range from 0-1.
            Default value is 1.
         */
        void SetAlpha(float val) { if(m_drawable.get() != nullptr) m_drawable.get()->SetAlpha(val); };

        /** Gets the curernt alpha. Values range from 0-1.
            Default value is 1.
         */
        float GetAlpha() { return *m_drawable.get()->GetAlpha(); };

        /** Control whether the object receives lights or not. If false it's
            completely lit up. */
        auto& GetAcceptsLight() { return m_acceptsLight; };

        /** Lighting setter */
        void SetAcceptsLight(bool val) { m_acceptsLight = val; if(m_drawable.get() != nullptr) m_drawable.get()->GetAcceptsLight() = val; };

        /** Set the color mod */
        void SetColorMod(Color4 val) { m_colorMod = val; if(m_drawable.get() != nullptr) m_drawable.get()->SetColorMod(val); };

        /** Get the color mod */
        Color4 GetColorMod() { return m_colorMod; };

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
        bool m_acceptsLight;
        SpriteDrawType m_type;
        Color4 m_colorMod;
        bool m_isDrawable;
        std::unique_ptr<DrawableSpriteI> m_drawable;
    };
};

#endif /* sprite_draw_interface_h */
