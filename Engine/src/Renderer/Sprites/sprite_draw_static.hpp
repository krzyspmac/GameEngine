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

    class SpriteDrawStatic: public SpriteDrawI
    {
    public:
        SpriteDrawStatic(SpriteAtlasItemI *spriteAtlasItem, int scale);

    public:
        void Draw(int x, int y);
        void Draw();

    private:
        SpriteAtlasItemI *m_sprite;

    /// ScriptingInterface
    public:
        /// @private
        SCRIPTING_INTERFACE_HEADERS(SpriteDrawStatic);
    };
};

#endif /* sprite_draw_hpp */
