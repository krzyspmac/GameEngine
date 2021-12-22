//
//  sprite.cpp
//  RendererAppSDL
//
//  Created by krzysp on 21/12/2021.
//

#include "sprite.hpp"
#include "common_engine.h"

using namespace engine;

Sprite::Sprite(SpriteAtlasItemI *spriteAtlasItem)
: SpriteI(spriteAtlasItem->GetTexture(), spriteAtlasItem->GetSpriteDescriptor())
{
}

void Sprite::Draw(int x, int y, int frameNumber)
{
//    GetMainEngine()->getProvider().DrawTexture(
//        m_texture,
//        x,
//        y,
//        m_spriteDescriptor.spriteSrcX + (m_spriteDescriptor.spriteWidth * frameNumber),
//        m_spriteDescriptor.spriteSrcY,
//        m_spriteDescriptor.spriteWidth,
//        m_spriteDescriptor.spriteHeight
//    );
}

void Sprite::DrawAnimated(int x, int y)
{
//    Uint32 ticks = SDL_GetTicks();
//    Uint32 seconds = ticks / m_spriteAnimationDescriptor.frameDuration;
//    Uint32 sprite = seconds % m_spriteAnimationDescriptor.frameCount;
//
//    GetMainEngine()->getProvider().DrawTexture(
//        m_texture,
//        x,
//        y,
//        m_spriteDescriptor.spriteSrcX + (m_spriteDescriptor.spriteWidth * sprite),
//        m_spriteDescriptor.spriteSrcY,
//        m_spriteDescriptor.spriteWidth,
//        m_spriteDescriptor.spriteHeight
//    );
}
