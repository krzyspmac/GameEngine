//
//  character.cpp
//  Engine
//
//  Created by krzysp on 25/12/2021.
//

#include "character_renderer.hpp"
#include "engine.hpp"

using namespace engine;

CharacterRenderer::CharacterRenderer(SpriteAtlasI *characterAtlas, int scale)
: CharacterRendererI(characterAtlas, scale), m_headOffsetX(0), m_headOffsetY(0)
{
}

CharacterRenderer::~CharacterRenderer()
{
    // TODO: memory management
//    GetMainEngine()->getTextureManager().UnloadTexture(m_bufferTexture);
}

CharacterWalkRenderer &CharacterRenderer::GetRenderer(CharacterWalkState direction)
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
        case FORWARD:
            return m_walkF;
        case STAND_FORWARD:
            return m_standF;
        case BACKWARD:
            return m_walkB;
        case STAND_BACKWARD:
            return m_standB;
    }

    return m_walkR;
}

void CharacterRenderer::SetZPosition(float value)
{
    CharacterWalkState directions[] = { STAND_RIGHT, RIGHT, STAND_LEFT, LEFT };
    int directionsCount = sizeof(directions) / sizeof(CharacterWalkState);

    for (int i = 0; i < directionsCount; i++)
    {
        CharacterWalkState state = (CharacterWalkState)directions[i];
        CharacterWalkRenderer &characterRenderer = GetRenderer(state);
        for (int n = 0; n < characterRenderer.GetBodyAnimationCount(); n++)
        {
            characterRenderer.GetBodyRendererAtIndex(n)->GetDrawable()->SetZPosition(value);
        }
        for (int n = 0; n < characterRenderer.GetHeadAnimationCount(); n++)
        {
            characterRenderer.GetHeadRendererAtIndex(n)->GetDrawable()->SetZPosition(value);
        }
    }
}

void CharacterRenderer::AppendBodyWalkAnimationFrame(CharacterWalkState direction, SpriteAtlasItemI *sprite, int offsetX, int offsetY, int headOffsetX, int headOffsetY)
{
    if (sprite)
    {
        CharacterWalkRenderer &characterRenderer = GetRenderer(direction);

        CharacterBodyRenderer *bodyRenderer = new CharacterBodyRenderer(sprite, offsetX, offsetY);
        bodyRenderer->SetHeadOffsetX(headOffsetX);
        bodyRenderer->SetHeadOffsetY(headOffsetY);

        characterRenderer.AppendBodyRenderer(bodyRenderer);
    }
    else
    {
        std::cout << "No Sprite for walk" << std::endl;
    }
}

void CharacterRenderer::AppendHeadAnimationFrame(CharacterWalkState direction, SpriteAtlasItemI *sprite, int offsetX, int offsetY)
{
    if (sprite)
    {
        CharacterWalkRenderer &characterRenderer = GetRenderer(direction);
        CharacterHeadRenderer *headRenderer = new CharacterHeadRenderer(sprite, offsetX, offsetY);
        characterRenderer.AppendHeadRenderer(headRenderer);
    }
    else
    {
        std::cout << "No Sprite for walk" << std::endl;
    }
}

void CharacterRenderer::PrepareCharacter()
{
    CharacterWalkState directions[] = { STAND_RIGHT, RIGHT, STAND_LEFT, LEFT };
    int directionsCount = sizeof(directions) / sizeof(CharacterWalkState);

    int maxBodyWidth = 0;
    int maxBodyHeight = 0;
    int maxHeadWidth = 0;
    int maxHeadHeight = 0;

    for (int i = 0; i < directionsCount; i++)
    {
        CharacterWalkState state = (CharacterWalkState)directions[i];
        CharacterWalkRenderer &characterRenderer = GetRenderer(state);
        maxBodyWidth = std::max(maxBodyWidth, characterRenderer.GetBodyMaxWidth());
        maxBodyHeight = std::max(maxBodyHeight, characterRenderer.GetBodyMaxHeight());
        maxHeadWidth = std::max(maxHeadWidth, characterRenderer.GetHeadMaxWidth());
        maxHeadHeight = std::max(maxHeadHeight, characterRenderer.GetHeadMaxHeight());
    }

    m_bodyWidth = std::max(maxBodyWidth, maxHeadWidth);
    m_bodyHeight = maxBodyHeight;
    m_headHeadHeight = maxHeadHeight;

    auto& anyRenderer = m_standB;
    auto body = anyRenderer.GetBodyRendererAtIndex(0);
    auto sprite = new SpriteRepresentationStatic(body->GetSprite());
    m_bodySprite = std::unique_ptr<SpriteRepresentationStatic>(std::move(sprite));
}

void CharacterRenderer::DrawBody(CharacterWalkRenderer &renderer, bool isAnimating, Vector2 position)
{
    if (!renderer.GetBodyAnimationCount())
    {
        return;
    }

    auto& provider = GetMainEngine()->getProvider();
    int m_maxWidth = renderer.GetBodyMaxWidth();

    Uint64 ticks = provider.GetTicks();
    Uint64 seconds = ticks / renderer.GetBodyAnimationDelay();
    Uint32 frameCount = (Uint32)renderer.GetBodyAnimationCount();
    Uint32 frameNo = //renderer.GetIsReversed()
        //? (frameCount-1) - (seconds % frameCount)
        /*: */(seconds % frameCount)
    ;
    Uint32 spriteNo = isAnimating ? (frameNo) : 0;

    // Get the current body renderer
    CharacterBodyRenderer *bodyRenderer = renderer.GetBodyRendererAtIndex(spriteNo);

    // The current sprite item decides where the body should go
    SpriteAtlasItemI *spriteItem = bodyRenderer->GetSprite();
    m_headOffsetX = bodyRenderer->GetHeadOffsetX();
    m_headOffsetY = bodyRenderer->GetHeadOffsetY();

    float x = ceil(
        ((m_maxWidth - spriteItem->GetWidth())/2) + bodyRenderer->GetBodyOffsetX()
    );

    float spriteWidth = spriteItem->GetWidth();
    float spriteWidth2 = spriteWidth / 2;
    float widthDifference = (m_maxWidth - spriteWidth)/2;

    auto drawable = bodyRenderer->GetDrawable();
    drawable->SetScale(m_scale);
    provider.DrawableRender(
        drawable
      , position.x - (widthDifference * m_scale) - ceil(bodyRenderer->GetBodyOffsetX() * m_scale)  // - (m_bodyWidth * m_scale / 2)
      , position.y
    );
}

void CharacterRenderer::DrawHead(CharacterWalkRenderer &renderer, bool isAnimating, Vector2 position)
{
    if (!renderer.GetHeadAnimationCount()) { return; }

    auto& provider = GetMainEngine()->getProvider();
    int m_maxWidth = renderer.GetHeadMaxWidth();

    Uint64 ticks = GetMainEngine()->getProvider().GetTicks();
    Uint64 seconds = ticks / renderer.GetHeadAnimationDelay();
    Uint32 frameCount = (Uint32)renderer.GetHeadAnimationCount();
    Uint32 frameNo = (seconds % frameCount);
    Uint32 spriteNo = isAnimating ? (frameNo) : 0;

    // Get the current body renderer
    auto headPartRenderer = renderer.GetHeadRendererAtIndex(spriteNo);
    SpriteAtlasItemI *spriteItem = headPartRenderer->GetSprite();

    auto drawable = headPartRenderer->GetDrawable();
    drawable->SetScale(m_scale);
    float x = ceil((m_maxWidth - (float)spriteItem->GetWidth())/2) + m_headOffsetX + spriteItem->GetWidth();
    float y = m_headOffsetY * m_scale;

    provider.DrawableRender(
        drawable
      , position.x - ceil(x * m_scale)
      , position.y - (m_headHeadHeight * m_scale * 2)  // + y + (m_headHeadHeight * m_scale)
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

void CharacterRenderer::Draw(CharacterWalkState state, bool isWalking, bool isTalking, Vector2& position)
{
    // Get the engine provider. All drawing functions go through there.
    EngineProviderI &provider = GetMainEngine()->getProvider();

    // Get the current walk renderer.
    CharacterWalkRenderer &renderer = GetRenderer(state);

    Vector2 bodyPosition =
    {
        position.x - (m_bodyWidth * m_scale / 2),
        position.y - (m_bodyHeight * m_scale * 2)
    };

    // Render the body, then the head
    DrawBody(renderer, isWalking, bodyPosition);
    DrawHead(renderer, isTalking, bodyPosition);

    // Render display artifacts
    provider.RenderSetColor(255, 255, 255, 120);
    DrawBoundingBox(provider);
    DrawOriginCrosshair(provider);
}

#pragma mark - CharacterWalkRenderer

void CharacterWalkRenderer::AppendBodyRenderer(CharacterBodyRenderer* value)
{
    m_bodyRenderers.emplace_back(std::move(value));
    m_bodyMaxWidth = std::max(m_bodyMaxWidth, value->GetSprite()->GetWidth());
    m_bodyMaxHeight = std::max(m_bodyMaxHeight, value->GetSprite()->GetHeight());
}

void CharacterWalkRenderer::AppendHeadRenderer(CharacterHeadRenderer* value)
{
    m_headRenderers.emplace_back(std::move(value));
    m_headMaxWidth = std::max(m_headMaxWidth, value->GetSprite()->GetWidth());
    m_headMaxHeight = std::max(m_headMaxHeight, value->GetSprite()->GetHeight());
}
