//
//  sprite_atlas_manager.hpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#ifndef sprite_atlas_manager_hpp
#define sprite_atlas_manager_hpp

#include "scripting_engine_provider_interface.h"
#include "sprite_atlas_interface.h"

namespace engine
{

    /// A manager for sprite atlases. Loads the textures, keeps them for
    /// future reference.
    _LUA_EXPOSED("SpriteAtlasManager")
    class SpriteAtlasManager
    {
    public:
        /// A concrete instance would load the sprite atlas, its texture (using ::LoadTexture) and the json
        /// file for individual sprite splices.
        _LUA_EXPOSED("spriteAtlasLoad")
        SpriteAtlasI *SpriteAtlasLoad(std::string jsonFilename, std::string textureFilename);

        ///
        _LUA_EXPOSED("spriteAtlasGet")
        SpriteAtlasI *SpriteAtlasGet(std::string jsonFilename);

        ///
        _LUA_EXPOSED("spriteAtlasUnload")
        void SpriteAtlasUnload(SpriteAtlasI *atlas);

        ///
        _LUA_EXPOSED("spriteAtlasDisposeAll")
        void SpriteAtlasDisposeAll();

    private:
        std::vector<std::unique_ptr<SpriteAtlasI>> m_atlas;

    /// ScriptingInterface
    public:
        SCRIPTING_INTERFACE_HEADERS(SpriteAtlasManager);
    };
};

#endif /* sprite_atlas_manager_hpp */
