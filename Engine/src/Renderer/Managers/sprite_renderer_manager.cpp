//
//  sprite_renderer_manager.cpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

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
