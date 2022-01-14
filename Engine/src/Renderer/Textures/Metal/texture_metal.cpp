//
//  texture_metal.cpp
//  Engine
//
//  Created by x180611 on 14/01/2022.
//

#include "texture_metal.hpp"
#include "AAPLImage.h"
#include "engine.hpp"

using namespace engine;

TextureMetal::TextureMetal(MTL::Device *device, std::string filename)
    : TextureI(nullptr, filename, Vector2Zero)
    , m_texture(nullptr)
{
    if (filename.ends_with(".tga"))
    {
        std::string path = GetMainEngine()->getFileAccess().GetFullPath(filename);
        
        TextureMetalTGA *texture = new TextureMetalTGA(path);
        if (texture != nullptr)
        {
            m_textureDescriptor = MTL::TextureDescriptor::alloc()->init();
            m_textureDescriptor->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
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
}

TextureMetal::~TextureMetal()
{
    // TODO: memory cleanup
}
