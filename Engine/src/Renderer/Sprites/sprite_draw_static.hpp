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

    /**
     \ingroup API_EXPOSED
     */
    class SpriteDrawStatic: public SpriteDrawI, public ScriptingInterface
    {
    public:
        /** @private */
        SpriteDrawStatic(SpriteAtlasItemI *spriteAtlasItem, int scale);

    public:
    public:
        /**
         Sets the scale.
         \ingroup API_EXPOSED
         */
         void SetScale(float x);

        /**
         Draws the sprite.
         \ingroup API_EXPOSED
         */
        void DrawAt(int x, int y);

        /**
         Draws the sprite.
         \ingroup API_EXPOSED
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
