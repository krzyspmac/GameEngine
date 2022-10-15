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

#include "texture_target_metal.hpp"

using namespace engine;

TextureTargetMetal::TextureTargetMetal(MTL::Device *device, float width, float height)
    : TextureTargetI(nullptr, Vector2Make(width, height))
{
    m_textureDescriptor = MTL::TextureDescriptor::alloc()->init();
    m_textureDescriptor->setTextureType(MTL::TextureType2D);
    m_textureDescriptor->setWidth(width);
    m_textureDescriptor->setHeight(width);
    m_textureDescriptor->setPixelFormat(MTL::PixelFormatBGRA8Unorm);

    m_textureDescriptor->setUsage(MTL::TextureUsageRenderTarget | MTL::TextureUsageShaderRead);
    
    m_texture = device->newTexture(m_textureDescriptor);
}
