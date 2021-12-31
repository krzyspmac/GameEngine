//
//  scene.hpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#ifndef scene_hpp
#define scene_hpp

/**

\mainpage Some Project

...

See \ref API_EXPOSED "Public API" for details on these functions.

*/

#include "scripting_engine_provider_interface.h"
#include "sprite_draw_static.hpp"
#include "sprite_draw_animated.hpp"
#include "sprite_atlas.hpp"
#include <iostream>

namespace engine
{
    /**
     \ingroup API_EXPOSED
     */
    class Scene
    {
    ///
    public:
        Scene();
        ~Scene();

    /// Rederer
    public:
        /**
         Render the scene including all the objects that have been
         added to it.
        */
        void RenderScene();

    public:
        /** @name Exposed APIs
         */
        ///@{
        /**
         Helper method to oad the sprite and puts it into the stack.
         \include SampleSpriteStatic-helper.lua
         \ingroup API_EXPOSED
         \see Scene::AddSpriteDrawStatic.
         */
        SpriteDrawStatic *LoadSpriteStatic(SpriteAtlas *atlas, std::string name);

    public:
        /** @name Exposed APIs
         */
        ///@{
        /**
         Add a sprite renderer to the list of game objects.
         \include SampleSprite1.lua
         \ingroup API_EXPOSED
         */
        void AddSpriteDrawStatic(SpriteDrawStatic*);
        ///@}
    /// Variables
    private:
        std::vector<SpriteDrawStatic*> m_staticSprites;

    /// ScriptingInterface
    public:
        /// @private
        SCRIPTING_INTERFACE_HEADERS(Scene);
    };
};

#endif /* scene_hpp */
