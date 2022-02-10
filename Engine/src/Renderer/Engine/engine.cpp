//
//  engine.cpp
//  RendererApp
//
//  Created by krzysp on 19/12/2021.
//

#include "engine.hpp"
#include "font_bitmap.hpp"
#include "sprite_atlas_interface.h"
#include "sprite_atlas.hpp"
#include "sprite_representation_static.hpp"
#include "sprite_draw_animated.hpp"
#include "character_renderer.hpp"
#include "character.hpp"
#include "character_mover.hpp"
#include "polygon_loader.hpp"
#include "animation_curve_factory.hpp"
#include "ini_reader.hpp"

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

Engine::Engine(EngineProviderI &engineProvider,
               TextureManager &textureManager,
               FileAccessI &fileAccess,
               FontManager &fontManager,
               ScriptingEngineI &scriptingEngine,
               EventProviderI &eventProvider,
               EventsManager &eventsManager,
               CharacterManager &characterManager,
               SceneManager &sceneManager,
               SpriteAtlasManager &spriteAtlasManager,
               SpriteRendererManager &spriteRendererManager,
               ConsoleRendererI &consoleRenderer,
               Size viewportSize
               )
    : EngineI(engineProvider, textureManager, fileAccess, fontManager, scriptingEngine, eventProvider, eventsManager, characterManager, sceneManager, spriteAtlasManager, spriteRendererManager, consoleRenderer, viewportSize)
    , m_viewportScale(1)
{
    sharedEngine = this;
    SetCapRate(60);

    EngineSetup setup;
    setup.resolution.width = 320;
    setup.resolution.height = 200;
    setup.affineScale = 1.0f;
    setup.isDirty = false;

    AnimationCurveFactory::Prepare();
}

Engine::~Engine()
{
}

void Engine::Setup()
{
    // Preare the file access functions
    m_fileAccess.LoadDirectory(m_fileAccess.GetResourcesDirectory());

    // Read the ini file. If not existing - exit with a proper message.
    try
    {
        std::string path = m_fileAccess.GetFullPath("main.ini");
        IniReader reader(path);
        m_engineSetup = reader.GetSetup();
    }
    catch (const char* exception)
    {
        printf("Exception found while loading main.ini: %s.\n", exception);
        exit(1);
    }

    // Register time helper for future reference.
    // Needed to scripts at the start of execution.
    m_time.Prepare();

    // Load some debug fonts
#if SHOW_FPS
    m_displayFont = new FontBitmapRepresentation("DialogFont_retro.fnt", "DialogFont_retro.png", 1);
#endif

    // Load the main script file
    std::unique_ptr<FileStreamI> streamBuffer(m_fileAccess.GetAccess("main.lua"));

    m_scriptingEngine.newState();
    m_scriptingEngine.loadFile(streamBuffer.get());
    m_scriptingEngine.registerFunctions();
    m_scriptingEngine.callInit();

    m_engineProvider.SetRenderBackgroundColor(0, 0, 0, 255);
    m_engineProvider.ClearRender();

    // Register events listeners. For simple events - use lambda.
    // Complex events get their own handler.

    // Register & process mouse events
    m_mousePosition.x = 0;
    m_mousePosition.y = 0;
    m_eventsManager.RegisterMouseMovedEvents([&](Origin *origin){
        m_mousePosition.x = origin->x;
        m_mousePosition.y = origin->y;
    });

#if SHOW_CONSOLE
    m_consoleRenderer.Setup();
    m_consoleRenderer.SetConsoleHidden(true);
#endif
}

void Engine::SetCapRate(int fps)
{
    m_fpsCap = fps;
    m_fpsCapInverse = (1.0f / (float)fps) * 1000.f;
}

int Engine::ProcessEvents()
{
    int result = m_eventsManager.DoEvents();
    return result;
}

void Engine::FrameBegin()
{
    // Update the time object
    m_time.PreUpdate();

    // Calculate performance
    MeasurePerformanceStart();

    // Periodic updates update
    m_periodicUpdatesManager.Update();
}

void Engine::ProcessScript()
{
    m_scriptingEngine.callUpdate();
}

void Engine::FrameDrawBackgroundObjects()
{
    Scene *scene = m_sceneManager.SceneGetCurrent();
    if (scene != nullptr)
    {
        scene->RenderSceneBackground();
    }
}

void Engine::FrameDrawForegroundObjects()
{
    Scene *scene = m_sceneManager.SceneGetCurrent();
    if (scene != nullptr)
    {
        scene->RenderSceneForeground();
    }
}

void Engine::FrameDrawLightObjects()
{
}

void Engine::FrameDrawTopObjects()
{
    // Draw the texts
    RenderSceneTexts();
}

void Engine::FrameEnd()
{
    // Update the time object
    m_time.PostUpdate();

    // Calculate performance
    MeasurePerformanceEnd();
}

void Engine::MeasurePerformanceStart()
{
    m_performanceStart = m_engineProvider.GetPerformanceCounter();
}

void Engine::MeasurePerformanceEnd()
{
//    m_performanceEnd = m_engineProvider.GetPerformanceCounter();
//    m_performanceDelta = m_performanceEnd - m_performanceStart;
//    m_seconds = m_performanceDelta / (float)SDL_GetPerformanceFrequency();
//    m_milliseconds = m_seconds * 1000;
//    m_previousFps = 1.0f / m_seconds;
}

void Engine::RenderScene()
{
}

void Engine::RenderSceneTexts()
{
#if SHOW_FPS
//    sprintf(m_fpsBuffer, "%.0f", m_previousFps);
//    m_displayFont->DrawAt(m_fpsBuffer, 0, 10, 255, 255, 255, 255, TEXT_ALIGN_LEFT);
#endif
    static char mousePos[256];
    sprintf(mousePos, "%d x %d", m_mousePosition.x, m_mousePosition.y);
    sprintf(mousePos, "Mouse testing: %d x %d", m_mousePosition.x, m_mousePosition.y);

    m_displayFont->DrawAt(mousePos, 0, 0, 255, 255, 255, 255, TEXT_ALIGN_LEFT);
}

void Engine::ApplyScaleTransformations()
{
//    // Apply scaling transformation due to possible window resize
//    int windowW, windowH;
//    m_engineProvider.GetWindowSize(&windowW, &windowH);
//
//    float scaleX, scaleY;
//    scaleX = (float)windowW / (float)m_viewportSize.width;
//    scaleY = (float)windowH / (float)m_viewportSize.height;
//
//    m_viewportScale = std::min(scaleX, scaleY);
//    m_engineProvider.RenderSetScale(m_viewportScale, m_viewportScale);
//
//    int targetWidth = m_viewportSize.width * m_viewportScale;
//    int targetHeight = m_viewportSize.height * m_viewportScale;
//
//    m_viewportOffset = OriginMake(
//        ((windowW - targetWidth) / 2)/m_viewportScale,
//        ((windowH - targetHeight) / 2)/m_viewportScale
//    );
}

void Engine::MouseClicked()
{
}
