//
//  scene.hpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#ifndef scene_hpp
#define scene_hpp

#include "scripting_engine_provider_interface.h"

namespace engine
{
    class Scene
    {
    ///
    public:
        Scene();
        ~Scene();

    /// Rederer
    public:
        /// Render the scene including all the objects that have been
        /// added to it.
        void RenderScene();

    /// Setup
    public:

    /// ScriptingInterface
    public:
        SCRIPTING_INTERFACE_HEADERS(Scene);
    };
};

#endif /* scene_hpp */
