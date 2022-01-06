//
//  sprite_draw.hpp
//  RendererAppSDL
//
//  Created by krzysp on 22/12/2021.
//

#ifndef sprite_draw_hpp
#define sprite_draw_hpp

#include "scripting_engine_provider_interface.h"
#include "sprite_draw_interface.h"

namespace engine
{

    class SpriteDrawStatic: public SpriteDrawI, public ScriptingInterface
    {
    public:
        /** @private */
        SpriteDrawStatic(SpriteAtlasItemI *spriteAtlasItem, int scale);

    public:
    public:
        /**
         Sets the scale.
         */
        void SetScale(float x);

        /**
         Sets the position for the sprite.
         */
        void SetPosition(Vector2 &pos) { m_position = pos; };

        /**
         Gets the current position for the sprite.
         */
        Vector2& GetPosition() { return m_position; };

        /**
         Sets the alpha. Values range from 0-255.
         Default value is 255.
         */
        void SetAlpha(uint8_t val) { SpriteDrawI::SetAlpha(val); };

        /**
         Gets the curernt alpha. Values range from 0-255.
         Default value is 255.
         */
        uint8_t GetAlpha() { return SpriteDrawI::GetAlpha(); };

        /**
         Get width & size of the sprite.
         */
        Size& GetSize() { return m_sprite->GetSize(); };

        /**
         Draws the sprite.
         */
        void DrawAt(int x, int y);

        /**
         Draws the sprite.
         */
        void Draw();
    public:

    private:
        SpriteAtlasItemI *m_sprite;

    /// ScriptingInterface
    public:
        /// @private
        SCRIPTING_INTERFACE_HEADERS(SpriteDrawStatic);
    };
};

#endif /* sprite_draw_hpp */
