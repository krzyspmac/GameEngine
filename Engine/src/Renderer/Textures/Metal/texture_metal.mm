// Copyright (c) 2022 Krzysztof Pawłowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

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
