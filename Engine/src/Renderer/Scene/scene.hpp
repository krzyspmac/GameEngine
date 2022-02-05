//
//  scene.hpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#ifndef scene_hpp
#define scene_hpp

#include "scripting_engine_provider_interface.h"
#include "engine_provider_interface.h"
#include "sprite_draw_static.hpp"
#include "sprite_draw_animated.hpp"
#include "sprite_atlas.hpp"
#include "character_representation.hpp"
#include "common.h"
#include <iostream>

namespace engine
{
    class Scene
    {
        EngineProviderI& m_engineProvider;
        std::vector<SpriteDrawStatic*> m_staticSprites;
        std::vector<CharacterRepresentation*> m_characterRepresentations;
        CharacterRepresentation *m_mainCharacter;
        int m_mouseDownFunctionRef;
    ///
    public:

        Scene();
        ~Scene();

    /// Rederer
    public:
        /** Render the scene including only objects marked as `background`.
            @private
        */
        void RenderSceneBackground();

        /** Render the scene including only objects marked as `foreground`.
            @private
        */
        void RenderSceneForeground();

        /** Render the scene including only objects marked as `light`.
            @private
        */
        void RenderSceneLights();

        /**
         Called by the engine. Reacts to mouse clicks.
         @private
         */
        void MouseClicked(Vector2 pos);

    public:
        /**
         \brief Load a sprite renderer.

         Helper method to load the sprite and puts it into the stack.
         Uses SpriteRendererManager.
         \include SampleSpriteStatic-helper.lua
         \see Scene::AddSpriteDrawStatic.
         */
        SpriteDrawStatic *LoadSpriteStatic(SpriteAtlasI *atlas, std::string name);

        /**
         \brief Load a character representation.

         The character representation is loaded and put into cache.
         Loads the appropriate atlas and atlas items referenced by the json file.
         Uses CharacterManager, SpriteRendererManager and others.
         */
        CharacterRepresentation *LoadCharacter(std::string jsonFilename);

        /**
         \brief Main character setter.
         
         Sets the character as main. By default the character reacts to mouse clicks
         and walks the path unless specified otherwise. If `SetMainCharacter` is not
         called with a proper CharacterRepresentation the script must walk the
         character on its own. \see SetMouseDownFunction.
         */
        void SetMainCharacter(CharacterRepresentation*);

        /**
         \brief Register a sprite renderer.

         Add a sprite renderer to the list of game objects.
         \include SampleSpriteStatic-lowlevel.lua
         */
        void AddSpriteDrawStatic(SpriteDrawStatic*);

        /**
         \brief Set a mouse down function.

         Registers a `mouse down` function. Only one can exist for the scene.
         Calling this multiple times keeps the last one only.
         The function must take two parameters: x & y (float).
         \include Scene_MouseDown.lua
         */
        void SetMouseDownFunction(int mouseFunctionRef);

    public: /** Getters */

        auto& GetStaticSprites() { return m_staticSprites; };

    /// ScriptingInterface
    public:
        /// @private
        SCRIPTING_INTERFACE_HEADERS(Scene);
    };
};

#endif /* scene_hpp */
