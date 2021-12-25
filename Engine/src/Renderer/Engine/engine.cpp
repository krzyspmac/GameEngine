//
//  engine.cpp
//  RendererApp
//
//  Created by krzysp on 19/12/2021.
//

#include "engine.hpp"
#include "font.hpp"
#include "sprite_atlas_interface.h"
#include "sprite_atlas.hpp"
#include "sprite_draw_static.hpp"
#include "sprite_draw_animated.hpp"

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
//    DisposeAllSprites();
    DisposeAllFonts();
    DisposeAllTextures();
    SpriteAtlasDisposeAll();
    SpriteDrawDisposeAll();
}

void Engine::setup()
{
    m_fileAccess.LoadDirectory(m_fileAccess.GetResourcesDirectory());
#if SHOW_FPS
    m_fpsFont = LoadFont("EnterCommand.ttf");
#endif

    std::unique_ptr<FileMemoryBufferStreamI> streamBuffer(m_fileAccess.GetAccess("main.lua"));

    m_scriptingEngine.newState();
    m_scriptingEngine.loadFile(streamBuffer.get());
    m_scriptingEngine.registerFunctions();
    m_scriptingEngine.callInit();

    m_engineProvider.SetRenderBackgroundColor(96, 128, 255, 255);
    m_engineProvider.ClearRender();
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
    m_performanceStart = m_engineProvider.GetPerformanceCounter();

    m_engineProvider.SetRenderBackgroundColor(96, 128, 255, 255);
    m_engineProvider.ClearRender();

    m_scriptingEngine.callUpdate();

#if SHOW_FPS
    sprintf(m_fpsBuffer, "%.0f", m_previousFps);
    DrawText(m_fpsFont, m_fpsBuffer, 0, 0, 255, 255, 255, TEXT_ALIGN_LEFT);
#endif

    m_engineProvider.RenderPresent();

    m_performanceEnd = m_engineProvider.GetPerformanceCounter();
    m_performanceDelta = m_performanceEnd - m_performanceStart;
    m_seconds = m_performanceDelta / (float)SDL_GetPerformanceFrequency();
    m_previousFps = 1.0f / m_seconds;

    m_engineProvider.Delay(1);
}

TextureI *Engine::LoadTexture(std::string filename)
{
    TextureI *result = GetTexture(filename);
    if (!result)
    {
        std::unique_ptr<FileMemoryBufferStreamI> stream(m_fileAccess.GetAccess(filename));
        result = m_engineProvider.LoadTexture(filename, stream.get());
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
        std::unique_ptr<FileMemoryBufferStreamI> stream(m_fileAccess.GetAccess(name));
        result = m_engineProvider.LoadFont(name, stream.get());
        if (result)
        {
            m_fonts.emplace_back(std::move(result));
            return result;
        }
    }
    return result;
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

SpriteAtlasI *Engine::SpriteAtlasLoad(std::string jsonFilename, std::string textureFilename)
{
    SpriteAtlasI *atlas = SpriteAtlasGet(jsonFilename);
    if (!atlas)
    {
        atlas = new SpriteAtlas(jsonFilename, textureFilename);
        if (atlas)
        {
            m_atlas.emplace_back(std::move(atlas));
        }
    }

    return atlas;
}

SpriteAtlasI *Engine::SpriteAtlasGet(std::string jsonFilename)
{
    for(auto it = std::begin(m_atlas); it != std::end(m_atlas); ++it)
    {
        SpriteAtlasI *item = it->get();
        if (item->GetFilename().compare(jsonFilename) == 0)
        {
            return item;
        }
    }

    return NULL;
}

void Engine::SpriteAtlasUnload(SpriteAtlasI *atlas)
{
    for(auto it = std::begin(m_atlas); it != std::end(m_atlas); ++it)
    {
        SpriteAtlasI *item = it->get();
        if (item == atlas)
        {
            m_atlas.erase(it);
            break;
        }
    }
}

void Engine::SpriteAtlasDisposeAll()
{
    m_atlas.clear();
}

SpriteDrawI *Engine::SpriteDrawLoadStatic(SpriteAtlasItemI *sprite)
{
    engine::SpriteDrawStatic *sd = new engine::SpriteDrawStatic(sprite);

    if (sd)
    {
        m_spriteDraws.emplace_back(std::move(sd));
    }
    return sd;
}

SpriteDrawI *Engine::SpriteDrawLoadAnimated(SpriteAtlasItemI *sprite, int frameAnimationDurationMs)
{
    engine::SpriteDrawAnimated *sd = new engine::SpriteDrawAnimated(sprite, frameAnimationDurationMs);

    if (sd)
    {
        m_spriteDraws.emplace_back(std::move(sd));
    }
    return sd;

}

void Engine::SpriteDrawUnload(SpriteDrawI *spriteDraw)
{
    for(auto it = std::begin(m_spriteDraws); it != std::end(m_spriteDraws); ++it)
    {
        SpriteDrawI *item = it->get();
        if (item == spriteDraw)
        {
            m_spriteDraws.erase(it);
            break;
        }
    }
}

void Engine::SpriteDrawDisposeAll()
{
    m_spriteDraws.empty();
}
