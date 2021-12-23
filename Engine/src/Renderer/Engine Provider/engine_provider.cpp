//
//  engine_provider.cpp
//  RendererApp
//
//  Created by krzysp on 19/12/2021.
//

#include "engine_provider.hpp"
#include "texture.hpp"
#include "font.hpp"

namespace engine
{

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
        return NULL;
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
        return NULL;
    }
}

void EngineProvider::UnloadTexture(TextureI *texture)
{
    if (texture != NULL)
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
    if (texture != NULL)
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

void EngineProvider::DrawTexture(TextureI *texture, int x, int y, int srcX, int srcY, int srcW, int srcH)
{
    if (texture != NULL)
    {
        SDL_Rect dest;
        SDL_Rect src;

        SDL_Texture *sdlTexture = (SDL_Texture*)texture->getTextureHandle();
        SDL_QueryTexture(sdlTexture, NULL, NULL, &dest.w, &dest.h);

        dest.x = x;
        dest.y = y;
        dest.w = srcW;
        dest.h = srcH;

        src.x = srcX;
        src.y = srcY;
        src.w = srcW;
        src.h = srcH;

        SDL_RenderCopy(m_engineHandle->renderer, sdlTexture, &src, &dest);
    }
    else
    {
        std::cout << "No texture to draw" << std::endl;
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

};
