//
//  scene_manager_interface.h
//  Engine
//
//  Created by krzysp on 25/09/2022.
//

#ifndef scene_manager_interface_h
#define scene_manager_interface_h

#include "scene_interface.h"

namespace engine
{
    /** SceneManagerI
        \addtogroup API_GLOBALS

        Manages the scene. Only the current screen renders its resources on-screen.
        Note that scene management does not impact game input handling nor any other
        non-scene related event observers.
     */
    class SceneManagerI
    {
    public:

        /** Creates a new scene. Removes the old one and removes it data. */
        virtual SceneI* SceneCreateNew() = 0;

        /** Get the current scene */
        virtual SceneI* SceneGetCurrent() = 0;

        /** Unload the current scene. */
        virtual void SceneUnload(SceneI*) = 0;

        /** Make active. */
        virtual void SceneMakeActive(SceneI*) = 0;
    };
};

#endif /* scene_manager_interface_h */
