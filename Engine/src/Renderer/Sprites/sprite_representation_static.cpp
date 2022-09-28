//
//  sprite_draw.cpp
//  RendererAppSDL
//
//  Created by krzysp on 22/12/2021.
//

#include "sprite_representation_static.hpp"
#include "common_engine.h"
#include "common.h"
#include "scripting_engine.hpp"

using namespace engine;

SpriteRepresentationStatic::SpriteRepresentationStatic(SpriteAtlasItemI *spriteAtlasItem)
    : SpriteRepresentationI(1.0f)
    , m_sprite(spriteAtlasItem)
{
    auto drawable = ENGINE().getProvider().DrawableCreate(spriteAtlasItem, 1.f);
    m_drawable = std::unique_ptr<DrawableSpriteI>(std::move(drawable));
}

void SpriteRepresentationStatic::DrawAt(int x, int y)
{
    EngineProviderI &provider = ENGINE().getProvider();
    provider.DrawableRender(m_drawable.get(), this, x, y);
}

void SpriteRepresentationStatic::SetPosition(Vector2 &pos)
{
    m_position = pos;
}

void SpriteRepresentationStatic::SetZPosition(float zPos)
{
    SpriteRepresentationI::SetZPosition(zPos);
    m_drawable->SetZPosition(zPos);
}

void SpriteRepresentationStatic::SetRotation(Rotation rotation)
{
    SpriteRepresentationI::SetRotation(rotation);
    m_drawable->SetRotation(rotation.angle, rotation.anchor.x, rotation.anchor.y);
}

void SpriteRepresentationStatic::SetScale(float x)
{
    SpriteRepresentationI::SetScale(x);
    m_drawable->SetScale(x);
}

void SpriteRepresentationStatic::Draw()
{
    DrawAt(m_position.x, m_position.y);
}
