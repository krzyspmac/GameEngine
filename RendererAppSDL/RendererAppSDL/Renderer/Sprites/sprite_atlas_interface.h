//
//  sprite_atlas_interface.h
//  RendererAppSDL
//
//  Created by krzysp on 22/12/2021.
//

#ifndef sprite_atlas_interface_h
#define sprite_atlas_interface_h

#include "texture_interface.h"
#include "sprite_interface_defs.h"

namespace engine {

    class SpriteAtlasItemI
    {
    public:
        SpriteAtlasItemI(TextureI *texture, int x, int y, int w, int h, bool rotated, std::string filename): m_texture(texture), x(x), y(y), w(w), h(h), rotated(rotated), m_filename(filename) { };

    public:

        /// Returns the filename associated with the sprite slice.
        std::string &GetFilename() { return m_filename; };

        ///
        TextureI *GetTexture() { return m_texture; };

        ///
        SpriteDescriptor GetSpriteDescriptor()
        {
            SpriteDescriptor sp;
            sp.spriteSrcX = x;
            sp.spriteSrcY = y;
            sp.spriteWidth = w;
            sp.spriteHeight = h;
            return sp;
        };

    private:
        int x;
        int y;
        int w;
        int h;
        bool rotated;
        std::string m_filename;
        TextureI *m_texture;
    };

    class SpriteAtlasI
    {
    public:
        SpriteAtlasI(std::string jsonFilename, std::string textureFilename) { }

    public:
        virtual std::string &GetFilename() = 0;

        virtual SpriteAtlasItemI *GetItemForName(std::string name) = 0;
    };
};

#endif /* sprite_atlas_interface_h */
