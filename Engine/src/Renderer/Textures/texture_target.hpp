//
//  texture_target.hpp
//  Engine
//
//  Created by krzysp on 26/12/2021.
//

#ifndef texture_target_hpp
#define texture_target_hpp

#include "texture_interface.h"

namespace engine
{

    class TextureTarget: public TextureTargetI
    {
    public:
        TextureTarget(void *textureHandle);
    };
};

#endif /* texture_target_hpp */
