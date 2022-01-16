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
    , m_flippedHorizontally(false)
{
    m_texture = m_atlasItem->GetTexture();
}

void DrawableSDL::SetTextureCoordinatesFlippedHorizontally(bool flipped)
{
    m_flippedHorizontally = flipped;
}

bool DrawableSDL::IsTextureCoordinatesFlippedHorizontally()
{
    return m_flippedHorizontally;
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
}

void DrawableTargetSDL::SetTextureCoordinatesFlippedHorizontally(bool flipped)
{
    m_flippedHorizontally = flipped;
}

bool DrawableTargetSDL::IsTextureCoordinatesFlippedHorizontally()
{
    return m_flippedHorizontally;
}
