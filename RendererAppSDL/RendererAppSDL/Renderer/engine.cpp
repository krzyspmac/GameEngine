//
//  engine.cpp
//  RendererApp
//
//  Created by krzysp on 19/12/2021.
//

#include "engine.hpp"
#include "font.hpp"
#include "sprite.hpp"

#ifdef __cplusplus
extern "C" {
    #include "../../../Lua/code/src/lua.h"
    #include "../../../Lua/code/src/lualib.h"
    #include "../../../Lua/code/src/lauxlib.h"
}
#endif //__cplusplus

using namespace engine;

/// Main accessor for easy access.
EngineI *sharedEngine = NULL;
engine::EngineI *GetMainEngine()
{
    return sharedEngine;
}

Engine::Engine(EngineProviderI &engineProvider, FileAccessI &fileAccess, ScriptingEngineI &scriptingEngine, EventProviderI &eventProvider)
: EngineI(engineProvider, fileAccess, scriptingEngine, eventProvider)
{
    sharedEngine = this;
}

Engine::~Engine()
{
    DisposeAllSprites();
    DisposeAllFonts();
    DisposeAllTextures();
}

void Engine::setup()
{
    m_scriptingEngine.newState();
    m_scriptingEngine.loadFile(m_fileAccess.getBundledFilepath("main.lua"));
    m_scriptingEngine.registerFunctions();
    m_scriptingEngine.callInit();

    m_engineProvider.SetRenderBackgroundColor(96, 128, 255, 255);
    m_engineProvider.ClearRender();;
}

int Engine::doInput()
{
    EVENT event;
    while (m_eventProvider.PollEvent(&event))
    {
        switch (event)
        {
            case EVENT_NONE:
            {
                break;
            }

            case EVENT_QUIT:
            {
                return 1;
            }
        };
    };

    m_engineProvider.GetMousePosition(&m_mousePosition.x, &m_mousePosition.y);

    return 0;
}

void Engine::update()
{
    m_performanceStart = m_engineProvider.GetPerformanceTicks();

    m_engineProvider.SetRenderBackgroundColor(96, 128, 255, 255);
    m_engineProvider.ClearRender();

    m_scriptingEngine.callUpdate();

    m_performanceEnd = m_engineProvider.GetPerformanceTicks();

    m_engineProvider.RenderPresent();
    m_engineProvider.Delay(1);

#if CALC_FPS
#endif
}

TextureI *Engine::LoadTexture(std::string name)
{
    TextureI *result = GetTexture(name);
    if (!result)
    {
        result = m_engineProvider.LoadTexture(name);
        if (result)
        {
            m_textures.emplace_back(std::move(result));
        }
    }

    return result;
}

TextureI *Engine::GetTexture(std::string name)
{
    for(auto it = std::begin(m_textures); it != std::end(m_textures); ++it)
    {
        TextureI *item = it->get();
        if (item->getTextureName().compare(name) == 0)
        {
            return item;
        }
    }

    return NULL;
}

void Engine::DrawTexture(TextureI *texture, int x, int y)
{
    m_engineProvider.DrawTexture(texture, x, y);
}

void Engine::UnloadTexture(TextureI *texture)
{
    for(auto it = std::begin(m_textures); it != std::end(m_textures); ++it)
    {
        TextureI *item = it->get();
        if (item == texture)
        {
            m_engineProvider.UnloadTexture(item);
            m_textures.erase(it);
            break;
        }
    }
}

void Engine::DisposeAllTextures()
{
    std::cout << "DisposeAlLTextures not implemented" << std::endl;
}

FontI *Engine::LoadFont(std::string name)
{
    FontI *result = GetFont(name);
    if (!result)
    {
        result = m_engineProvider.LoadFont(name);
        if (result)
        {
            m_fonts.emplace_back(std::move(result));
            return result;
        }
    }
    return NULL;
}

FontI *Engine::GetFont(std::string name)
{
    for(auto it = std::begin(m_fonts); it != std::end(m_fonts); ++it)
    {
        FontI *item = it->get();
        if (item->getFontName().compare(name) == 0)
        {
            return item;
        }
    }

    return NULL;
}

void Engine::DrawText(FontI *font, std::string text, int x, int y, int r, int g, int b, TEXT_ALIGNMENT align)
{
    m_engineProvider.DrawText(font, text, x, y, r, g, b, align);
}

void Engine::DisposeAllFonts()
{
    std::cout << "DisposeAllFonts not implemented" << std::endl;
}

SpriteI *Engine::LoadSprite(TextureI *texture, SpriteDescriptor spriteDescriptor)
{
    Sprite *sprite = new Sprite(texture, spriteDescriptor);
    m_sprites.emplace_back(std::move(sprite));
    return sprite;
}

void Engine::UnloadSprite(SpriteI *sprite)
{
    for(auto it = std::begin(m_sprites); it != std::end(m_sprites); ++it)
    {
        SpriteI *item = it->get();
        if (item == sprite)
        {
            m_sprites.erase(it);
            break;
        }
    }
}

void Engine::DisposeAllSprites()
{
    m_sprites.clear();
}

void Engine::SpriteDraw(SpriteI *sprite, int x, int y)
{
    sprite->Draw(x, y);
}
