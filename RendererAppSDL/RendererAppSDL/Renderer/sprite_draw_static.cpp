//
//  sprite_draw.cpp
//  RendererAppSDL
//
//  Created by krzysp on 22/12/2021.
//

#include "sprite_draw_static.hpp"
#include "common_engine.h"

using namespace engine;

SpriteDrawStatic::SpriteDrawStatic(SpriteI *sprite)
    : SpriteDrawI(sprite)
{

}

void SpriteDrawStatic::Draw(int x, int y)
{
//    if (m_animation.frameCount < 1)
//    {
        SpriteDescriptor &descriptor = m_sprite->GetDescriptor();

        GetMainEngine()->getProvider().DrawTexture(
            m_sprite->GetTexture(),
            x,
            y,
            descriptor.spriteSrcX,
            descriptor.spriteSrcY,
            descriptor.spriteWidth,
            descriptor.spriteHeight
        );
//    }
//    else
//    {
//        SpriteDescriptor &descriptor = m_sprite->GetDescriptor();
//
//        Uint32 ticks = SDL_GetTicks();
//        Uint32 seconds = ticks / m_animation.frameDuration;
//        Uint32 spriteNo = seconds % m_animation.frameCount;
//
//        GetMainEngine()->getProvider().DrawTexture(
//            m_sprite->GetTexture(),
//            x,
//            y,
//            descriptor.spriteSrcX + (descriptor.spriteWidth * spriteNo),
//            descriptor.spriteSrcY,
//            descriptor.spriteWidth,
//            descriptor.spriteHeight
//        );
//    }
}
