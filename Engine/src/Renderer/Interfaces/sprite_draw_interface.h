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

    class SpriteDrawI
    {
    public:
        /// Scale applies to width and height. Does not modify x no y.
        SpriteDrawI(int scale): m_scale(scale), m_position(Vector2Zero) {};
        virtual ~SpriteDrawI() { };
        
    public:
        /**
         Draws the sprite at a given coordinates.
         */
        virtual void DrawAt(int x, int y) = 0;

        /**
         Draws the sprite at the stored coorindates that were
         previously set.
         */
        virtual void Draw() = 0;

        void SetScale(float x) { m_scale = x; };

    public:
        void SetPosition(Vector2 pos) { m_position = pos; };
        Vector2& GetPosition() { return m_position; };

        /** Set Alpha as uint 0-255 */
        void SetAlpha(uint8_t val) { m_drawable->SetAlpha((float)val/255.0f); }
        uint8_t GetAlpha() { return *m_drawable->GetAlpha() * 255; };

        /** The main drawable for this sprite */
        DrawableI* GetDrawable() { return m_drawable.get(); };
        
    protected:
        int m_scale;
        Vector2 m_position;
        std::unique_ptr<DrawableI> m_drawable;
    };
};

#endif /* sprite_draw_interface_h */
