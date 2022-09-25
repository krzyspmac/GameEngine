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
#include "sprite_atlas_manager_interface.h"
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
#include "engine_setup_interface.h"
#include "light_manager.hpp"
#include "sound_manager.hpp"
#include "engine_screen.hpp"
#include "engine_state_interface.h"

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
                m_time(engineProvider),
                m_lightManager(*(new LightManager())),
                m_soundManager(*(new SoundManager())),
                m_engineScreen(*(new EngineScreen())),
                m_engineState(*(new EngineState()))
        { }

    /// Setup
    public:

        /** Setup the ini & the EngineSetup structure */
        virtual void SetupInit() = 0;

        /** The main setup. All engine components should be
            loaded by the concrete class after this call.
         */
        virtual void Setup() = 0;

        /** A concrete instance will prepare the engine for the frame drawing.
            Just after this method a similar method will be called on the
            engine provider. In case of metal a RenderCommandEncoder will be stored
            in the provider so that the drawing functions have some rendering handle
            to deal with.s
         */
        virtual void FrameBegin() = 0;


        /** Process the inputs from the game.
            Return != 0 do quit the application.
        */
        virtual int ProcessEvents() = 0;

        /** Entry point for a concrete instance to process the script functions
         */
        virtual void ProcessScript() = 0;

        /** The `update` method. Draw the foreground items.
         */
        virtual void FrameDrawObjects() = 0;

        /** The `update` method. Draw the top most items. Those do not get any effects.
         */
        virtual void FrameDrawTopObjects() = 0;

        /** The `update` method. Draw the light items.
         */
        virtual void FrameDrawLightObjects() = 0;

        /** Executed at the end of the frame pass */
        virtual void FrameEnd() = 0;

    /// States
    public:

        /** Get the resolution set in the main ini file */
        auto& GetEngineSetup() { return m_engineSetup; };

        /** Get the current viewport size */
        Size &GetViewport() { return m_viewportSize; };

        /** Set the viewport scale to match the current screen the engine in on */
        void SetViewportScale(float val) { m_engineProvider.SetViewportScale(val); m_viewportScale = val; };

        /** Get the viewport scale to match the current screen the engine in on */
        float GetViewportScale() { return m_viewportScale; };

        /** Get Mouse position */
        engine::Origin& GetMousPosition() { return m_mousePosition; };

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
        FontManagerI& getFontManager() { return m_fontManager; };

        ///
        CharacterManager& getCharacterManager() { return m_characterManager; };

        ///
        SceneManager& getSceneManager() { return m_sceneManager; };

        ///
        LightManager& getLightMnaager() { return m_lightManager; };

        ///
        SoundManager& getSoundManager() { return m_soundManager; };

        ///
        SpriteAtlasManagerI& getAtlasManager() { return m_spriteAtlasManager; };

        ///
        SpriteRendererManager& getSpriteRendererManager() { return m_spriteRendererManager; };

        ///
        EventsManager& getEventsManager() { return m_eventsManager; };

        ///
        EventProviderI& getEventProvider() { return m_eventProvider; };

        ///
        Time& getTime() { return m_time; };

        ///
        ValueAnimatorFactory& getValueAnimatorFactory() { return m_valueAnimatorFactory; };

        ///
        PropertyAnimatorFactory& getPropertyAnimatorFactory() { return m_propertyAnimatorFactory; };

        ///
        PeriodicUpdatesManager& getPeriodicUpdatesManager() { return m_periodicUpdatesManager; };

        ///
        EngineStateI& getEngineState() { return m_engineState; };

        ///
        EngineScreen& getEngineScreen() { return m_engineScreen; };
        
        ///
        MemoryReleasePool& getReleasePool() { return m_releasePool; };
        
        ///
        AnimationGroupFactory& getAnimationGroupFactory() { return m_animationGroupFactory; };

        ///
        ConsoleRendererI& getConsoleRenderer() { return m_consoleRenderer; };

    /// Other states
    public:

    protected:
        EngineSetup m_engineSetup;

        Size m_viewportSize;
        float m_viewportScale;
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
        LightManager &m_lightManager;
        SoundManager &m_soundManager;
        EngineScreen &m_engineScreen;
        EngineStateI &m_engineState;

        engine::Origin m_mousePosition;
        Time m_time;
        ValueAnimatorFactory m_valueAnimatorFactory;
        PropertyAnimatorFactory m_propertyAnimatorFactory;
        PeriodicUpdatesManager m_periodicUpdatesManager;
        AnimationGroupFactory m_animationGroupFactory;
        MemoryReleasePool m_releasePool;
        ConsoleRendererI &m_consoleRenderer;
    };

};

/// Main accessor for easy access.
engine::EngineI &ENGINE();

#endif /* engine_interface_h */

