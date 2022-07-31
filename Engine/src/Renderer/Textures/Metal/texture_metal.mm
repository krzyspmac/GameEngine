//
//  texture_metal.cpp
//  Engine
//
//  Created by x180611 on 14/01/2022.
//

#include "texture_metal.hpp"
#include "AAPLImage.h"
#include "engine.hpp"
#include <MetalKit/MetalKit.h>

using namespace engine;

#define USES_METAL_TEXTURE_LOADING 1

TextureMetal::TextureMetal(MTL::Device *device, std::string filename)
    : TextureI(nullptr, filename, Vector2Zero)
    , m_texture(nullptr)
{
    std::string path = ENGINE().getFileAccess().GetFullPath(filename);

#if USES_METAL_TEXTURE_LOADING
    m_texture = TextureMetalTGA::CreateFrom(path, device, &m_options.flippedHorizontally, &m_options.flippedVertically);
    if (m_texture != nullptr)
    {
        SetSize(Vector2Make(m_texture->width(), m_texture->height()));
    }
    else
    {
        SetSize(Vector2Zero);
    }
#else
    if (filename.ends_with(".tga"))
    {
        TextureMetalTGA *texture = new TextureMetalTGA(path, &m_options.flippedHorizontally, &m_options.flippedVertically);
        if (texture != nullptr)
        {
            m_textureDescriptor = MTL::TextureDescriptor::alloc()->init();
            m_textureDescriptor->setPixelFormat(MTL::PixelFormatBGRA8Unorm_sRGB);
            m_textureDescriptor->setResourceOptions(MTL::ResourceStorageModeShared);
            m_textureDescriptor->setWidth(texture->GetWidth());
            m_textureDescriptor->setHeight(texture->GetHeight());
            
            m_texture = device->newTexture(m_textureDescriptor);
            
            // Calculate the number of bytes per row in the image.
            unsigned int width = texture->GetWidth();
            unsigned int height = texture->GetHeight();
            unsigned int bytesPerRow = 4 * width;
            
            MTL::Region region(0, 0, 0, width, height, 1);
            
            // Copy bytes to the texture
            m_texture->replaceRegion(region, 0, texture->GetData(), bytesPerRow);
            
            SetSize(Vector2Make(width, height));
            
            delete texture;
        }
        else
        {
            SetSize(Vector2Zero);
        }
    }
    else
    {
        printf("Not a tga file\n");
    }
#endif
}

TextureMetal::~TextureMetal()
{
    m_texture->release();
}
