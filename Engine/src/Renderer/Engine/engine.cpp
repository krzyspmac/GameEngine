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
#include "sprite_draw_static.hpp"
#include "sprite_draw_animated.hpp"
#include "character_renderer.hpp"
#include "character.hpp"
#include "character_mover.hpp"
#include "polygon_loader.hpp"
#include "animation_curve_factory.hpp"

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
: EngineI(engineProvider, textureManager, fileAccess, fontManager, scriptingEngine, eventProvider, eventsManager, characterManager, sceneManager, spriteAtlasManager, spriteRendererManager, consoleRenderer, viewportSize), m_viewportScale(1)
{
    sharedEngine = this;
    SetCapRate(60);
    AnimationCurveFactory::Prepare();
}

Engine::~Engine()
{
    delete m_bufferTexture;
}

void Engine::Setup()
{
    // Register time helper for future reference.
    // Needed to scripts at the start of execution.
    m_time.Prepare();

    m_fileAccess.LoadDirectory(m_fileAccess.GetResourcesDirectory());
#if SHOW_FPS
    m_displayFont = new FontBitmapRepresentation("DialogFont_retro.fnt", "DialogFont_retro.png");
#endif

    m_bufferTexture = m_engineProvider.CreateTargetTexture(m_viewportSize.width, m_viewportSize.height);

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
    m_eventsManager.RegisterMouseMovedEvents(EventHolderMouseMoved([&](Origin *origin){
        m_mousePosition = *origin;

        m_mousePosition.x /= m_viewportScale;
        m_mousePosition.y /= m_viewportScale;

        m_mousePosition.x -= m_viewportOffset.x;
        m_mousePosition.y -= m_viewportOffset.y;
    }));

#if SHOW_CONSOLE
    m_consoleRenderer.SetConsoleHidden(false);
#endif
}

void Engine::SetCapRate(int fps)
{
    m_fpsCap = fps;
    m_fpsCapInverse = (1.0f / (float)fps) * 1000.f;
}

int Engine::doInput()
{
    int result = m_eventsManager.DoEvents();
    return result;
}

void Engine::FrameBegin()
{

}

void Engine::FrameDraw()
{
    // Update the time object
    m_time.PreUpdate();

    m_engineProvider.GetRendererOutputSize(&m_rendererOutputSize.width, &m_rendererOutputSize.height);

    // Calculate performance
    MeasurePerformanceStart();

    // Clear the window background
    m_engineProvider.SetRenderBackgroundColor(0, 0, 0, 255);
    m_engineProvider.ClearRender();

    // Push the buffer texture. All scene will be rendered to a buffer texture
//    m_engineProvider.RendererTargetPush(m_bufferTexture);

    // Clear the game background
    m_engineProvider.SetRenderBackgroundColor(0, 0, 0, 255);
    m_engineProvider.ClearRender();

    // Render scene
    RenderScene();

    // Pop the buffer texture. Blit the render to the screen.
//    m_engineProvider.RendererTargetPop();

    ApplyScaleTransformations();

    // Draw the back buffer texture
    m_engineProvider.DrawTexture(m_bufferTexture, m_viewportOffset.x, m_viewportOffset.y);

    // Draw the texts
    m_engineProvider.RenderSetScale(1.0f, 1.0f);
    RenderSceneTexts();

    // Render the current stack
    m_engineProvider.RenderPresent();

    // Update the time object
    m_time.PostUpdate();

    // Calculate performance
    MeasurePerformanceEnd();

#if SHOW_CONSOLE
    // Render the console if needed
//    m_consoleRenderer.DoFrame();
#endif
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

    //m_engineProvider.Delay(MAX(0, floor(m_fpsCapInverse - m_milliseconds)));
}

void Engine::RenderScene()
{
    Scene *scene = m_sceneManager.SceneGetCurrent();
    if (scene != nullptr)
    {
        scene->RenderScene();
    }

    m_periodicUpdatesManager.Update();
    m_scriptingEngine.callUpdate();
}

void Engine::RenderSceneTexts()
{
#if SHOW_FPS
    sprintf(m_fpsBuffer, "%.0f", m_previousFps);
    m_displayFont->DrawAt(m_fpsBuffer, 0, 0, 255, 255, 255, 255, TEXT_ALIGN_LEFT);
#endif
    static char mousePos[256];
    sprintf(mousePos, "%d x %d", m_mousePosition.x, m_mousePosition.y);
    m_displayFont->DrawAt(mousePos, 200, 0, 255, 255, 255, 255, TEXT_ALIGN_LEFT);
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
}
