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

#ifndef texture_manager_hpp
#define texture_manager_hpp

#include "common.h"
#include "texture_interface.h"

namespace engine
{
    /**
     Keps a list of textures. Handles their memory.
     */
    class TextureManager
    {
        std::vector<std::unique_ptr<TextureI>> m_textures;
    public:
        /**
         Loads the texture.
         If a texture exists for a given name the existing
         texture will be returned.
         TextureManager takes the ownership of the texture and adds it to the
         textures cache. The caller/scene must remove the
         textures by using `UnloadTexture` or `DisposeAllTextures`.
         */
        TextureI *LoadTexture(std::string name);

        /**
         A concrete instance should create the texture. The texture
         *is not* added to a cache and the ownershop is passed onto the
         caller.
         */
        TextureTargetI *CreateTargetTexture(int width, int height);

        /**
         A concrete instance should get the existing texture
         by comparing texture name. Otherwise returns NULL.
         In such a case you must load the texture by using
         `LoadTexture`.
         */
        TextureI *GetTexture(std::string name);

        /**
         A concrete instance should unlaod the texture and
         remove it from the cache.
         */
        void UnloadTexture(TextureI *texture);

        /**
         A concrete instance should unlaod all the textures and
         remove them from the cache.
         */
        void DisposeAllTextures();

    };
};

#endif /* texture_manager_hpp */
