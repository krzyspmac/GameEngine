//
//  drawable_sdl.cpp
//  Engine
//
//  Created by krzysp on 15/01/2022.
//

#include "drawable_sdl.hpp"
#include "engine.hpp"

using namespace engine;

DrawableSDL::DrawableSDL(SpriteAtlasItemI *atlasItem, float width, float height)
    : DrawableI(width, height)
    , m_atlasItem(atlasItem)
{
    m_texture = m_atlasItem->GetTexture();
}


DrawableTargetSDL::DrawableTargetSDL(float width, float height)
    : DrawableTargetI(width, height)
    , m_x(0)
    , m_y(0)
    , m_width(width)
    , m_height(height)
{
    EngineProviderI& provider = GetMainEngine()->getProvider();
    auto texture = provider.CreateTargetTexture(width, height);
    m_texture = texture;
//?    m_texture = m_atlasItem->GetTexture();
}
