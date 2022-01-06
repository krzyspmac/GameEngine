//
//  RendererEntry.hpp
//  RendererAppSDL
//
//  Created by krzysp on 20/12/2021.
//

#ifndef RendererEntry_hpp
#define RendererEntry_hpp

#include <stdio.h>
#include "common.h"
#include "file_access_provider.h"
#include "engine_provider_interface.h"
#include "scripting_engine_provider_interface.h"
#include "engine_interface.h"
#include "engine.hpp"
#include "events_manager.hpp"
#include "character_manager.hpp"
#include "scene_manager.hpp"
#include "sprite_atlas_manager.hpp"
#include "sprite_renderer_manager.hpp"

namespace engine
{

class RendererEntry
{
public:
    ///
    RendererEntry();

    ///
    int initSDL();

    void destroy();

    void prepare();

    void doInput();

    void doScene();

    ///
    void main(int argc, const char *argv[]);

private:
    engine::FileAccessI *m_fileAccess;
    engine::EngineProviderI *m_engineProvider;
    engine::ScriptingEngineI *m_scriptingEngine;
    engine::EventProviderI *m_eventProvider;
    engine::EventsManager *m_eventsManager;
    engine::CharacterManager *m_characterManager;
    engine::SceneManager *m_sceneManager;
    engine::SpriteAtlasManager *m_spriteAtlasManager;
    engine::SpriteRendererManager *m_sprireRendererManager;
    engine::Engine *m_engine;
    engine::SDL_APP m_app;
};

}; // namespace

#endif /* RendererEntry_hpp */
