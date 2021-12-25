//
//  character.cpp
//  Engine
//
//  Created by krzysp on 25/12/2021.
//

#include "character.hpp"
#include "common_engine.h"

using namespace engine;

Character::Character(SpriteAtlasI *characterAtlas, int scale)
: CharacterI(characterAtlas, scale), m_headOffsetX(0), m_headOffsetY(0)
{

}

void Character::SetWalkR(std::vector<SpriteAtlasItemI*> &sprites, int delay)
{
    CharacterWalkRenderer *walkRenderer = new CharacterWalkRenderer();
    walkRenderer->SetBodyAnimationDelay(delay);

    for(auto it = std::begin(sprites); it != std::end(sprites); ++it)
    {
        SpriteAtlasItemI *item = *it;
        CharacterBodyRenderer *renderer = new CharacterBodyRenderer(item);
        walkRenderer->AppendBodyRenderer(renderer);
    }

    m_walkR = walkRenderer;
}

void Character::SetHeadR(std::vector<SpriteAtlasItemI*> &sprites, int delay)
{
    CharacterWalkRenderer *walkRenderer = new CharacterWalkRenderer();
    walkRenderer->SetHeadAnimationDelay(delay);

    for(auto it = std::begin(sprites); it != std::end(sprites); ++it)
    {
        SpriteAtlasItemI *item = *it;
        CharacterHeadRenderer *renderer = new CharacterHeadRenderer(item);
        walkRenderer->AppendHeadRenderer(renderer);
    }

    m_headR = walkRenderer;
}

void Character::SetHeadOffsetForSpriteNamed(std::string spriteName, int offsetX, int offsetY)
{
    for (int i = 0; i < m_walkR->GetBodyAnimationCount(); i++)
    {
        CharacterBodyRenderer *renderer = m_walkR->GetBodyRendererAtIndex(i);
        if (renderer->GetSprite()->GetFilename().compare(spriteName) == 0) {
            renderer->SetHeadOffsetX(offsetX);
            renderer->SetHeadOffsetY(offsetY);
        }
    }
}

void Character::DrawBody(int x, int y)
{
    int m_maxWidth = m_walkR->GetBodyMaxWidth();
    int m_maxHeight = m_walkR->GetBodyMaxHeight();

    Uint32 ticks = SDL_GetTicks();
    Uint32 seconds = ticks / m_walkR->GetBodyAnimationDelay();
    Uint32 spriteNo = seconds % m_walkR->GetBodyAnimationCount();
    CharacterBodyRenderer *bodyRenderer = m_walkR->GetBodyRendererAtIndex(spriteNo);
    SpriteAtlasItemI *spriteItem = bodyRenderer->GetSprite();
    m_headOffsetX = bodyRenderer->GetHeadOffsetX();
    m_headOffsetY = bodyRenderer->GetHeadOffsetY();

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

void Character::DrawHead(int x, int y)
{
    CharacterWalkRenderer *renderer = m_headR;

    int m_maxWidth = renderer->GetHeadMaxWidth();
    int m_maxHeight = renderer->GetHeadMaxHeight();

    Uint32 ticks = SDL_GetTicks();
    Uint32 seconds = ticks / renderer->GetHeadAnimationDelay();
    Uint32 spriteNo = seconds % renderer->GetHeadAnimationCount();
    SpriteAtlasItemI *spriteItem = renderer->GetHeadRendererAtIndex(spriteNo)->GetSprite();

    GetMainEngine()->getProvider().DrawTexture(
       spriteItem->GetTexture(),
        x + ceil(m_scale *((m_maxWidth - spriteItem->getWidth())/2)) + (m_scale * m_headOffsetX),
        y - (spriteItem->getHeight() * m_scale) + (m_scale * m_headOffsetY),
        spriteItem->getX(),
        spriteItem->getY(),
        spriteItem->getWidth(),
        spriteItem->getHeight(),
        m_scale
    );
}

void Character::Draw(int x, int y)
{
    DrawBody(x, y);
    DrawHead(x, y);
}

#pragma mark - CharacterWalkRenderer

void CharacterWalkRenderer::AppendBodyRenderer(CharacterBodyRenderer* value)
{
    m_bodyRenderers.emplace_back(std::move(value));
    m_bodyMaxWidth = std::max(m_bodyMaxWidth, value->GetSprite()->getWidth());
    m_bodyMaxHeight = std::max(m_bodyMaxHeight, value->GetSprite()->getHeight());
}

void CharacterWalkRenderer::AppendHeadRenderer(CharacterHeadRenderer* value)
{
    m_headRenderers.emplace_back(std::move(value));
    m_headMaxWidth = std::max(m_headMaxWidth, value->GetSprite()->getWidth());
    m_headMaxHeight = std::max(m_headMaxHeight, value->GetSprite()->getHeight());
}
