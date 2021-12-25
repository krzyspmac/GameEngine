//
//  sprite_draw_interface.h
//  RendererAppSDL
//
//  Created by krzysp on 22/12/2021.
//

#ifndef sprite_draw_interface_h
#define sprite_draw_interface_h

#include "sprite_atlas_interface.h"

namespace engine
{

    class SpriteDrawI
    {
    public:
        SpriteDrawI(SpriteAtlasItemI *spriteAtlasItem)
            : m_sprite(spriteAtlasItem)
        { };

    public:
        virtual void Draw(int x, int y) = 0;

    protected:
        SpriteAtlasItemI *m_sprite;
    };
};

#endif /* sprite_draw_interface_h */
