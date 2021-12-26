//
//  character.cpp
//  Engine
//
//  Created by krzysp on 25/12/2021.
//

#include "character_renderer.hpp"
#include "common_engine.h"

#include "engine_provider.hpp" // temp
#include <SDL.h>

using namespace engine;

CharacterRenderer::CharacterRenderer(SpriteAtlasI *characterAtlas, int scale)
: CharacterRendererI(characterAtlas, scale), m_headOffsetX(0), m_headOffsetY(0)
{
}

CharacterRenderer::~CharacterRenderer()
{
    GetMainEngine()->UnloadTexture(m_bufferTexture);
}

CharacterWalkRenderer &CharacterRenderer::GetRenderer(CharacterWalkDirection direction)
{
    switch (direction)
    {
        case RIGHT:
            return m_walkR;
        case STAND_RIGHT:
            return m_standR;
        case LEFT:
            return m_walkL;
        case STAND_LEFT:
            return m_standL;
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

void CharacterRenderer::PrepareCharacter()
{
    CharacterWalkDirection directions[] = { STAND_RIGHT, RIGHT, STAND_LEFT, LEFT };
    int directionsCount = sizeof(directions) / sizeof(CharacterWalkDirection);

    int maxBodyWidth = 0;
    int maxBodyHeight = 0;
    int maxHeadWidth = 0;
    int maxHeadHeight = 0;

    for (int i = 0; i < directionsCount; i++)
    {
        CharacterWalkDirection state = (CharacterWalkDirection)directions[i];
        CharacterWalkRenderer &characterRenderer = GetRenderer(state);
        maxBodyWidth = std::max(maxBodyWidth, characterRenderer.GetBodyMaxWidth());
        maxBodyHeight = std::max(maxBodyHeight, characterRenderer.GetBodyMaxHeight());
        maxHeadWidth = std::max(maxHeadWidth, characterRenderer.GetHeadMaxWidth());
        maxHeadHeight = std::max(maxHeadHeight, characterRenderer.GetHeadMaxHeight());
    }

    m_bodyWidth = std::max(maxBodyWidth, maxHeadWidth);
    m_bodyHeight = maxBodyHeight + maxHeadHeight;
    m_headHeadHeight = maxHeadHeight;
    m_bufferTexture = GetMainEngine()->CreateTargetTexture(m_bodyWidth, m_bodyHeight);
}

void CharacterRenderer::DrawBody(CharacterWalkRenderer &renderer, bool isAnimating)
{
    if (!renderer.GetBodyAnimationCount())
    {
        return;
    }

    int m_maxWidth = renderer.GetBodyMaxWidth();

    Uint32 ticks = SDL_GetTicks();
    Uint32 seconds = ticks / renderer.GetBodyAnimationDelay();
    Uint32 frameCount = (Uint32)renderer.GetBodyAnimationCount();
    Uint32 frameNo = renderer.GetIsReversed()
        ? (frameCount-1) - (seconds % frameCount)
        : (seconds % frameCount)
    ;
    Uint32 spriteNo = isAnimating ? (frameNo) : 0;
    CharacterBodyRenderer *bodyRenderer = renderer.GetBodyRendererAtIndex(spriteNo);
    SpriteAtlasItemI *spriteItem = bodyRenderer->GetSprite();
    m_headOffsetX = bodyRenderer->GetHeadOffsetX();
    m_headOffsetY = bodyRenderer->GetHeadOffsetY();

    GetMainEngine()->getProvider().DrawTexture(
       spriteItem->GetTexture(),
        /*x + */ceil(1 *((m_maxWidth - spriteItem->getWidth())/2)) + + (1 * bodyRenderer->GetBodyOffsetX()),
        /*y + */m_headHeadHeight,
        spriteItem->getX(),
        spriteItem->getY(),
        spriteItem->getWidth(),
        spriteItem->getHeight(),
        1
    );
}

void CharacterRenderer::DrawHead(CharacterWalkRenderer &renderer, bool isAnimating)
{
    if (!renderer.GetHeadAnimationCount())
    {
        return;
    }

    int m_maxWidth = renderer.GetHeadMaxWidth();

    Uint32 ticks = SDL_GetTicks();
    Uint32 seconds = ticks / renderer.GetHeadAnimationDelay();
    Uint32 frameCount = (Uint32)renderer.GetHeadAnimationCount();
    Uint32 frameNo = renderer.GetIsReversed()
        ? (frameCount-1) - (seconds % frameCount)
        : (seconds % frameCount)
    ;
    Uint32 spriteNo = isAnimating ? (frameNo) : 0;
    SpriteAtlasItemI *spriteItem = renderer.GetHeadRendererAtIndex(spriteNo)->GetSprite();

    GetMainEngine()->getProvider().DrawTexture(
       spriteItem->GetTexture(),
        /*0 + */ceil((m_maxWidth - spriteItem->getWidth())/2) + m_headOffsetX,
        /*0 + */m_headOffsetY,
        spriteItem->getX(),
        spriteItem->getY(),
        spriteItem->getWidth(),
        spriteItem->getHeight(),
        1
    );
}

void CharacterRenderer::DrawBoundingBox(EngineProviderI &provider)
{
    Engine_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = m_bodyWidth;
    rect.h = m_bodyHeight;
    provider.RenderDrawRect(&rect);
}

void CharacterRenderer::DrawOriginCrosshair(EngineProviderI &provider)
{
    int length = 20;
    int arrowLength = 5;
    int midPosX = m_bodyWidth/2;

    provider.RenderDrawLine(midPosX, m_bodyHeight - length, midPosX, m_bodyHeight + length);
    provider.RenderDrawLine(midPosX, m_bodyHeight - length, midPosX - arrowLength, m_bodyHeight - arrowLength);
    provider.RenderDrawLine(midPosX, m_bodyHeight - length, midPosX + arrowLength, m_bodyHeight - arrowLength);
}

void CharacterRenderer::Draw(CharacterWalkDirection state, bool isAnimating, int x, int y)
{
    // Get the engine provider. All drawing functions go through there.
    EngineProviderI &provider = GetMainEngine()->getProvider();

    // Get the current walk renderer.
    CharacterWalkRenderer &renderer = GetRenderer(state);

    // Set the buffer texture as the current rendering target
    GetMainEngine()->SetRenderTarget(m_bufferTexture);

    // Clear the buffer textures with a clear color
    provider.RenderSetColor(255, 255, 255, 0);
    GetMainEngine()->getProvider().RenderClear();

    // Render the body, then the head
    DrawBody(renderer, isAnimating);
    DrawHead(renderer, isAnimating);

    // Render display artifacts
    provider.RenderSetColor(255, 255, 255, 120);
    DrawBoundingBox(provider);
    DrawOriginCrosshair(provider);

    // Clear the render target so that the final pass can be pushed
    // to the graphics card.
    GetMainEngine()->ClearRenderTarget();

    // Draw the buffer texture.
    provider.DrawTexture(m_bufferTexture, ANCHOR_BOTTOM_CENTER, 200, 300, m_scale, renderer.GetIsReversed());
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
