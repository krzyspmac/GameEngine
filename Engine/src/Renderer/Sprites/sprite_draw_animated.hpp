//
//  sprite_draw_animated.hpp
//  RendererAppSDL
//
//  Created by krzysp on 22/12/2021.
//

#ifndef sprite_draw_animated_hpp
#define sprite_draw_animated_hpp

#include "sprite_draw_interface.h"

namespace engine
{

    class SpriteDrawAnimated: public SpriteDrawI
    {
    public:
        /// Asumming consecutive frames are laid out on the x-axis only!
        SpriteDrawAnimated(SpriteAtlasItemI *spriteAtlasItem, int frameAnimationDurationMs);

    public:
        void Draw(int x, int y);

    private:
        int m_frameCount;
        int m_frameAnimationDurationMs;
    };

};

#endif /* sprite_draw_animated_hpp */
