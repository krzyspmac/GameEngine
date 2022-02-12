//
//  sprite_backbuffer.hpp
//  Engine
//
//  Created by krzysp on 16/01/2022.
//

#ifndef sprite_backbuffer_hpp
#define sprite_backbuffer_hpp

#include "sprite_draw_interface.h"
#include "drawable_interface.h"

namespace engine
{
    /** Declares a sprite that is used to render the current pass off-stage.
        It has a texture that is of the same size and can be set to accept
        the current rendering pass. Such a texture can then be rendered in one go.
     */
    class SpriteDrawBackbuffer: public SpriteRepresetationI
    {
        TextureTargetI *m_targetTexture;
    public:
        SpriteDrawBackbuffer(float width, float height);

        TextureTargetI *GetTargetTexture();
    };
};

#endif /* sprite_backbuffer_hpp */
