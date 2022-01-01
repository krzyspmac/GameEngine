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
    /**
     SpriteAtlasManager
     \addtogroup API_GLOBALS
     */
    /**
     A manager for sprite atlases. Loads the textures, keeps them for
     future reference.
     */
    class SpriteAtlasManager
    {
    public:
        /**
         Loads sprite atlas, its texture and the json
         file for individual sprite splices.
        */
        SpriteAtlasI *SpriteAtlasLoad(std::string jsonFilename, std::string textureFilename);

        /**
         Gets the specific atlas item using the name provided.
        */
        SpriteAtlasI *SpriteAtlasGet(std::string jsonFilename);

        /**
        */
        void SpriteAtlasUnload(SpriteAtlasI *atlas);

        /**
        */
        void SpriteAtlasDisposeAll();

    private:
        std::vector<std::unique_ptr<SpriteAtlasI>> m_atlas;

    /// ScriptingInterface
    public:
        /** @private */
        SCRIPTING_INTERFACE_HEADERS(SpriteAtlasManager);
    };
};

#endif /* sprite_atlas_manager_hpp */
