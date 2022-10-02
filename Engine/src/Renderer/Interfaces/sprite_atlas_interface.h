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

#ifndef sprite_atlas_interface_h
#define sprite_atlas_interface_h

#include "texture_interface.h"
#include "sprite_interface_defs.h"
#include "vector2.hpp"
#include "size.hpp"

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
