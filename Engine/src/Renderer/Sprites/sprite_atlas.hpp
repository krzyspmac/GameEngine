//
//  sprite_atlas.hpp
//  RendererAppSDL
//
//  Created by krzysp on 22/12/2021.
//

#ifndef sprite_atlas_hpp
#define sprite_atlas_hpp

#include "common.h"
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

#include "sprite_atlas_interface.h"

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

        /** Get the specific atlas item for the name.
         */
        SpriteAtlasItemI *GetItemForName(std::string name);

        /** Get all the sprite items */
        std::vector<std::unique_ptr<SpriteAtlasItemI>>& GetAllItems();

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
        std::vector<std::unique_ptr<SpriteAtlasItemI>> m_items;
        bool m_flippedVertically;
    };
};

#endif /* sprite_atlas_hpp */
