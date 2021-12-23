//
//  sprite_draw_animated.cpp
//  RendererAppSDL
//
//  Created by krzysp on 22/12/2021.
//

#include "sprite_draw_animated.hpp"
#include "common_engine.h"

using namespace engine;

SpriteDrawAnimated::SpriteDrawAnimated(SpriteI *sprite, int frameCount, int frameAnimationDurationMs)
: SpriteDrawI(sprite), m_frameCount(frameCount), m_frameAnimationDurationMs(frameAnimationDurationMs)
{

}

void SpriteDrawAnimated::Draw(int x, int y)
{
    SpriteDescriptor &descriptor = m_sprite->GetDescriptor();

    Uint32 ticks = SDL_GetTicks();
    Uint32 seconds = ticks / m_frameAnimationDurationMs;
    Uint32 spriteNo = seconds % m_frameCount;

    Uint32 frameWidth = descriptor.spriteWidth / m_frameCount;

    GetMainEngine()->getProvider().DrawTexture(
        m_sprite->GetTexture(),
        x,
        y,
        descriptor.spriteSrcX + (frameWidth * spriteNo),
        descriptor.spriteSrcY,
        frameWidth,
        descriptor.spriteHeight
    );
}
