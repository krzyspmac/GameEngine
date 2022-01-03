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
    /**
     SpriteRendererManager
     \addtogroup API_GLOBALS
     */
    /**
     Manages a list of sprite renderers. Those are used by the current
     scene to render the appropriate sprites at particular timeframes.
     */
    class SpriteRendererManager
    {
    public:
        /// Creates or gets a drawing handle for a sprite.
        /// The result is cached.
        /// \ingroup API_EXPOSED
        SpriteDrawI *SpriteDrawLoadStatic(SpriteAtlasItemI *sprite);

        /// Creates or gets a drawing handle for a sprite
        /// \ingroup API_EXPOSED
        SpriteDrawI *SpriteDrawLoadAnimated(std::vector<SpriteAtlasItemI*> sprites, int frameAnimationDurationMs);

        /// Unloads the sprite draw.
        /// \ingroup API_EXPOSED
        void SpriteDrawUnload(SpriteDrawI *spriteDraw);

        /// Unloads all.
        /// \ingroup API_EXPOSED
        void SpriteDrawDisposeAll();

    private:
        std::vector<std::unique_ptr<SpriteDrawI>> m_spriteDraws;

    /// ScriptingInterface
    public:
        /** @private */
        SCRIPTING_INTERFACE_HEADERS(SpriteRendererManager);
    };
};

#endif /* sprite_renderer_manager_hpp */
