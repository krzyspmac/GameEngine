//
//  sprite_representation_text_interface.h
//  Engine
//
//  Created by krzysp on 25/09/2022.
//

#ifndef text_sprite_representation_interface_h
#define text_sprite_representation_interface_h

#include "sprite_draw_interface.h"

namespace engine
{
    class SpriteRepresentationTextI: public SpriteRepresentationI
    {
        using SpriteRepresentationI::SpriteRepresentationI;
    public:

        /** Text */
        virtual void SetText(std::string) = 0;

        /** Shadow color. If alpha is <= 0 shadow is disabled. Default is clear color. */
        virtual void SetShadowColor(Color4) = 0;

        /** Set shadow offset. Default is { 1, 1 } */
        virtual void SetShadowOffset(OriginF) = 0;

        /** Set the line multiplier. Default is 1.f and is based on what was initially
            defined in the .fnt file */
        virtual void SetLineHeightMultiplier(float) = 0;

        /** Set the horizontal alignment. "left"|"center"|"right"
            */
        virtual void SetHorizontalAlignment(std::string) = 0;

        /** Set the vertical alignment. "top"|"middle"|"bottom"
            */
        virtual void SetVerticalAlignment(std::string) = 0;

    };
};

#endif /* text_sprite_representation_interface_h */
