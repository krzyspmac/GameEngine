//
//  sprite_interface_defs.h
//  RendererAppSDL
//
//  Created by krzysp on 22/12/2021.
//

#ifndef sprite_interface_defs_h
#define sprite_interface_defs_h

namespace engine
{
    typedef struct
    {
        int spriteSrcX;         // x location in asset-like texture
        int spriteSrcY;         // y location in asset-like texture
        int spriteWidth;        // single frame width
        int spriteHeight;       // single frame height
    } SpriteDescriptor;

    typedef struct
    {
        int frameCount;         // number of frames
        int frameDuration;      // in ms; 0 means animation off
    } SpriteAnimationDescriptor;
};

#endif /* sprite_interface_defs_h */
