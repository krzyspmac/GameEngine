//
//  drawable_sdl.hpp
//  Engine
//
//  Created by krzysp on 15/01/2022.
//

#ifndef drawable_sdl_hpp
#define drawable_sdl_hpp

#include "common.h"
#include "drawable_interface.h"
#include "sprite_atlas_interface.h"

namespace engine
{
    /** Defines the SDL drawable that goes to the gpu. */
    class DrawableSDL: public DrawableSpriteI
    {
    public: // Drawable I
        DrawableSDL(SpriteAtlasItemI *atlasItem);
    };

    /** Defines a concrete metal class for the target drawable that is capable of
        accepting the render pass as its input.
     */
    class DrawableTargetSDL: public DrawableTargetI
    {
    public: // Drawable I
        DrawableTargetSDL(float width, float height);
    };
};

#endif /* drawable_sdl_hpp */
