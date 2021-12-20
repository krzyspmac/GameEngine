//
//  RendererEntry.hpp
//  RendererAppSDL
//
//  Created by krzysp on 20/12/2021.
//

#ifndef RendererEntry_hpp
#define RendererEntry_hpp

#include <stdio.h>
#include "file_access_provider.h"
#include "engine_provider_interface.h"
#include "scripting_engine_provider_interface.h"
#include "engine_interface.h"
#include "SDL.h"

namespace engine
{

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
} SDL_APP;

class RendererEntry
{
public:
    ///
    RendererEntry();

    ///
    int initSDL();

    void prepare();

    void doInput();

    void doScene();

    ///
    void main(int argc, const char *argv[]);

private:
    engine::FileAccessI *m_fileAccess;
    engine::EngineProviderI *m_engineProvider;
    engine::ScriptingEngineI *m_scriptingEngine;
    engine::EngineI *m_engine;
    engine::SDL_APP m_app;
};

}; // namespace

#endif /* RendererEntry_hpp */
