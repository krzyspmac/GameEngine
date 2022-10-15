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

#include "sprite_representation_animated.hpp"
#include "common_engine.h"
#include "engine.hpp"
#include "general.hpp"

using namespace engine;

SpriteRepresentationAnimated::SpriteRepresentationAnimated(std::vector<SpriteAtlasItemI*> sprites, int frameAnimationDurationMs)
    : SpriteRepresentationI(1.0f)
    , m_maxWidth(0)
    , m_maxHeight(0)
    , m_frameAnimationDurationMs(frameAnimationDurationMs)
{
    auto& spriteManager = ENGINE().getSpriteRendererManager();

    for (auto& item : sprites)
    {
        auto* spriteRepresentation = (SpriteRepresentationStatic*)spriteManager.SpriteRepresentationStaticLoad(item);
        m_sprites.emplace_back(spriteRepresentation);
    }
}

SpriteRepresentationAnimated::~SpriteRepresentationAnimated()
{
    auto& spriteManager = ENGINE().getSpriteRendererManager();

    for (auto* item : m_sprites)
    {
        spriteManager.SpriteDrawUnload(item);
    }
}

SpriteRepresentationAnimated *SpriteRepresentationAnimated::CreateFromAtlas(std::vector<std::unique_ptr<SpriteAtlasItemI>>& sprites, int frameAnimationDurationMs)
{
    std::vector<SpriteAtlasItemI*> array;
    for (auto& item : sprites)
    {
        array.emplace_back(item.get());
    }

    return new SpriteRepresentationAnimated(array, frameAnimationDurationMs);
}

void SpriteRepresentationAnimated::SetPosition(Vector2 &pos)
{
    m_position = pos;
}

void SpriteRepresentationAnimated::SetScale(float value)
{
    for (auto& item : m_sprites)
    {
        item->SetScale(value);
    }
}

void SpriteRepresentationAnimated::SetAlpha(float val)
{
    for (auto& item : m_sprites)
    {
        item->SetAlpha(val);
    }
}

void SpriteRepresentationAnimated::PrepareAnimation()
{
}

void SpriteRepresentationAnimated::SetRotation(Rotation rotation)
{
    SpriteRepresentationI::SetRotation(rotation);
    
    for (auto& item : m_sprites)
    {
        item->SetRotation(rotation);
    }
}

void SpriteRepresentationAnimated::SetAcceptsLight(bool val)
{
    for (auto& item : m_sprites)
    {
        item->SetAcceptsLight(val);
    }
}

void SpriteRepresentationAnimated::SetZPosition(float zPos)
{
    for (auto& item : m_sprites)
    {
        item->SetZPosition(zPos);
    }
}

void SpriteRepresentationAnimated::SetAnimationFrameDuration(float value)
{
    m_frameAnimationDurationMs = value;
}

void SpriteRepresentationAnimated::SetColorMod(Color4 val)
{
    for (auto& item : m_sprites)
    {   item->SetColorMod(val);
    }
}

void SpriteRepresentationAnimated::DrawAt(int x, int y)
{
    Uint64 ticks = ENGINE().getProvider().GetTicks();
    Uint64 seconds = ticks / m_frameAnimationDurationMs;
    Uint64 spriteNo = seconds % m_sprites.size();
    SpriteRepresentationI *spriteItem = m_sprites.at(spriteNo);
    spriteItem->DrawAt(x, y);
}

void SpriteRepresentationAnimated::Draw()
{
    DrawAt(m_position.x, m_position.y);
}
