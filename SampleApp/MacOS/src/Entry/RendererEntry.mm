//
//  RendererEntry.cpp
//  RendererAppSDL
//
//  Created by krzysp on 20/12/2021.
//

#include "RendererEntry.hpp"
#include "file_access.hpp"
#include "scripting_engine.hpp"
#include "event_provider.hpp"
#include "engine.hpp"
#include "common_sdl.h"

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720
#define ASPECT_RATIO (640/480)

using namespace engine;

RendererEntry::RendererEntry()
{
    SDL_APP *sdl_app = new SDL_APP();

    FileAccess *fa = new FileAccess();
    TextureManager *tm = new TextureManager();
    EngineProviderSDL *ep = new EngineProviderSDL(sdl_app);
    FontManager *fm  = new FontManager();
    ScriptingEngine *se = new ScriptingEngine();
    EventProvider *eventProvider = new EventProvider();
    EventsManager *eventsManager = new EventsManager(*eventProvider, *ep);
    CharacterManager *characteManager = new CharacterManager();
    SceneManager *sceneManager = new SceneManager();
    SpriteAtlasManager * spriteAtlasManager = new SpriteAtlasManager();
    SpriteRendererManager *sprireRendererManager = new SpriteRendererManager();
    ConsoleRenderer *consoleRenderer = new ConsoleRenderer();


    this->m_fileAccess = fa;
    this->m_textureManager = tm;
    this->m_engineProvider = ep;
    this->m_fontManager = fm;
    this->m_scriptingEngine = se;
    this->m_eventProvider = eventProvider;
    this->m_eventsManager = eventsManager;
    this->m_characterManager = characteManager;
    this->m_sceneManager = sceneManager;
    this->m_spriteAtlasManager = spriteAtlasManager;
    this->m_sprireRendererManager = sprireRendererManager;
    this->m_consoleRenderer = consoleRenderer;

    Size viewportSize;
    viewportSize.width = SCREEN_WIDTH;
    viewportSize.height = SCREEN_HEIGHT;
    this->m_engine = new Engine(*this->m_engineProvider, *this->m_textureManager, *this->m_fileAccess, *this->m_fontManager, *this->m_scriptingEngine, *this->m_eventProvider, *this->m_eventsManager, *this->m_characterManager, *this->m_sceneManager, *this->m_spriteAtlasManager, *this->m_sprireRendererManager, *this->m_consoleRenderer, viewportSize);
}

int RendererEntry::initSDL()
{
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    windowFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    if (TTF_Init() < 0)
    {
        printf("Couldn't initialize SDL TTF: %s\n", SDL_GetError());
        exit(1);
    }

    m_engineProvider->GetRendererHandle()->window = SDL_CreateWindow("SomeEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

    if(!m_engineProvider->GetRendererHandle()->window)
    {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    SDL_SetWindowResizable(m_engineProvider->GetRendererHandle()->window, SDL_TRUE);
//    SDL_SetWindowFullscreen(m_app.window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    SDL_SetHintWithPriority(SDL_HINT_RENDER_SCALE_QUALITY, "nearest", SDL_HINT_OVERRIDE);
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "metal");
    m_engineProvider->GetRendererHandle()->renderer = SDL_CreateRenderer(m_engineProvider->GetRendererHandle()->window, -1, rendererFlags);

    if (!m_engineProvider->GetRendererHandle()->renderer)
    {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Cursor *cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
    SDL_SetCursor(cursor);
    SDL_ShowCursor(1);

    return 0;
}

void RendererEntry::destroy()
{
    delete (m_engine);
    SDL_DestroyRenderer(m_engineProvider->GetRendererHandle()->renderer);
    SDL_DestroyWindow(m_engineProvider->GetRendererHandle()->window);
    TTF_Quit();
    SDL_Quit();
}

void RendererEntry::prepare()
{
    m_engine->setup();
}

void RendererEntry::doInput()
{
    if (m_engine->doInput())
    {
        destroy();
        exit(0);
    }
}

void RendererEntry::doScene()
{
    m_engine->update();
}

void RendererEntry::main(int argc, const char *argv[])
{
    if(initSDL())
    {
        std::cout << "Could not initialize SDL" << "\n";
        return;
    }

    prepare();
    
    while(1)
    {
        @autoreleasepool
        {
            doInput();
            doScene();
        }
    }
}
