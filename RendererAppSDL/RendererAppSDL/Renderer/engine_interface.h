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

namespace engine
{
    class EngineI
    {
    public:
        ///
        EngineI(EngineProviderI &engineProvider, FileAccessI &fileAccess, ScriptingEngineI &scriptingEngine)
        : m_engineProvider(engineProvider), m_fileAccess(fileAccess), m_scriptingEngine(scriptingEngine)
        { }

        /// The main setup. All engine components should be
        /// loaded by the concrete class after this call.
        virtual void setup() = 0;

        /// The main `update` method.
        /// Engine magic happens there.
        virtual void update() = 0;

        /// A concrete instance should load the texture.
        /// If a texture exists for a given name the existing
        /// texture will be returned.
        /// The engine takes the ownership of the texture and add it to the
        /// textures cache. You (the caller) must remove the
        /// texture by using `UnloadTexture` or `DisposeAllTextures`.
        virtual TextureI *LoadTexture(std::string name) = 0;

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

    public:
        ///
        EngineProviderI& getProvider() { return m_engineProvider; };

        ///
        ScriptingEngineI& getScripting() { return m_scriptingEngine; };

        ///
        FileAccessI& getFileAccess() { return m_fileAccess; };

    protected:
        EngineProviderI &m_engineProvider;
        FileAccessI &m_fileAccess;
        ScriptingEngineI &m_scriptingEngine;
    };
};

#endif /* engine_interface_h */
