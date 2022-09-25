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
#include "interfaces.h"

namespace engine
{

    /** Declares an interface that holds information on a particular sprite atlas item
        loaded using SpriteAtlasI.
     */
    class SpriteAtlasItemI
    {
    public:
        SpriteAtlasItemI(TextureI *texture, int x, int y, int w, int h, bool rotated, std::string filename)
            : m_texture(texture)
            , x(x), y(y), w(w), h(h)
            , m_size({w, h})
            , rotated(rotated)
            , m_filename(filename)
            , m_flippedVertically(false)
        { };

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
        RectF GetTextureCoordinates() { return {(float)x, (float)y, (float)w, (float)h}; };

        /** Mark this sprite atlas as using a flipped texture. For compatibility issues.
            @private
         */
        void SetFlippedVertically(bool val) { m_flippedVertically = val; };

        /** */
        bool GetFlippedVertically() { return m_flippedVertically; };

    private:
        int x;
        int y;
        int w;
        int h;
        Size m_size;
        bool rotated;
        std::string m_filename;
        TextureI *m_texture;
        bool m_flippedVertically;
    };

    /** Declares an abstraction that defines a sprite atlas loaded from a file.
     */
    class SpriteAtlasI
    {
    public:
        SpriteAtlasI(std::string jsonFilename, std::string textureFilename) { }
        virtual ~SpriteAtlasI() { };

    public:

        virtual std::string &GetFilename() = 0;

        /** Get the SpriteAtlasItemI if that item exists in the atlas json.
         */
        virtual SpriteAtlasItemI *GetItemForName(std::string name) = 0;

        /** Get all the sprites */
        virtual std::vector<std::unique_ptr<SpriteAtlasItemI>>& GetAllItems() = 0;

        /** Mark this sprite atlas as using a flipped texture. For compatibility issues.
            @private
         */
        virtual void SetFlippedVertically(bool val) = 0;

        /** */
        virtual bool GetFlippedVertically() = 0;
    };
};

#endif /* sprite_atlas_interface_h */
