//
//  sprite_backbuffer.cpp
//  Engine
//
//  Created by krzysp on 16/01/2022.
//

#include "sprite_draw_backbuffer.hpp"
#include "engine.hpp"

using namespace engine;

SpriteDrawBackbuffer::SpriteDrawBackbuffer(float width, float height)
    : SpriteRepresentationI(1)
{
    EngineProviderI& provider = ENGINE().getProvider();
    auto drawable = provider.DrawableTargetCreate(width, height);
//    m_drawable = std::unique_ptr<DrawableI>(std::move((DrawableI*)drawable));

    m_targetTexture = provider.CreateTargetTexture(width, height);
}

TextureTargetI *SpriteDrawBackbuffer::GetTargetTexture()
{
    return m_targetTexture;
}
