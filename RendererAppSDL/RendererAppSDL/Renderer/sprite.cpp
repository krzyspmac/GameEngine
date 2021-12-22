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
