//
//  scene_manager.hpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#ifndef scene_manager_hpp
#define scene_manager_hpp

#include "scene_interface.h"
#include "scene_manager_interface.h"

namespace engine
{

    /**
     SceneManager
     \addtogroup API_GLOBALS
     */
    /**
     Manages the scene. Loading a new scene should unload the previous
     scene's resources.
     */
    class SceneManager: public SceneManagerI
    {
    public:
        SceneManager()
        :   m_current(nullptr)
        { };

    public: // SceneManagerI
        SceneI* SceneCreateNew();
        SceneI* SceneGetCurrent();
        void SceneUnload(SceneI*);
        void SceneMakeActive(SceneI*);

    private:
        std::vector<std::unique_ptr<SceneI>>::iterator GetFor(SceneI*);

    private:
        std::vector<std::unique_ptr<SceneI>> m_scenes;
        SceneI* m_current;
//
//    /// ScriptingInterface
//    public:
//        /** @private */
//        SCRIPTING_INTERFACE_HEADERS(SceneManager);
    };
};

#endif /* scene_manager_hpp */
