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
#include "drawable_interface.h"

namespace engine
{

    class SpriteRepresentationStatic: public SpriteRepresentationI, public ScriptingInterface
    {
    public:
        /** @private */
        SpriteRepresentationStatic(SpriteAtlasItemI *spriteAtlasItem);
        virtual ~SpriteRepresentationStatic() { };
        
    public:
        /** Sets the scale.
         */
        void SetScale(float x);

        /** Sets the position for the sprite.
         */
        void SetPosition(Vector2 &pos);

        /** Gets the current position for the sprite.
         */
        Vector2& GetPosition() { return m_position; };

        /** Get width & size of the sprite.
         */
        Size& GetSize() { return m_sprite->GetSize(); };

        /** Get the current sprite atlas item for this sprite */
        SpriteAtlasItemI *GetSpriteAtlasItem() { return m_sprite; };

        /** Draws the sprite.
         */
        void DrawAt(int x, int y);

        /** Draws the sprite.
         */
        void Draw();

    public:

    private:
        SpriteAtlasItemI *m_sprite;

    /// ScriptingInterface
    public:
        /// @private
        SCRIPTING_INTERFACE_HEADERS(SpriteRepresentationStatic);
    };
};

#endif /* sprite_draw_hpp */
