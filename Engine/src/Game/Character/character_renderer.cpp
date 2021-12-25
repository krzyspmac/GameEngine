//
//  character.cpp
//  Engine
//
//  Created by krzysp on 25/12/2021.
//

#include "character_renderer.hpp"
#include "common_engine.h"

using namespace engine;

CharacterRenderer::CharacterRenderer(SpriteAtlasI *characterAtlas, int scale)
: CharacterRendererI(characterAtlas, scale), m_headOffsetX(0), m_headOffsetY(0)
{

}

CharacterWalkRenderer &CharacterRenderer::GetRenderer(CharacterWalkDirection direction)
{
    switch (direction)
    {
        case RIGHT:
            return m_walkR;
    }

    return m_walkR;
}

void CharacterRenderer::AppendBodyWalkAnimationFrame(CharacterWalkDirection direction, SpriteAtlasItemI *sprite, int headOffsetX, int headOffsetY)
{
    CharacterWalkRenderer &characterRenderer = GetRenderer(direction);

    CharacterBodyRenderer *bodyRenderer = new CharacterBodyRenderer(sprite);
    bodyRenderer->SetHeadOffsetX(headOffsetX);
    bodyRenderer->SetHeadOffsetY(headOffsetY);

    characterRenderer.AppendBodyRenderer(bodyRenderer);
}

void CharacterRenderer::AppendHeadAnimationFrame(CharacterWalkDirection direction, SpriteAtlasItemI *sprite)
{
    CharacterWalkRenderer &characterRenderer = GetRenderer(direction);
    CharacterHeadRenderer *headRenderer = new CharacterHeadRenderer(sprite);
    characterRenderer.AppendHeadRenderer(headRenderer);
}

void CharacterRenderer::DrawBody(int x, int y)
{
    CharacterWalkRenderer &renderer = GetRenderer(RIGHT);
    if (!renderer.GetBodyAnimationCount())
    {
        return;
    }

    int m_maxWidth = renderer.GetBodyMaxWidth();
    int m_maxHeight = renderer.GetBodyMaxHeight();

    Uint32 ticks = SDL_GetTicks();
    Uint32 seconds = ticks / renderer.GetBodyAnimationDelay();
    Uint32 spriteNo = seconds % renderer.GetBodyAnimationCount();
    CharacterBodyRenderer *bodyRenderer = renderer.GetBodyRendererAtIndex(spriteNo);
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

void CharacterRenderer::DrawHead(int x, int y)
{
    CharacterWalkRenderer &renderer = GetRenderer(RIGHT);
    if (!renderer.GetHeadAnimationCount())
    {
        return;
    }

    int m_maxWidth = renderer.GetHeadMaxWidth();

    Uint32 ticks = SDL_GetTicks();
    Uint32 seconds = ticks / renderer.GetHeadAnimationDelay();
    Uint32 spriteNo = seconds % renderer.GetHeadAnimationCount();
    SpriteAtlasItemI *spriteItem = renderer.GetHeadRendererAtIndex(spriteNo)->GetSprite();

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

void CharacterRenderer::Draw(int x, int y)
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
