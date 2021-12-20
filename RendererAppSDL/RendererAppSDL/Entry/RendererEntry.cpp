//
//  RendererEntry.cpp
//  RendererAppSDL
//
//  Created by krzysp on 20/12/2021.
//

#include "RendererEntry.hpp"
#include "file_access.hpp"
#include "engine_provider.hpp"
#include "scripting_engine.hpp"
#include "engine.hpp"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SPRITE_SIZE    32

namespace engine
{

RendererEntry::RendererEntry()
{
    FileAccess *fa = new FileAccess();;
    EngineProvider *ep = new EngineProvider(&m_app);
    ScriptingEngine *se = new ScriptingEngine();

    this->m_fileAccess = fa;
    this->m_engineProvider = ep;
    this->m_scriptingEngine = se;
    this->m_engine = new Engine(*this->m_engineProvider, *this->m_fileAccess, *this->m_scriptingEngine);

    se->setEngine(m_engine);
}

int RendererEntry::initSDL()
{
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED;
    windowFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    m_app.window = SDL_CreateWindow("Shooter 01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

    if(!m_app.window)
    {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    m_app.renderer = SDL_CreateRenderer(m_app.window, -1, rendererFlags);

    if (!m_app.renderer)
    {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }

//    SDL_ShowCursor(0);

    m_engine->LoadTexture(m_fileAccess->getBundledFilepath("background.jpg"));

    return 0;
}

void RendererEntry::prepare()
{
    SDL_SetRenderDrawColor(m_app.renderer, 96, 128, 255, 255);
    SDL_RenderClear(m_app.renderer);
    m_engine->setup();
}

void RendererEntry::doInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                delete (m_engine);
                exit(0);
            break;

            default:
                break;
        }
    }
}

void RendererEntry::doScene()
{
    m_engine->update();
    SDL_RenderPresent(m_app.renderer);
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
        doInput();
        doScene();
        SDL_Delay(1);
    }
}

}; // namespace
