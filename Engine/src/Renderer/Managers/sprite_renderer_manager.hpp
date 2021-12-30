//
//  sprite_renderer_manager.hpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#ifndef sprite_renderer_manager_hpp
#define sprite_renderer_manager_hpp

#include "scripting_engine_provider_interface.h"
#include "sprite_draw_interface.h"
#include <iostream>

namespace engine
{
    class SpriteRendererManager
    {
    public:
        /// Creates or gets a drawing handle for a sprite.
        /// The result is cached.
        _LUA_EXPOSED("spriteDrawLoadStatic")
        SpriteDrawI *SpriteDrawLoadStatic(SpriteAtlasItemI *sprite, int scale);

        /// Creates or gets a drawing handle for a sprite
        _LUA_EXPOSED("spriteDrawLoadAnimated")
        SpriteDrawI *SpriteDrawLoadAnimated(std::vector<SpriteAtlasItemI*> sprites, int frameAnimationDurationMs, int scale);

        /// Unloads the sprite draw.
        _LUA_EXPOSED("spriteDrawUnload")
        void SpriteDrawUnload(SpriteDrawI *spriteDraw);

        /// Unloads all.
        _LUA_EXPOSED("spriteDrawDisposeAll")
        void SpriteDrawDisposeAll();

    private:
        std::vector<std::unique_ptr<SpriteDrawI>> m_spriteDraws;

    /// ScriptingInterface
    public:
        SCRIPTING_INTERFACE_HEADERS(SpriteRendererManager);
    };
};

#endif /* sprite_renderer_manager_hpp */
