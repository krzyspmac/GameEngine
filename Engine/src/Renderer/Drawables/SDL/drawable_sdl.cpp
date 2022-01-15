//
//  drawable_sdl.cpp
//  Engine
//
//  Created by krzysp on 15/01/2022.
//

#include "drawable_sdl.hpp"

using namespace engine;

DrawableSDL::DrawableSDL(SpriteAtlasItemI *atlasItem, float width, float height)
    : DrawableI(width, height)
    , m_atlasItem(atlasItem)
{
}

TextureI *DrawableSDL::GetTexture()
{
    return m_atlasItem->GetTexture();
}
