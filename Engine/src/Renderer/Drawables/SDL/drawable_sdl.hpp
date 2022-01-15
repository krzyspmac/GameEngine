//
//  drawable_sdl.hpp
//  Engine
//
//  Created by krzysp on 15/01/2022.
//

#ifndef drawable_sdl_hpp
#define drawable_sdl_hpp

#include "common.h"
#include "drawable_interface.h"
#include "sprite_atlas_interface.h"

namespace engine
{
    /** Defines the SDL drawable that goes to the gpu. */
    class DrawableSDL: public DrawableI
    {
        SpriteAtlasItemI *m_atlasItem;
    public: // Drawable I
        DrawableSDL(SpriteAtlasItemI *atlasItem, float width, float height);

    public:
        TextureI *GetTexture();
        int &GetX() { return m_atlasItem->GetX(); };
        int &GetY() { return m_atlasItem->GetY(); };
        int &GetWidth() { return m_atlasItem->GetWidth(); };
        int &GetHeight() { return m_atlasItem->GetHeight(); };
        Size &GetSize() { return m_atlasItem->GetSize(); };

    };
};

#endif /* drawable_sdl_hpp */
