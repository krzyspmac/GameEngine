//
//  engine_interface.h
//  Renderer
//
//  Created by krzysp on 19/12/2021.
//

#ifndef engine_interface_h
#define engine_interface_h

#include "engine_provider_interface.h"
#include "file_access_provider.h"
#include "scripting_engine_provider_interface.h"
#include "event_provider_interface.h"
#include "sprite_draw_interface.h"
#include "events_manager.hpp"
#include "character_manager.hpp"
#include "scene_manager.hpp"
#include "sprite_atlas_manager.hpp"
#include "sprite_renderer_manager.hpp"
#include "periodic_updates_manager.hpp"
#include "value_animator_factory.hpp"
#include "property_animator_factory.hpp"
#include "time.hpp"
#include "engine_state.hpp"
#include "release_pool.hpp"
#include "animation_group_factory.hpp"
#include "console_renderer.h"
#include "texture_manager.hpp"
#include "font_manager.hpp"

namespace engine
{
    class EngineI
    {
    public:
        ///
        EngineI(EngineProviderI &engineProvider,
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
        :       m_engineProvider(engineProvider),
                m_textureManager(textureManager),
                m_fileAccess(fileAccess),
                m_fontManager(fontManager),
                m_scriptingEngine(scriptingEngine),
                m_eventProvider(eventProvider),
                m_eventsManager(eventsManager),
                m_characterManager(characterManager),
                m_sceneManager(sceneManager),
                m_spriteAtlasManager(spriteAtlasManager),
                m_spriteRendererManager(spriteRendererManager),
                m_viewportSize(viewportSize),
                m_consoleRenderer(consoleRenderer),
                m_time(engineProvider)
        { }

    /// Setup
    public:
        /// The main setup. All engine components should be
        /// loaded by the concrete class after this call.
        virtual void setup() = 0;

        /// Process the inputs from the game.
        /// Return != 0 do quit the application.
        virtual int doInput() = 0;

        /// The main `update` method.
        /// Engine magic happens there.
        virtual void update() = 0;

    /// States
    public:
        Size &GetViewport() { return m_viewportSize; };

        Size &GetRendererOutputSize() { return m_rendererOutputSize; };

    /// Behaviour
    public:
        /// Sets the cap rate. Default is 60.
        virtual void SetCapRate(int fps) = 0;

    /// Helper methods to deal with engine provider functionality
    /// so that things that need be cashed are cached propery.
    /// Also multiple methods should be called on-demant by the
    /// main renderer-entry that is platform specific.

    /// Animations & Periodic Updates
    public:

    /// Providers
    public:
        ///
        EngineProviderI& getProvider() { return m_engineProvider; };

        ///
        ScriptingEngineI& getScripting() { return m_scriptingEngine; };

        ///
        FileAccessI& getFileAccess() { return m_fileAccess; };

    /// Managers
    public:
        ///
        TextureManager &getTextureManager() { return m_textureManager; };

        ///
        FontManager& getFontManager() { return m_fontManager; };

        ///
        CharacterManager& getCharacterManager() { return m_characterManager; };

        ///
        SceneManager& getSceneManager() { return m_sceneManager; };

        ///
        SpriteAtlasManager& getAtlasManager() { return m_spriteAtlasManager; };

        ///
        SpriteRendererManager& getSpriteRendererManager() { return m_spriteRendererManager; };

        ///
        EventsManager& getEventsManager() { return m_eventsManager; };

        ///
        Time& getTime() { return m_time; };

        ///
        ValueAnimatorFactory& getValueAnimatorFactory() { return m_valueAnimatorFactory; };

        ///
        PropertyAnimatorFactory& getPropertyAnimatorFactory() { return m_propertyAnimatorFactory; };

        ///
        PeriodicUpdatesManager& getPeriodicUpdatesManager() { return m_periodicUpdatesManager; };

        ///
        EngineState& getEngineState() { return m_engineState; };
        
        ///
        MemoryReleasePool& getReleasePool() { return m_releasePool; };
        
        ///
        AnimationGroupFactory& getAnimationGroupFactory() { return m_animationGroupFactory; };

        ///
        ConsoleRendererI& getConsoleRenderer() { return m_consoleRenderer; };

    /// Other states
    public:

    protected:
        Size m_viewportSize;
        Size m_rendererOutputSize;
        EngineProviderI &m_engineProvider;
        FileAccessI &m_fileAccess;
        ScriptingEngineI &m_scriptingEngine;
        EventProviderI &m_eventProvider;
        EventsManager &m_eventsManager;

        TextureManager &m_textureManager;
        FontManager &m_fontManager;
        SpriteAtlasManager &m_spriteAtlasManager;
        SpriteRendererManager &m_spriteRendererManager;
        SceneManager &m_sceneManager;
        CharacterManager &m_characterManager;

        engine::Origin m_mousePosition;
        Time m_time;
        ValueAnimatorFactory m_valueAnimatorFactory;
        PropertyAnimatorFactory m_propertyAnimatorFactory;
        PeriodicUpdatesManager m_periodicUpdatesManager;
        EngineState m_engineState;
        AnimationGroupFactory m_animationGroupFactory;
        MemoryReleasePool m_releasePool;

        ConsoleRendererI &m_consoleRenderer;
    };

};

/// Main accessor for easy access.
engine::EngineI *GetMainEngine();

#endif /* engine_interface_h */

