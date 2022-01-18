//
//  texture_target_metal.hpp
//  Engine
//
//  Created by x180611 on 14/01/2022.
//

#ifndef texture_target_metal_hpp
#define texture_target_metal_hpp

#include "common.h"
#include "texture_target.hpp"

#include <Metal/Metal.hpp>

namespace engine
{

    class TextureTargetMetal: public TextureTargetI
    {
        MTL::TextureDescriptor *m_textureDescriptor;
        MTL::Texture *m_texture;
    public:
        TextureTargetMetal(MTL::Device*, float, float);
        
        MTL::Texture* GetMTLTextureHandle() { return m_texture; };
    };
};

#endif /* texture_target_metal_hpp */
