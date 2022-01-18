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

namespace engine
{
    /**
     */
    class SpriteAtlas: public SpriteAtlasI
    {
    public:
        /** @private */
        SpriteAtlas(std::string jsonFilename, std::string textureFilename);

        /** @private */
        virtual ~SpriteAtlas();

        /**
         Get the specific atlas item for the name.
         */
        SpriteAtlasItemI *GetItemForName(std::string name);

        /** @private */
        std::string &GetFilename() { return m_filename; };

        /** Mark the texture using this atlas as flipped vertically.
            For compatibility reasons. If you see your textures
            being flipped on the Y-axis use :SetFlippedVertically(true)
         */
        void SetFlippedVertically(bool val);
        bool GetFlippedVertically();
    private:
        std::string m_filename;
        TextureI *m_texture;
        std::vector<SpriteAtlasItemI> m_items;
        bool m_flippedVertically;

    /// ScriptingInterface
    public:
        /** @private */
        SCRIPTING_INTERFACE_HEADERS(SpriteAtlas);
    };
};

#endif /* sprite_atlas_hpp */
