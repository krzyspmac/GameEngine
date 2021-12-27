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
#include "character_mover.hpp"

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
: EngineI(engineProvider, fileAccess, scriptingEngine, eventProvider, viewportSize), m_viewportScale(1)
{
    sharedEngine = this;
    SetCapRate(60);
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
    m_character->SetScale(2);

    m_characterMover = new CharacterMover(m_character);
    m_characterMover->PlaceCharacter(OriginMake(100, 450));

    std::vector<Vector2> polygon1List;
    polygon1List.push_back( Vector2Make(0, 393) );
    polygon1List.push_back( Vector2Make(557, 368) );
    polygon1List.push_back( Vector2Make(742, 295) );
    polygon1List.push_back( Vector2Make(590, 267) );
    polygon1List.push_back( Vector2Make(292, 254) );
    polygon1List.push_back( Vector2Make(291, 300) );
    polygon1List.push_back( Vector2Make(386, 280) );
    polygon1List.push_back( Vector2Make(386, 319) );
    polygon1List.push_back( Vector2Make(206, 353) );

    polygon1List.push_back( Vector2Make(0, 254) );
    polygon1List.push_back( Vector2Make(0, 393) );
    Polygon polygon1(polygon1List);

    std::vector<Vector2> polygon2List;
    polygon2List.push_back( Vector2Make(0, 487) );
    polygon2List.push_back( Vector2Make(212, 466) );
    polygon2List.push_back( Vector2Make(624, 446) );
    polygon2List.push_back( Vector2Make(908, 319) );
    polygon2List.push_back( Vector2Make(873, 259) );
    polygon2List.push_back( Vector2Make(703, 229) );
    polygon2List.push_back( Vector2Make(689, 0) );
    polygon2List.push_back( Vector2Make(1280, 0) );
    polygon2List.push_back( Vector2Make(1280, 540) );
    polygon2List.push_back( Vector2Make(0, 540) );
//    polygon2List.push_back( Vector2Make(0, 540) );
    Polygon polygon2(polygon2List);

    std::vector<Polygon> polygonList;
    polygonList.push_back(polygon1);
    polygonList.push_back(polygon2);

    m_walkingBoxes = new PathFinder(polygonList);
}

void Engine::SetCapRate(int fps)
{
    m_fpsCap = fps;
    m_fpsCapInverse = 1.0f / (float)fps;
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

            case EVENT_MOUSEMOVE:
            {
                break;
            }

            case EVENT_MOUSEUP:
            {
                MouseClicked();
                break;
            }

            case EVENT_QUIT:
            {
                return 1;
            }
        };
    };

    m_engineProvider.GetMousePosition(&m_mousePosition.x, &m_mousePosition.y);
    m_mousePosition.x /= m_viewportScale;
    m_mousePosition.y /= m_viewportScale;

    m_mousePosition.x -= m_viewportOffset.x;
    m_mousePosition.y -= m_viewportOffset.y;

    return 0;
}

void Engine::update()
{
    // Calculate performance
    MeasurePerformanceStart();

    // Clear the window background
    m_engineProvider.SetRenderBackgroundColor(0, 0, 0, 255);
    m_engineProvider.ClearRender();

    // Push the buffer texture. All scene will be rendered to a buffer texture
    m_engineProvider.RendererTargetPush(m_bufferTexture);

    // Clear the game background
    m_engineProvider.SetRenderBackgroundColor(255, 0, 0, 120);
    m_engineProvider.ClearRender();

    // Render scene
    RenderScene();

    // Pop the buffer texture. Blit the render to the screen.
    m_engineProvider.RendererTargetPop();

    ApplyScaleTransformations();

    // Draw the back buffer texture
    m_engineProvider.DrawTexture(m_bufferTexture, m_viewportOffset.x, m_viewportOffset.y);

    // Draw the texts
    m_engineProvider.RenderSetScale(1.0f, 1.0f);
    RenderSceneTexts();

    // Render the current stack
    m_engineProvider.RenderPresent();

    // Calculate performance
    MeasurePerformanceEnd();
}

void Engine::MeasurePerformanceStart()
{
    m_performanceStart = m_engineProvider.GetPerformanceCounter();
}

void Engine::MeasurePerformanceEnd()
{
    m_performanceEnd = m_engineProvider.GetPerformanceCounter();
    m_performanceDelta = m_performanceEnd - m_performanceStart;
    m_seconds = m_performanceDelta / (float)SDL_GetPerformanceFrequency();
    m_milliseconds = m_seconds * 1000;
    m_previousFps = 1.0f / m_seconds;

    m_engineProvider.Delay(floor(m_fpsCapInverse - m_milliseconds));
}

void Engine::RenderScene()
{
    m_scriptingEngine.callUpdate();
    m_characterMover->Update();

    m_walkingBoxes->Draw();
}

void Engine::RenderSceneTexts()
{
#if SHOW_FPS
    sprintf(m_fpsBuffer, "%.0f", m_previousFps);
    //m_engineProvider.DrawText(m_fpsFont, m_fpsBuffer, 0, 0, 255, 255, 255, TEXT_ALIGN_LEFT);
#endif
    static char mousePos[256];
    sprintf(mousePos, "%d x %d", m_mousePosition.x, m_mousePosition.y);
    m_engineProvider.DrawText(m_fpsFont, mousePos, 200, 0, 255, 255, 255, TEXT_ALIGN_LEFT);
}

void Engine::ApplyScaleTransformations()
{
    // Apply scaling transformation due to possible window resize
    int windowW, windowH;
    m_engineProvider.GetWindowSize(&windowW, &windowH);

    float scaleX, scaleY;
    scaleX = (float)windowW / (float)m_viewportSize.width;
    scaleY = (float)windowH / (float)m_viewportSize.height;

    m_viewportScale = std::min(scaleX, scaleY);
    m_engineProvider.RenderSetScale(m_viewportScale, m_viewportScale);

    int targetWidth = m_viewportSize.width * m_viewportScale;
    int targetHeight = m_viewportSize.height * m_viewportScale;

    m_viewportOffset = OriginMake(
        ((windowW - targetWidth) / 2)/m_viewportScale,
        ((windowH - targetHeight) / 2)/m_viewportScale
    );
}

void Engine::MouseClicked()
{
//    m_character->SetTalking(!m_character->IsTalking());
//    m_characterMover->MoveCharacter(m_mousePosition);
    Origin pos = m_characterMover->GetCharacterPosition();
    Vector2 from = Vector2Make(pos.x, pos.y);
    m_walkingBoxes->CalculatePathTo(from, Vector2Make(m_mousePosition.x, m_mousePosition.y));
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
    m_spriteDraws.clear();
}
