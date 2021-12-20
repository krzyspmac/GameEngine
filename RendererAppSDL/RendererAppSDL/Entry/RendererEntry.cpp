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
    this->m_fileAccess = new FileAccess();
    this->m_engineProvider = new EngineProvider();
    this->m_scriptingEngine = new ScriptingEngine(this->m_engineProvider);
    this->m_engine = new Engine(*this->m_engineProvider, *this->m_fileAccess, *this->m_scriptingEngine);
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

    return 0;
}

void RendererEntry::main(int argc, const char *argv[])
{
    if(initSDL())
    {
        std::cout << "Could not initialize SDL" << "\n";
        return;
    }

    while(true)
    {
    
    }
}

}; // namespace
