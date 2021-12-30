//
//  scene.hpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#ifndef scene_hpp
#define scene_hpp

#include "scripting_engine_provider_interface.h"
#include "sprite_draw_static.hpp"
#include "sprite_draw_animated.hpp"
#include <iostream>

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

    /// Helper setup with smaller boilerplate
    public:
        
    /// Setup using originally exposed functions.
    public:
        ///
        _LUA_EXPOSED("addSpriteDrawStatic")
        void AddSpriteDrawStatic(SpriteDrawStatic*);

        ///
        void AddSpriteDrawAnimated(SpriteDrawAnimated*);

    /// Variables
    private:
        std::vector<SpriteDrawStatic*> m_staticSprites;

    /// ScriptingInterface
    public:
        SCRIPTING_INTERFACE_HEADERS(Scene);
    };
};

#endif /* scene_hpp */
