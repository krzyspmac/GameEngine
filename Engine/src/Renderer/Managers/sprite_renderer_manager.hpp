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
#include "font_interface.h"
#include <iostream>

namespace engine
{
    /** SpriteRendererManager
        \addtogroup API_GLOBALS
     */
    /** Manages a list of sprite renderers. Those are used by the current
        scene to render the appropriate sprites at particular timeframes.
     */
    class SpriteRendererManager
    {
    public:
        /** Loads a sprite representation for a sprite atlas item descriptor.
            The result is cached. */
        SpriteRepresentationI *SpriteRepresentationStaticLoad(SpriteAtlasItemI *sprite);

        /** Loads a sprite representation for a sprite animation made up from
            individual sprite atlas items.
            The result is cached. */
        /** @private */
        SpriteRepresentationI *SpriteRepresentationAnimatedLoad(int frameAnimationDurationMs, std::vector<SpriteAtlasItemI*> sprites);

        /** Loads a sprite representation for a sprite animation made up of all the
            frames in one sprite atlas.
            The result is cached. */
        SpriteRepresentationI *SpriteRepresentationAnimatedLoad(int frameAnimationDurationMs, SpriteAtlasI*);

        /** Loads a text sprite representation.
            The result is cached. */
        SpriteRepresentationI *SpriteRepresentationTextLoad(FontI*);

        /** Unloads the sprite draw.
         */
        void SpriteDrawUnload(SpriteRepresentationI *spriteDraw);

        /** Unloads all.
         */
        void SpriteDrawDisposeAll();

    private:
        std::vector<std::unique_ptr<SpriteRepresentationI>> m_spriteDraws;

    /// ScriptingInterface
    public:
        /** @private */
        SCRIPTING_INTERFACE_HEADERS(SpriteRendererManager);
    };
};

#endif /* sprite_renderer_manager_hpp */
