//
//  engine_provider.cpp
//  RendererApp
//
//  Created by krzysp on 19/12/2021.
//

#include "engine_provider.hpp"
#include "texture.hpp"
#include "font.hpp"
#include "texture_target.hpp"
#include "SDL.h"

/// Defaults

static SDL_Point flipPoint;
static SDL_FPoint flipPointF;

using namespace engine;

EngineProvider::EngineProvider(engine::SDL_APP *engineHandle)
: EngineProviderI(), m_engineHandle(engineHandle)
{
    flipPoint.x = 0.5;
    flipPoint.y = 0.5;
    flipPointF.x = 0.5;
    flipPointF.y = 0.5;
}

Uint64 EngineProvider::GetTicks()
{
    return SDL_GetTicks64();
}

Uint64 EngineProvider::GetPerformanceTicks()
{
    return SDL_GetPerformanceCounter();
}

Uint64 EngineProvider::GetPerformanceCounter()
{
    return SDL_GetPerformanceCounter();
}

void EngineProvider::GetMousePosition(int *x, int *y)
{
    SDL_GetMouseState(x, y);
}

void EngineProvider::Delay(Uint32 ms)
{
    SDL_Delay(ms);
}

void EngineProvider::GetWindowSize(int *w, int *h)
{
    SDL_GetWindowSize(m_engineHandle->window, w, h);
}

void EngineProvider::SetRenderBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(m_engineHandle->renderer, r, g, b, a);
}

void EngineProvider::ClearRender()
{
    SDL_RenderClear(m_engineHandle->renderer);
}

void EngineProvider::RenderPresent()
{
    SDL_RenderPresent(m_engineHandle->renderer);
}

TextureI *EngineProvider::LoadTexture(std::string filename, FileMemoryBufferStreamI *stream)
{
    SDL_Texture *textureHandle;

    SDL_RWops *ops = SDL_RWFromConstMem(stream->GetMemory(), (int)stream->GetSize());
    if (!ops)
    {
        return nullptr;
    }

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename.c_str());
    textureHandle = IMG_LoadTexture_RW(m_engineHandle->renderer, ops, 1);

    if (textureHandle != NULL)
    {
        Texture *texture = new Texture(textureHandle, filename);
        return (TextureI*)texture;
    }
    else
    {
        return nullptr;
    }
}

TextureTargetI *EngineProvider::CreateTargetTexture(int width, int height)
{
    SDL_Texture* textureHandle = SDL_CreateTexture(m_engineHandle->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_SetTextureBlendMode(textureHandle, SDL_BLENDMODE_BLEND);
    TextureTarget *texture = new TextureTarget(textureHandle);
    return (TextureTargetI*)texture;
}

void EngineProvider::UnloadTexture(TextureI *texture)
{
    if (texture != nullptr)
    {
        SDL_Texture *sdlTexture = (SDL_Texture*)texture->getTextureHandle();
        if (sdlTexture != NULL)
        {
            SDL_DestroyTexture(sdlTexture);
        }
        else
        {
            std::cout << "No SDL_Texture to destroy" << std::endl;
        }
    }
    else
    {
        std::cout << "No texture to destroy" << std::endl;
    }
}

void EngineProvider::DrawTexture(TextureI *texture, int x, int y)
{
    if (texture != nullptr)
    {
        SDL_Texture *sdlTexture = (SDL_Texture*)texture->getTextureHandle();
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;

        SDL_QueryTexture(sdlTexture, NULL, NULL, &dest.w, &dest.h);
        SDL_RenderCopy(m_engineHandle->renderer, sdlTexture, NULL, &dest);
    }
    else
    {
        std::cout << "No texture to draw" << std::endl;
    }
}

void EngineProvider::DrawTexture(TextureI *texture, int x, int y, int srcX, int srcY, int srcW, int srcH, float scale)
{
    if (texture != nullptr)
    {
        SDL_Rect dest;
        SDL_Rect src;

        SDL_Texture *sdlTexture = (SDL_Texture*)texture->getTextureHandle();
        SDL_QueryTexture(sdlTexture, NULL, NULL, &dest.w, &dest.h);

        dest.x = x / scale;
        dest.y = y / scale;
        dest.w = srcW;
        dest.h = srcH;

        src.x = srcX;
        src.y = srcY;
        src.w = srcW;
        src.h = srcH;

        float originalScaleX, originalScaleY;
        SDL_RenderGetScale(m_engineHandle->renderer, &originalScaleX, &originalScaleY);
        SDL_RenderSetScale(m_engineHandle->renderer, scale, scale);
        SDL_RenderCopy(m_engineHandle->renderer, sdlTexture, &src, &dest);
        SDL_RenderSetScale(m_engineHandle->renderer, originalScaleX, originalScaleY);
    }
    else
    {
        std::cout << "No texture to draw" << std::endl;
    }
}

void EngineProvider::DrawTexture(TextureI *texture, Anchor_Point anchorPoint, int x, int y, float scale, bool flipHorizontal)
{
    if (texture != NULL)
    {
        SDL_Rect dest;

        SDL_Texture *sdlTexture = (SDL_Texture*)texture->getTextureHandle();
        SDL_QueryTexture(sdlTexture, NULL, NULL, &dest.w, &dest.h);

        dest.x = x / scale;
        dest.y = y / scale;

        switch (anchorPoint)
        {
            case ANCHOR_TOP_LEFT:
                break;
            case ANCHOR_BOTTOM_CENTER:
                dest.x -= dest.w / 2;
                dest.y -= dest.h;
                break;
        }

        float originalScaleX, originalScaleY;
        SDL_RenderGetScale(m_engineHandle->renderer, &originalScaleX, &originalScaleY);
        SDL_RenderSetScale(m_engineHandle->renderer, scale, scale);
        SDL_RenderCopyEx(m_engineHandle->renderer, sdlTexture, NULL, &dest, 0, &flipPoint, flipHorizontal ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
        SDL_RenderSetScale(m_engineHandle->renderer, originalScaleX, originalScaleY);
    }
}

void EngineProvider::DrawTexture(TextureI *texture, Anchor_Point anchorPoint, Vector2& position, float scale, bool flipHorizontal)
{
    if (texture != NULL)
    {
        SDL_FRect dest;
        int textureW, textureH;

        SDL_Texture *sdlTexture = (SDL_Texture*)texture->getTextureHandle();
        SDL_QueryTexture(sdlTexture, NULL, NULL, &textureW, &textureH);

        dest.x = position.x / scale;
        dest.y = position.y / scale;
        dest.w = textureW;
        dest.h = textureH;

        switch (anchorPoint)
        {
            case ANCHOR_TOP_LEFT:
                break;
            case ANCHOR_BOTTOM_CENTER:
                dest.x -= dest.w / 2;
                dest.y -= dest.h;
                break;
        }

        float originalScaleX, originalScaleY;
        SDL_RenderGetScale(m_engineHandle->renderer, &originalScaleX, &originalScaleY);
        SDL_RenderSetScale(m_engineHandle->renderer, scale, scale);
        SDL_RenderCopyExF(m_engineHandle->renderer, sdlTexture, NULL, &dest, 0, &flipPointF, flipHorizontal ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
        SDL_RenderSetScale(m_engineHandle->renderer, originalScaleX, originalScaleY);
    }
}

FontI *EngineProvider::LoadFont(std::string name, FileMemoryBufferStreamI *stream)
{
    return (FontI*)new Font(m_engineHandle, name, stream);
}

void EngineProvider::DrawText(FontI *font, std::string text, int x, int y, int r, int g, int b, TEXT_ALIGNMENT align)
{
    Font *fontImpl = (Font*)font;
    fontImpl->DrawText(m_engineHandle, text, x, y, r, g, b, align);
}

void EngineProvider::TextureAlphaSetMod(TextureI *texture, uint8_t alpha)
{
    if (SDL_SetTextureAlphaMod((SDL_Texture*)texture->getTextureHandle(), alpha) == -1)
    {
        std::cout << "Error. SDL_SetTextureAlphaMod not supported by the renderer" << std::endl;
    }
}

void EngineProvider::RendererTargetPush(TextureTargetI *targetTexture)
{
    m_rendererStack.push_back(targetTexture);
    SDL_SetRenderTarget(m_engineHandle->renderer, (SDL_Texture*)targetTexture->getTextureHandle());
}

void EngineProvider::RendererTargetPop()
{
    m_rendererStack.pop_back();
    if (m_rendererStack.size() > 0)
    {
        TextureI *targetTexture = m_rendererStack.at(m_rendererStack.size()-1);
        SDL_SetRenderTarget(m_engineHandle->renderer, (SDL_Texture*)targetTexture->getTextureHandle());
    }
    else
    {
        SDL_SetRenderTarget(m_engineHandle->renderer, NULL);
    }
}

void EngineProvider::RenderTargetSet(TextureI *targetTexture)
{
    SDL_SetRenderTarget(m_engineHandle->renderer, (SDL_Texture*)targetTexture->getTextureHandle());
}

void EngineProvider::RenderTargetClear()
{
    SDL_SetRenderTarget(m_engineHandle->renderer, NULL);
}

void EngineProvider::RenderClear()
{
    SDL_RenderClear(m_engineHandle->renderer);
}

void EngineProvider::RenderSetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(m_engineHandle->renderer, r, g, b, a);
}

void EngineProvider::RenderSetScale(float scaleX, float scaleY)
{
    SDL_RenderSetScale(m_engineHandle->renderer, scaleX, scaleY);
}

void EngineProvider::RenderDrawRect(Engine_Rect *rect)
{
    SDL_RenderDrawRect(m_engineHandle->renderer, (SDL_Rect*)rect);
}

void EngineProvider::RenderFillRect(Engine_Rect *rect)
{
    SDL_RenderFillRect(m_engineHandle->renderer, (SDL_Rect*)rect);
}

void EngineProvider::RenderDrawLine(int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(m_engineHandle->renderer, x1, y1, x2, y2);
}

void EngineProvider::RenderDrawPoint(int x1, int y1)
{
    SDL_RenderDrawPoint(m_engineHandle->renderer, x1, y1);
}
