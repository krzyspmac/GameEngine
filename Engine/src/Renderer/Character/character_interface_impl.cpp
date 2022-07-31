//
//  character_interface_impl.cpp
//  Engine
//
//  Created by krzysp on 16/01/2022.
//

#include "character_interface_impl.hpp"
#include "engine.hpp"

using namespace engine;

void CharacterBodyPartRendererI::PrepareDrawable()
{
    auto drawable = ENGINE().getProvider().DrawableCreate(m_bodySprite, 1);
    m_drawable = std::unique_ptr<DrawableSpriteI>(std::move(drawable));
}
