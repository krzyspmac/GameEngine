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
#include "sprite_atlas_interface.h"
#include "texture_interface.h"

namespace engine
{
    class Sprite: public SpriteI
    {
    public:

        Sprite(TextureI *texture, SpriteDescriptor spriteDescriptor)
        : SpriteI(texture, spriteDescriptor)
        { };

        Sprite(SpriteAtlasItemI *spriteAtlasItem);
    };
}; // namespace engine

#endif /* sprite_hpp */
