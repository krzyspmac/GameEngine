// Copyright (c) 2022 Krzysztof Pawłowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

#include "engine.hpp"
#include "font_bitmap.hpp"
#include "sprite_atlas_interface.h"
#include "sprite_atlas.hpp"
#include "sprite_representation_static.hpp"
#include "sprite_representation_animated.hpp"
#include "character_renderer.hpp"
#include "character.hpp"
#include "character_mover.hpp"
#include "polygon_loader.hpp"
#include "animation_curve_factory.hpp"
#include "ini_reader.hpp"
#include "static_objects.hpp"

using namespace engine;

/// Main accessor for easy access.
EngineI *sharedEngine = NULL;
engine::EngineI &ENGINE()
{
    return *sharedEngine;
}

Engine::Engine(EngineProviderI &engineProvider,
               TextureManager &textureManager,
               FileAccessI &fileAccess,
               FontManager &fontManager,
               EventProviderI &eventProvider,
               EventsManager &eventsManager,
               CharacterManager &characterManager,
               SceneManager &sceneManager,
               SpriteAtlasManager &spriteAtlasManager,
               SpriteRendererManager &spriteRendererManager,
               ConsoleRendererI &consoleRenderer,
               Size viewportSize
               )
    : EngineI(engineProvider, textureManager, fileAccess, fontManager, eventProvider, eventsManager, characterManager, sceneManager, spriteAtlasManager, spriteRendererManager, consoleRenderer, viewportSize)
    , m_viewportScale(1)
{
    StaticObjects::init();
    StaticObjects::engine_provide(this);
    sharedEngine = this;
    SetCapRate(60);

    EngineSetup setup;
    setup.resolution.width = 320;
    setup.resolution.height = 200;
    setup.affineScale = 1.0f;
    setup.isDirty = false;

    m_animationCurveFactory.Prepare();
}

Engine::~Engine()
{
}

void Engine::SetupInit()
{
    // Read the ini file first. It may change various engine properties.
    try
    {
        std::string path = m_fileAccess.GetFullPath("GameResources/main.ini");
        IniReader reader(path);
        m_engineSetup = reader.GetSetup();
    }
    catch (const char* exception)
    {
        printf("Exception found while loading main.ini: %s.\n", exception);
        exit(1);
    }
}

void Engine::Setup()
{
    // Preare the file access functions
    m_fileAccess.LoadDirectory(m_engineSetup.gameFolder);

    // Register time helper for future reference.
    // Needed to scripts at the start of execution.
    m_time.Prepare();

    // Load some debug fonts
#if SHOW_FPS
    m_displayFont = new FontBitmapRepresentation("at01.fnt", "at01.png", 1);
    m_displayFont->SetZPosition(0);
#endif

    auto initFunction = ENGINE().GetEngineSetup().initFunction;
    if (initFunction == nullptr)
    {
        std::cout << "Error: No init function setup. Cannot start engine." << std::endl;
    }
    else
    {
        initFunction();
    }

    m_engineProvider.SetRenderBackgroundColor(0, 0, 0, 255);
    m_engineProvider.ClearRender();

    // Register events listeners. For simple events - use lambda.
    // Complex events get their own handler.

    // Register & process mouse events
    m_mousePosition.x = 0;
    m_mousePosition.y = 0;

    m_eventsManager.RegisterMouseMovedEvents(CallableParameters1<Origin>::make_shared([&](Origin origin){
        m_mousePosition.x = origin.x;
        m_mousePosition.y = origin.y;
    }));

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
    ENGINE().GetEngineSetup().frameUpdateFunction();
}

void Engine::FrameDrawObjects()
{
    SceneI *scene = m_sceneManager.SceneGetCurrent();
    if (scene != nullptr)
    {
        scene->RenderSceneSprites();
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

    static Color4 white = {1.f, 1.f, 1.f, 1.f};
    m_displayFont->DrawAt(mousePos, 20, 0, 255, 255, 255, 255, TEXT_ALIGN_LEFT, TEXT_ALIGN_TOP, white, 1.f);
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
