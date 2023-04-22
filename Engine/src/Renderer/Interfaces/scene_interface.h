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

#ifndef scene_interface_h
#define scene_interface_h

#include "vector2.hpp"
#include "sprite_draw_interface.h"
#include "font_interface.h"
#include "sprite_representation_text_interface.h"
#include "light_interface.hpp"

namespace engine
{
    class SceneI
    {
    public:
        SceneI() { };
        virtual ~SceneI() { };

        /** Render the scene sprites. If set this will also call the update function
            before any rendering occurs.
            @private
        */
        virtual void RenderSceneSprites() = 0;

        /**
         Called by the engine. Reacts to mouse clicks.
         @private
         */
        virtual void MouseClicked(Vector2 pos) = 0;

        virtual void SetIsActivated(bool) = 0;

        virtual bool GetIsActivated() = 0;

        /** \brief Load a sprite renderer.
         */
        virtual SpriteRepresentationI *SpriteStaticLoad(SpriteAtlasI *atlas, std::string name) = 0;

        /** \brief Load a sprite renderer for animation
         */
        virtual SpriteRepresentationI *SpriteAnimatedLoad(float keyframeAnimationDelay, SpriteAtlasI *atlas) = 0;

        /** \brief Load a drawable text representation
         */
        virtual SpriteRepresentationTextI *SpriteTextLoad(FontI*) = 0;

        /**
         \brief Creates a light and adds it to the scene. This is a helper function
         to the the LightManager.
         */
        virtual LightI* CreateLight(std::string type, Color3 color, float ambientIntensity, Origin position, float diffuseSize, float diffuseIntensity) = 0;

        /** \brief Set the function to receive frame updates.
         */
        virtual void SetFrameUpdate(std::function<void(void)>) = 0;

        /** \brief Remove the frame updates
         */
        virtual void RemoveFrameUpdates() = 0;
    };
};

#endif /* scene_interface_h */
