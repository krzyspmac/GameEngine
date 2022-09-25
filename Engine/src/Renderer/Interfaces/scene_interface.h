//
//  scene_interface.h
//  Engine
//
//  Created by krzysp on 25/09/2022.
//

#ifndef scene_interface_h
#define scene_interface_h

#include "vector2.hpp"
#include "sprite_draw_interface.h"
#include "font_interface.h"

namespace engine
{
    class SceneI
    {
    public:
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
        virtual SpriteRepresentationI *SpriteTextLoad(FontI*) = 0;

    };
};

#endif /* scene_interface_h */
