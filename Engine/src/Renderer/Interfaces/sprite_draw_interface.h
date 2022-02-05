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
      , SPRITE_DRAW_TYPE_LIGHT          = 2     // light sprites are drawn on the screen
                                                // in one pass and applied on top of
                                                // forground objects
    } SpriteDrawType;

    class SpriteDrawI
    {
    public:
        /// Scale applies to width and height. Does not modify x no y.
        SpriteDrawI(int scale)
            : m_scale(scale)
            , m_position(Vector2Zero)
            , m_isDrawable(true)
            , m_type(SPRITE_DRAW_TYPE_FOREGROUND)
        { };
        
        virtual ~SpriteDrawI() { };
        
    public:
        /** Draws the sprite at a given coordinates. */
        virtual void DrawAt(int x, int y) = 0;

        /** Draws the sprite at the stored coorindates that were previously set.
         */
        virtual void Draw() = 0;

        void SetScale(float x) { m_scale = x; };

    public:
        /** Position this sprite in game coordinates */
        void SetPosition(Vector2 pos) { m_position = pos; };

        /** Get this sprite's position in game coordinates */
        Vector2& GetPosition() { return m_position; };

        /**
         Sets the alpha. Values range from 0-1.
         Default value is 1.
         */
        void SetAlpha(float val) { m_drawable.get()->SetAlpha(val); };

        /**
         Gets the curernt alpha. Values range from 0-1.
         Default value is 1.
         */
        float GetAlpha() { return *m_drawable.get()->GetAlpha(); };

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
        SpriteDrawType m_type;
        bool m_isDrawable;
        std::unique_ptr<DrawableSpriteI> m_drawable;
    };
};

#endif /* sprite_draw_interface_h */
