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
        bool m_flippedHorizontally;
    public: // Drawable I
        DrawableSDL(SpriteAtlasItemI *atlasItem, float width, float height);

        bool IsTextureCoordinatesFlippedHorizontally();
        void SetTextureCoordinatesFlippedHorizontally(bool);

    public:
        SpriteAtlasItemI *GetSpriteItem() { return m_atlasItem; };
        
        int GetX() { return m_atlasItem->GetX(); };
        int GetY() { return m_atlasItem->GetY(); };
        int GetWidth() { return m_atlasItem->GetWidth(); };
        int GetHeight() { return m_atlasItem->GetHeight(); };
        Size GetSize() { return m_atlasItem->GetSize(); };

    };

    /** Defines a concrete metal class for the target drawable that is capable of
        accepting the render pass as its input.
     */
    class DrawableTargetSDL: public DrawableTargetI
    {
        int m_x;
        int m_y;
        int m_width;
        int m_height;
        bool m_flippedHorizontally;
    public: // Drawable I
        DrawableTargetSDL(float width, float height);

        bool IsTextureCoordinatesFlippedHorizontally();
        void SetTextureCoordinatesFlippedHorizontally(bool);

    public: // Overrides
        int GetX() { return m_x; };
        int GetY() { return m_y; };
        int GetWidth() { return m_width; };
        int GetHeight() { return m_height; };
        Size GetSize() { return { m_width, m_height}; };
    };
};

#endif /* drawable_sdl_hpp */
