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

#ifndef texture_metal_hpp
#define texture_metal_hpp

#include "common.h"
#include "texture_interface.h"
#include "file_access_provider.h"
#include <Metal/Metal.hpp>

namespace engine
{
    typedef struct
    {
        bool flippedHorizontally;
        bool flippedVertically;
    } TextureMetalOptions;

    class TextureMetal: public TextureI
    {
        MTL::TextureDescriptor *m_textureDescriptor;
        MTL::Texture *m_texture;
        TextureMetalOptions m_options;
    public:
        TextureMetal(MTL::Device*, std::string filename);
        virtual ~TextureMetal();
        
        MTL::TextureDescriptor *GetTextureDescriptor() { return m_textureDescriptor; };
        MTL::Texture* GetMTLTextureHandle() { return m_texture; };
        TextureMetalOptions *GetOptions() { return &m_options; };
    };
};

#endif /* texture_metal_hpp */
