//
//  engine_interface.h
//  Renderer
//
//  Created by krzysp on 19/12/2021.
//

#ifndef engine_interface_h
#define engine_interface_h

#include "common_engine_impl.h"
#include "engine_provider_interface.h"
#include "file_access_provider.h"
#include "scripting_engine_provider_interface.h"
#include "event_provider_interface.h"
#include "sprite_draw_interface.h"
#include "events_manager.hpp"

namespace engine
{
    class EngineI
    {
    public:
        ///
        EngineI(EngineProviderI &engineProvider, FileAccessI &fileAccess, ScriptingEngineI &scriptingEngine, EventProviderI &eventProvider, EventsManager &eventsManager, Size viewportSize)
        : m_engineProvider(engineProvider), m_fileAccess(fileAccess), m_scriptingEngine(scriptingEngine), m_eventProvider(eventProvider), m_eventsManager(eventsManager), m_viewportSize(viewportSize)
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

    /// Behaviour
    public:
        /// Sets the cap rate. Default is 60.
        virtual void SetCapRate(int fps) = 0;

    /// Helper methods to deal with engine provider functionality
    /// so that things that need be cashed are cached propery.
    /// Also multiple methods should be called on-demant by the
    /// main renderer-entry that is platform specific.

    /// Textures
    public:
        /// A concrete instance should load the texture.
        /// If a texture exists for a given name the existing
        /// texture will be returned.
        /// The engine takes the ownership of the texture and add it to the
        /// textures cache. You (the caller) must remove the
        /// texture by using `UnloadTexture` or `DisposeAllTextures`.
        virtual TextureI *LoadTexture(std::string name) = 0;

        /// A concrete instance should create the texture. The texture
        /// *is not* added to a cache and the ownershop is passed onto the
        /// caller.
        virtual TextureTargetI *CreateTargetTexture(int width, int height) = 0;

        /// A concrete instance should get the existing texture
        /// by comparing texture name. Otherwise returns NULL.
        /// In such a case you must load the texture by using
        /// `LoadTexture`.
        virtual TextureI *GetTexture(std::string name) = 0;

        /// A concrete instance should unlaod the texture and
        /// remove it from the cache.
        virtual void UnloadTexture(TextureI *texture) = 0;

        /// A concrete instance should unlaod all the textures and
        /// remove them from the cache.
        virtual void DisposeAllTextures() = 0;

    /// Fonts
    public:

        /// Loads a font if not loaded previously.
        virtual FontI *LoadFont(std::string name) = 0;

        /// Gets the previously loaded font or returns nil;
        virtual FontI *GetFont(std::string name) = 0;

        /// Disposes of all fonts.
        virtual void DisposeAllFonts() = 0;

    /// Sprite atlas
    public:

        /// A concrete instance would load the sprite atlas, its texture (using ::LoadTexture) and the json
        /// file for individual sprite splices.
        virtual SpriteAtlasI *SpriteAtlasLoad(std::string jsonFilename, std::string textureFilename) = 0;

        ///
        virtual SpriteAtlasI *SpriteAtlasGet(std::string jsonFilename) = 0;

        ///
        virtual void SpriteAtlasUnload(SpriteAtlasI *atlas) = 0;

        ///
        virtual void SpriteAtlasDisposeAll() = 0;

    /// Drawing
    public:

        /// Creates or gets a drawing handle for a sprite
        virtual SpriteDrawI *SpriteDrawLoadStatic(SpriteAtlasItemI *sprite, int scale) = 0;

        /// Creates or gets a drawing handle for a sprite
        virtual SpriteDrawI *SpriteDrawLoadAnimated(std::vector<SpriteAtlasItemI*> sprites, int frameAnimationDurationMs, int scale) = 0;

        /// Unloads the sprite draw.
        virtual void SpriteDrawUnload(SpriteDrawI *spriteDraw) = 0;

        /// Unloads all.
        virtual void SpriteDrawDisposeAll() = 0;

    public:
        ///
        EngineProviderI& getProvider() { return m_engineProvider; };

        ///
        ScriptingEngineI& getScripting() { return m_scriptingEngine; };

        ///
        FileAccessI& getFileAccess() { return m_fileAccess; };

    protected:
        Size m_viewportSize;
        EngineProviderI &m_engineProvider;
        FileAccessI &m_fileAccess;
        ScriptingEngineI &m_scriptingEngine;
        EventProviderI &m_eventProvider;
        EventsManager &m_eventsManager;
        engine::Origin m_mousePosition;
    };

};

/// Main accessor for easy access.
engine::EngineI *GetMainEngine();

#endif /* engine_interface_h */

