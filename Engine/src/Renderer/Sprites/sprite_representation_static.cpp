// Copyright (c) 2022 Krzysztof Pawłowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

#include "sprite_representation_static.hpp"
#include "common_engine.h"
#include "common.h"

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
