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
        /// Scale applies to width and height. Does not modify x no y.
        SpriteDrawI(int scale): m_scale(scale) {};

    public:
        virtual void Draw(int x, int y) = 0;

    protected:
        int m_scale;
    };
};

#endif /* sprite_draw_interface_h */
