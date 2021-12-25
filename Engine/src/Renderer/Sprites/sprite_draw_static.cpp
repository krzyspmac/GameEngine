//
//  sprite_draw.cpp
//  RendererAppSDL
//
//  Created by krzysp on 22/12/2021.
//

#include "sprite_draw_static.hpp"
#include "common_engine.h"

using namespace engine;

SpriteDrawStatic::SpriteDrawStatic(SpriteAtlasItemI *spriteAtlasItem)
    : SpriteDrawI(spriteAtlasItem)
{

}

void SpriteDrawStatic::Draw(int x, int y)
{
    GetMainEngine()->getProvider().DrawTexture(
       m_sprite->GetTexture(),
       x,
       y,
       m_sprite->getX(),
       m_sprite->getY(),
       m_sprite->getWidth(),
       m_sprite->getHeight()
    );
}
