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
        case STAND_RIGHT:
            return m_standR;
    }

    return m_walkR;
}

void CharacterRenderer::AppendBodyWalkAnimationFrame(CharacterWalkDirection direction, SpriteAtlasItemI *sprite, int offsetX, int offsetY, int headOffsetX, int headOffsetY)
{
    CharacterWalkRenderer &characterRenderer = GetRenderer(direction);

    CharacterBodyRenderer *bodyRenderer = new CharacterBodyRenderer(sprite, offsetX, offsetY);
    bodyRenderer->SetHeadOffsetX(headOffsetX);
    bodyRenderer->SetHeadOffsetY(headOffsetY);

    characterRenderer.AppendBodyRenderer(bodyRenderer);
}

void CharacterRenderer::AppendHeadAnimationFrame(CharacterWalkDirection direction, SpriteAtlasItemI *sprite, int offsetX, int offsetY)
{
    CharacterWalkRenderer &characterRenderer = GetRenderer(direction);
    CharacterHeadRenderer *headRenderer = new CharacterHeadRenderer(sprite, offsetX, offsetY);
    characterRenderer.AppendHeadRenderer(headRenderer);
}

void CharacterRenderer::DrawBody(CharacterWalkDirection direction, bool isAnimating, int x, int y)
{
    CharacterWalkRenderer &renderer = GetRenderer(direction);
    if (!renderer.GetBodyAnimationCount())
    {
        return;
    }

    int m_maxWidth = renderer.GetBodyMaxWidth();
    int m_maxHeight = renderer.GetBodyMaxHeight();

    Uint32 ticks = SDL_GetTicks();
    Uint32 seconds = ticks / renderer.GetBodyAnimationDelay();
    Uint32 spriteNo = isAnimating ? (seconds % renderer.GetBodyAnimationCount()) : 0;
    CharacterBodyRenderer *bodyRenderer = renderer.GetBodyRendererAtIndex(spriteNo);
    SpriteAtlasItemI *spriteItem = bodyRenderer->GetSprite();
    m_headOffsetX = bodyRenderer->GetHeadOffsetX();
    m_headOffsetY = bodyRenderer->GetHeadOffsetY();

    GetMainEngine()->getProvider().DrawTexture(
       spriteItem->GetTexture(),
        x + ceil(m_scale *((m_maxWidth - spriteItem->getWidth())/2)) + (m_scale * bodyRenderer->GetBodyOffsetX()),
        y + ceil(m_scale *((m_maxHeight - spriteItem->getHeight())/2)) + (m_scale * bodyRenderer->GetBodyOffsetY()),
        spriteItem->getX(),
        spriteItem->getY(),
        spriteItem->getWidth(),
        spriteItem->getHeight(),
        m_scale
    );
}

void CharacterRenderer::DrawHead(CharacterWalkDirection direction, bool isAnimating, int x, int y)
{
    CharacterWalkRenderer &renderer = GetRenderer(direction);
    if (!renderer.GetHeadAnimationCount())
    {
        return;
    }

    int m_maxWidth = renderer.GetHeadMaxWidth();

    Uint32 ticks = SDL_GetTicks();
    Uint32 seconds = ticks / renderer.GetHeadAnimationDelay();
    Uint32 spriteNo = isAnimating ? (seconds % renderer.GetHeadAnimationCount()) : 0;
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
