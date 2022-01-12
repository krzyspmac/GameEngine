//
//  texture.hpp
//  RendererAppSDL
//
//  Created by krzysp on 20/12/2021.
//

#ifndef texture_hpp
#define texture_hpp

#include <stdio.h>
#include "texture_interface.h"

namespace engine
{

    class Texture: public TextureI
    {
    public:
        Texture(void *textureHandle, std::string textureName)
            : TextureI(textureHandle, textureName)
        {
        }

    };
};

#endif /* texture_hpp */
