//
//  sprite.hpp
//  RendererAppSDL
//
//  Created by krzysp on 21/12/2021.
//

#ifndef sprite_hpp
#define sprite_hpp

#include "common.h"
#include "sprite_interface.h"

namespace engine
{
    class Sprite: public SpriteI
    {
    public:
        Sprite(TextureI *texture, SpriteDescriptor spriteDescriptor)
            : SpriteI(texture, spriteDescriptor)
        { };

        /// Ask the engine provider to draw the sprite.
        void Draw(int x, int y, int frameNumber = 0);

        /// Draw the sprite animated.
        void DrawAnimated(int x, int y);
    };
}; // namespace engine

#endif /* sprite_hpp */
