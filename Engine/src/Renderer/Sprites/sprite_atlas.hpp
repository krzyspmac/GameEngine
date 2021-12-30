//
//  sprite_atlas.hpp
//  RendererAppSDL
//
//  Created by krzysp on 22/12/2021.
//

#ifndef sprite_atlas_hpp
#define sprite_atlas_hpp

#include "common.h"
#include "sprite_atlas_interface.h"
#include "scripting_engine_provider_interface.h"

namespace engine {

    class SpriteAtlas: public SpriteAtlasI
    {
    public:
        SpriteAtlas(std::string jsonFilename, std::string textureFilename);
        ~SpriteAtlas();

        SpriteAtlasItemI *GetItemForName(std::string name);

        std::string &GetFilename() { return m_filename; };

    private:
        std::string m_filename;
        TextureI *m_texture;
        std::vector<SpriteAtlasItemI> m_items;

    /// ScriptingInterface
    public:
        SCRIPTING_INTERFACE_HEADERS(SpriteAtlas);
    };
};

#endif /* sprite_atlas_hpp */
