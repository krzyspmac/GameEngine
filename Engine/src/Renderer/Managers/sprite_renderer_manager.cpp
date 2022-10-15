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

#include "sprite_renderer_manager.hpp"
#include "sprite_representation_static.hpp"
#include "sprite_representation_animated.hpp"
#include "sprite_representation_text.hpp"
#include "engine.hpp"

using namespace engine;

SpriteRepresentationI *SpriteRendererManager::SpriteRepresentationStaticLoad(SpriteAtlasItemI *sprite)
{
    SpriteRepresentationStatic *sd = new SpriteRepresentationStatic(sprite);

    if (sd)
    {
        m_spriteDraws.emplace_back(std::move(sd));
    }
    return sd;
}

SpriteRepresentationI *SpriteRendererManager::SpriteRepresentationAnimatedLoad(int frameAnimationDurationMs, std::vector<SpriteAtlasItemI*> sprites)
{
    engine::SpriteRepresentationAnimated *sd = new SpriteRepresentationAnimated(sprites, frameAnimationDurationMs);
    if (sd)
    {
        m_spriteDraws.emplace_back(std::move(sd));
    }
    return sd;
}

SpriteRepresentationI *SpriteRendererManager::SpriteRepresentationAnimatedLoad(int frameAnimationDurationMs, SpriteAtlasI *atlas)
{
    SpriteRepresentationAnimated *sd = SpriteRepresentationAnimated::CreateFromAtlas(atlas->GetAllItems(), frameAnimationDurationMs);
    if (sd)
    {
        m_spriteDraws.emplace_back(std::move(sd));
    }
    return sd;
}

SpriteRepresentationI *SpriteRendererManager::SpriteRepresentationTextLoad(FontI *font)
{
    SpriteRepresentationText *result = new SpriteRepresentationText(font);
    if (result != nullptr)
    {   m_spriteDraws.emplace_back(std::move(result));
    }

    return result;
}

void SpriteRendererManager::SpriteDrawUnload(SpriteRepresentationI *spriteDraw)
{
    for(auto it = std::begin(m_spriteDraws); it != std::end(m_spriteDraws); ++it)
    {
        SpriteRepresentationI *item = it->get();
        if (item == spriteDraw)
        {
            m_spriteDraws.erase(it);
            break;
        }
    }
}

void SpriteRendererManager::SpriteDrawDisposeAll()
{
    m_spriteDraws.clear();
}
