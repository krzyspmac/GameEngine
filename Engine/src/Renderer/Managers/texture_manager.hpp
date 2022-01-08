//
//  texture_manager.hpp
//  Engine
//
//  Created by krzysp on 08/01/2022.
//

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
