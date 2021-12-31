//
//  scene_manager.hpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#ifndef scene_manager_hpp
#define scene_manager_hpp

#include "scripting_engine_provider_interface.h"
#include "scene.hpp"

namespace engine
{

    class SceneManager
    {
    public:
        SceneManager(): m_currentScene(nullptr) { };

    public:
        /// Creates a new scene. Removes the old one and removes it data.
        _LUA_EXPOSED("sceneCreateNew")
        Scene* SceneCreateNew();

        /// Get the current scene.
        _LUA_EXPOSED("sceneGetCurrent")
        Scene* SceneGetCurrent() { return m_currentScene.get(); };

        /// Unload the current scene.
        _LUA_EXPOSED("sceneUnloadCurrent")
        void SceneUnloadCurrent();
        
    private:
        std::unique_ptr<Scene> m_currentScene;

    /// ScriptingInterface
    public:
        /** @private */
        SCRIPTING_INTERFACE_HEADERS(SceneManager);
    };
};

#endif /* scene_manager_hpp */
