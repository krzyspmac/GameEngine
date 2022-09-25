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
#include "sprite_representation_static.hpp"
#include "sprite_representation_animated.hpp"
#include "sprite_representation_text.hpp"
#include "sprite_atlas.hpp"
#include "character_representation.hpp"
#include "light_interface.hpp"
#include "font_interface.h"
#include "callable.hpp"
#include "scene_interface.h"
#include "common.h"
#include <iostream>

namespace engine
{
    class Scene: public SceneI
    {
        EngineProviderI& m_engineProvider;
        std::vector<SpriteRepresentationStatic*> m_staticSprites;
        std::vector<SpriteRepresentationAnimated*> m_animatedSprites;
        std::vector<SpriteRepresentationText*> m_textSprites;
        std::vector<CharacterRepresentation*> m_characterRepresentations;
        std::vector<LightI*> m_lights;
        CharacterRepresentation *m_mainCharacter;
        int m_mouseDownFunctionRef;
        unsigned int m_mouseDownIdentifier;
        CallableScriptFunctionSciptableInstance m_frameUpdateCallback;
        bool m_isActive;
    ///
    public:

        Scene();
        ~Scene();

    public: // SceneI
        void RenderSceneSprites();
        void MouseClicked(Vector2 pos);
        void SetIsActivated(bool value) { m_isActive = value; };
        bool GetIsActivated() { return m_isActive; };

    /// Rederer
    public:

    public:
        SpriteRepresentationI *SpriteStaticLoad(SpriteAtlasI *atlas, std::string name);

        SpriteRepresentationI *SpriteAnimatedLoad(float keyframeAnimationDelay, SpriteAtlasI *atlas);

        SpriteRepresentationI *SpriteTextLoad(FontI*);

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
        void SpriteStaticAdd(SpriteRepresentationStatic*);

        /**
         \brief Register a sprite renderer.
         */
        void SpriteAnimatedAdd(SpriteRepresentationAnimated*);

        /** Register a text renderer.
         */
        void SpriteTextAdd(SpriteRepresentationText *renderer);

        /**
         \brief Set a mouse down function.

         Registers a `mouse down` function. Only one can exist for the scene.
         Calling this multiple times keeps the last one only.
         The function must take two parameters: x & y (float).
         \include Scene_MouseDown.lua
         */
        void SetMouseDownFunction(int mouseFunctionRef);

        /**
         \brief Creates a light and adds it to the scene. This is a helper function
         to the the LightManager.
         */
        LightI* CreateLight(std::string type, Color3 color, float ambientIntensity, Origin position, float diffuseSize, float diffuseIntensity);

        /**
         \brief Register for a frame update. This will permamently add the observer
         for the frame udpate. The frame update funciton will be called only for
         the active scene.
         */
        void RegisterFrameUpdate(CallableScriptFunctionParametersEmpty);

    public: /** Getters */

        auto& GetStaticSprites() { return m_staticSprites; };

//    /// ScriptingInterface
//    public:
//        /// @private
//        SCRIPTING_INTERFACE_HEADERS(Scene);
    };
};

#endif /* scene_hpp */
