//
//  sprite_atlas_manager_interface.h
//  Engine
//
//  Created by krzysp on 25/09/2022.
//

#ifndef sprite_atlas_manager_interface_h
#define sprite_atlas_manager_interface_h

#include "sprite_atlas_interface.h"

namespace engine
{
    /** SpriteAtlasManagerI
        \addtogroup API_GLOBALS

        A manager for sprite atlas files. Loads the textures, keeps them for
        future reference.
     */
    class SpriteAtlasManagerI
    {
    public:
        /**
         Loads sprite atlas, its texture and the json
         file for individual sprite splices.
        */
        virtual SpriteAtlasI *SpriteAtlasLoad(std::string jsonFilename, std::string textureFilename) = 0;

        /**
         Gets the specific atlas item using the name provided.
        */
        virtual SpriteAtlasI *SpriteAtlasGet(std::string jsonFilename) = 0;

        /**
        */
        virtual void SpriteAtlasUnload(SpriteAtlasI *atlas) = 0;

        /**
        */
        virtual void SpriteAtlasDisposeAll() = 0;
    };
};

#endif /* sprite_atlas_manager_interface_h */
