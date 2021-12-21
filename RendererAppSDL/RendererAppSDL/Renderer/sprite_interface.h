//
//  sprite_provider.h
//  RendererAppSDL
//
//  Created by krzysp on 21/12/2021.
//

#ifndef sprite_provider_h
#define sprite_provider_h

#include "texture_interface.h"

namespace engine
{
    typedef struct
    {
        int spriteWidth;        // single frame width
        int spriteHeight;       // single frame height
        int frameCount;         // number of frames
        int frameDuration;      // in ms
    } SpriteDescriptor;

    class SpriteI
    {
    public:
        /// Default constructor. Does not take the ownership
        /// of the texture. SpriteDescriptor refer to
        /// a single sprite animation.
        SpriteI(TextureI *texture, SpriteDescriptor spriteDescriptor)
            : m_texture(texture), m_spriteDescriptor(spriteDescriptor)
        { };

        ///
        TextureI *GetTexture() { return m_texture; };

        /// Draw the sprite.
        virtual void Draw(int x, int y, int frameNumber = 0) = 0;

        /// Draw the sprite animated.
        virtual void DrawAnimated(int x, int y) = 0;

    protected:
        TextureI *m_texture;
        SpriteDescriptor m_spriteDescriptor;
    };

}; // namespace engine

#endif /* sprite_provider_h */
