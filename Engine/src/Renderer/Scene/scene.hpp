// Copyright (c) 2022 Krzysztof Pawłowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef scene_hpp
#define scene_hpp

#include "engine_provider_interface.h"
#include "sprite_representation_static.hpp"
#include "sprite_representation_animated.hpp"
#include "sprite_representation_text.hpp"
#include "sprite_atlas.hpp"
#include "character_representation.hpp"
#include "light_interface.hpp"
#include "font_interface.h"
#include "scene_interface.h"
#include "sprite_representation_text_interface.h"
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
        std::function<void(void)> m_frameUpdateCallback;
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

        SpriteRepresentationTextI *SpriteTextLoad(FontI*);

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

        void SetFrameUpdate(std::function<void(void)>);
        void RemoveFrameUpdates();

    public: /** Getters */

        auto& GetStaticSprites() { return m_staticSprites; };
    };
};

#endif /* scene_hpp */
