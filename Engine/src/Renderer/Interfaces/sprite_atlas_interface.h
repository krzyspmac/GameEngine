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
#include "scripting_engine_provider_interface.h"
#include "common_engine_impl.h"

namespace engine {

    class SpriteAtlasItemI
    {
    public:
        SpriteAtlasItemI(TextureI *texture, int x, int y, int w, int h, bool rotated, std::string filename)
            :   m_texture(texture),
                x(x), y(y), w(w), h(h),
                m_size({w, h}),
                rotated(rotated), m_filename(filename) { };

    public:

        /// Returns the filename associated with the sprite slice.
        std::string &GetFilename() { return m_filename; };

        ///
        TextureI *GetTexture() { return m_texture; };

        ///
        int &GetX() { return x; }
        int &GetY() { return y; }
        int &GetWidth() { return w; }
        int &GetHeight() { return h; }
        Size &GetSize() { return m_size; };

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
        Size m_size;
        bool rotated;
        std::string m_filename;
        TextureI *m_texture;
    };

    class SpriteAtlasI
    {
    public:
        SpriteAtlasI(std::string jsonFilename, std::string textureFilename) { }
        virtual ~SpriteAtlasI() { };

    public:

        virtual std::string &GetFilename() = 0;

        /**
         Get the SpriteAtlasItemI if that item exists in the atlas json.
         */
        virtual SpriteAtlasItemI *GetItemForName(std::string name) = 0;
    };
};

#endif /* sprite_atlas_interface_h */
