//
//  sprite_draw_animated.cpp
//  RendererAppSDL
//
//  Created by krzysp on 22/12/2021.
//

#include "sprite_draw_animated.hpp"
#include "common_engine.h"

using namespace engine;

SpriteDrawAnimated::SpriteDrawAnimated(std::vector<SpriteAtlasItemI*> sprites, int frameAnimationDurationMs, int scale)
: SpriteDrawI(scale), m_sprites(sprites), m_maxWidth(0), m_maxHeight(0), m_frameAnimationDurationMs(frameAnimationDurationMs)
{
    PrepareAnimation();
}

void SpriteDrawAnimated::PrepareAnimation()
{
    m_maxWidth = 0;
    m_maxHeight = 0;

    for (int i = 0; i < m_sprites.size(); i++)
    {
        SpriteAtlasItemI *item = m_sprites.at(i);
        m_maxWidth = std::max(m_maxWidth, item->getWidth());
        m_maxHeight = std::max(m_maxHeight, item->getHeight());
    }
}

void SpriteDrawAnimated::Draw(int x, int y)
{
    Uint64 ticks = GetMainEngine()->getProvider().GetTicks();
    Uint64 seconds = ticks / m_frameAnimationDurationMs;
    Uint64 spriteNo = seconds % m_sprites.size();
    SpriteAtlasItemI *spriteItem = m_sprites.at(spriteNo);

    GetMainEngine()->getProvider().DrawTexture(
       spriteItem->GetTexture(),
        x + ceil(m_scale *((m_maxWidth - spriteItem->getWidth())/2)),
        y + ceil(m_scale *((m_maxHeight - spriteItem->getHeight())/2)),
        spriteItem->getX(),
        spriteItem->getY(),
        spriteItem->getWidth(),
        spriteItem->getHeight(),
        m_scale
    );
}
