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
#include "character_renderer.hpp"
#include "character.hpp"
#include "engine_provider.hpp"

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

Engine::Engine(EngineProviderI &engineProvider, FileAccessI &fileAccess, ScriptingEngineI &scriptingEngine, EventProviderI &eventProvider, Size viewportSize)
: EngineI(engineProvider, fileAccess, scriptingEngine, eventProvider, viewportSize)
{
    sharedEngine = this;
}

Engine::~Engine()
{
    DisposeAllFonts();
    DisposeAllTextures();
    SpriteAtlasDisposeAll();
    SpriteDrawDisposeAll();

    delete m_bufferTexture;
    delete m_character;
}

void Engine::setup()
{
    m_fileAccess.LoadDirectory(m_fileAccess.GetResourcesDirectory());
#if SHOW_FPS
    m_fpsFont = LoadFont("EnterCommand.ttf");
#endif

    m_bufferTexture = m_engineProvider.CreateTargetTexture(m_viewportSize.width, m_viewportSize.height);

    std::unique_ptr<FileMemoryBufferStreamI> streamBuffer(m_fileAccess.GetAccess("main.lua"));

    m_scriptingEngine.newState();
    m_scriptingEngine.loadFile(streamBuffer.get());
    m_scriptingEngine.registerFunctions();
    m_scriptingEngine.callInit();

    m_engineProvider.SetRenderBackgroundColor(96, 128, 255, 255);
    m_engineProvider.ClearRender();

    m_character = new Character("brett_character.json");
    m_character->SetScale(2.5);
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

            case EVENT_KEYDOWN:
            {
                m_character->Change();
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
    // Calculate performance
    m_performanceStart = m_engineProvider.GetPerformanceCounter();

    // Clear the window background
    m_engineProvider.SetRenderBackgroundColor(0, 0, 0, 255);
    m_engineProvider.ClearRender();

    // Push the buffer texture. All scene will be rendered to a buffer texture
    m_engineProvider.RendererTargetPush(m_bufferTexture);

    // Clear the game background
    m_engineProvider.SetRenderBackgroundColor(255, 0, 0, 120);
    m_engineProvider.ClearRender();

    m_scriptingEngine.callUpdate();
    m_character->Draw(100, 480);

#if SHOW_FPS
    sprintf(m_fpsBuffer, "%.0f", m_previousFps);
    m_engineProvider.DrawText(m_fpsFont, m_fpsBuffer, 0, 0, 255, 255, 255, TEXT_ALIGN_LEFT);
#endif

    // Pop the buffer texture. Blit the render to the screen.
    m_engineProvider.RendererTargetPop();

    // Apply scaling transformation due to possible window resize
    int windowW, windowH;
    m_engineProvider.GetWindowSize(&windowW, &windowH);

    float scaleX, scaleY;
    scaleX = (float)windowW / (float)m_viewportSize.width;
    scaleY = (float)windowH / (float)m_viewportSize.height;

    float scale = std::min(scaleX, scaleY);
    SDL_RenderSetScale(((EngineProvider&)m_engineProvider).GetRendererHandle()->renderer, scale, scale);

    int targetWidth = m_viewportSize.width * scale;
    int targetHeight = m_viewportSize.height * scale;

    int offsetX = ((windowW - targetWidth) / 2)/scale;
    int offsetY = ((windowH - targetHeight) / 2)/scale;

    // Draw the back buffer texture
    m_engineProvider.DrawTexture(m_bufferTexture, offsetX, offsetY);

    // Render the current stack
    m_engineProvider.RenderPresent();

    // Calculate performance
    m_performanceEnd = m_engineProvider.GetPerformanceCounter();
    m_performanceDelta = m_performanceEnd - m_performanceStart;
    m_seconds = m_performanceDelta / (float)SDL_GetPerformanceFrequency();
    m_previousFps = 1.0f / m_seconds;
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

TextureTargetI *Engine::CreateTargetTexture(int width, int height)
{
    return m_engineProvider.CreateTargetTexture(width, height);
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

SpriteDrawI *Engine::SpriteDrawLoadStatic(SpriteAtlasItemI *sprite, int scale)
{
    engine::SpriteDrawStatic *sd = new engine::SpriteDrawStatic(sprite, scale);

    if (sd)
    {
        m_spriteDraws.emplace_back(std::move(sd));
    }
    return sd;
}

SpriteDrawI *Engine::SpriteDrawLoadAnimated(std::vector<SpriteAtlasItemI*> sprites, int frameAnimationDurationMs, int scale)
{
    engine::SpriteDrawAnimated *sd = new engine::SpriteDrawAnimated(sprites, frameAnimationDurationMs, scale);

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
