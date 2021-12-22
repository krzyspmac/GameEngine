//
//  sprite_draw.hpp
//  RendererAppSDL
//
//  Created by krzysp on 22/12/2021.
//

#ifndef sprite_draw_hpp
#define sprite_draw_hpp

#include "sprite_draw_interface.h"

namespace engine
{

    class SpriteDraw: public SpriteDrawI
    {
    public:
        SpriteDraw(SpriteI *sprite, SpriteAnimationDescriptor animation);

    public:
        void Draw(int x, int y);
    };
};

#endif /* sprite_draw_hpp */
