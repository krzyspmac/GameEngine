//
//  sprite_provider.h
//  RendererAppSDL
//
//  Created by krzysp on 21/12/2021.
//

#ifndef sprite_provider_h
#define sprite_provider_h

#include "texture_interface.h"
#include "sprite_interface_defs.h"
#include "sprite_atlas_interface.h"

namespace engine
{
    class SpriteI
    {
    public:
        /// Default constructor. Does not take the ownership
        /// of the texture. SpriteDescriptor refer to
        /// the sprite location within the texture.
        /// be layed out on the X-axis.
        SpriteI(TextureI *texture, SpriteDescriptor spriteDescriptor)
            : m_texture(texture), m_spriteDescriptor(spriteDescriptor)
        { };

        /// Go-to initializer for a sprite taken from the sprite-atlas.
        SpriteI(SpriteAtlasItemI *spriteAtlasItem, SpriteAnimationDescriptor animationDescriptor)
            : m_texture(NULL), m_spriteDescriptor(SpriteDescriptor())
        { };

        ///
        TextureI *GetTexture() { return m_texture; };

        ///
        SpriteDescriptor &GetDescriptor() { return m_spriteDescriptor; };

    protected:
        TextureI *m_texture;
        SpriteDescriptor m_spriteDescriptor;
    };

}; // namespace engine

#endif /* sprite_provider_h */
