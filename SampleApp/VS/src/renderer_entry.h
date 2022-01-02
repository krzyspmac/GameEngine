#pragma once

#include "common_engine_impl.h"

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

        void doMain(int argc, char* argv[]);

    private:
        //engine::FileAccessI* m_fileAccess;
        //engine::EngineProviderI* m_engineProvider;
        //engine::ScriptingEngineI* m_scriptingEngine;
        //engine::EventProviderI* m_eventProvider;
        //engine::EventsManager* m_eventsManager;
        //engine::CharacterManager* m_characterManager;
        //engine::SceneManager* m_sceneManager;
        //engine::SpriteAtlasManager* m_spriteAtlasManager;
        //engine::SpriteRendererManager* m_sprireRendererManager;
        //engine::Engine* m_engine;
        engine::SDL_APP m_app;
    };

}; // namespace
