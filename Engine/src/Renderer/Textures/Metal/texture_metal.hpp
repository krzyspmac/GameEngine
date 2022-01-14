//
//  texture_metal.hpp
//  Engine
//
//  Created by x180611 on 14/01/2022.
//

#ifndef texture_metal_hpp
#define texture_metal_hpp

#include "common.h"
#include "texture_interface.h"
#include "file_access_provider.h"
#include <Metal/Metal.hpp>

namespace engine
{
    class TextureMetal: public TextureI
    {
        MTL::TextureDescriptor *m_textureDescriptor;
        MTL::Texture *m_texture;
        void *m_textureBytes;
    public:
        TextureMetal(MTL::Device*, std::string filename);
        
        MTL::TextureDescriptor *GetTextureDescriptor() { return m_textureDescriptor; };
        MTL::Texture* GetTexture() { return m_texture; };
    };
};

#endif /* texture_metal_hpp */
