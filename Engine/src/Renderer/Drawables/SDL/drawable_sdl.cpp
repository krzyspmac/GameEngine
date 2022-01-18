//
//  drawable_sdl.cpp
//  Engine
//
//  Created by krzysp on 15/01/2022.
//

#include "drawable_sdl.hpp"
#include "engine.hpp"

using namespace engine;

DrawableSDL::DrawableSDL(SpriteAtlasItemI *atlasItem)
    : DrawableSpriteI(atlasItem)
{
    m_texture = m_atlasItem->GetTexture();
}

bool DrawableSDL::CanDraw()
{
    return true;
}

DrawableTargetSDL::DrawableTargetSDL(float width, float height)
    : DrawableTargetI(width, height)
{
    EngineProviderI& provider = GetMainEngine()->getProvider();
    auto texture = provider.CreateTargetTexture(width, height);
    m_texture = texture;
}

bool DrawableTargetSDL::CanDraw()
{
    return true;
}
