//
//  texture_target_metal.cpp
//  Engine
//
//  Created by x180611 on 14/01/2022.
//

#include "texture_target_metal.hpp"

using namespace engine;

TextureTargetMetal::TextureTargetMetal(MTL::Device *device, float width, float height)
    : TextureTargetI(nullptr, Vector2Make(width, height))
{
    m_textureDescriptor = MTL::TextureDescriptor::alloc()->init();
    m_textureDescriptor->setTextureType(MTL::TextureType2D);
    m_textureDescriptor->setWidth(width);
    m_textureDescriptor->setHeight(width);
    m_textureDescriptor->setPixelFormat(MTL::PixelFormatBC7_RGBAUnorm);
    m_textureDescriptor->setUsage(MTL::TextureUsageRenderTarget | MTL::TextureUsageShaderRead);
    
    m_texture = device->newTexture(m_textureDescriptor);
}
