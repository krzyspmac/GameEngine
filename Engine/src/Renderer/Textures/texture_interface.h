//
//  texture_interface.h
//  RendererAppSDL
//
//  Created by krzysp on 20/12/2021.
//

#ifndef texture_interface_h
#define texture_interface_h

#include "common.h"

namespace engine
{

    class TextureI
    {
    public:
        TextureI(void *textureHandle, std::string textureName)
        : m_textureHandle(textureHandle), m_textureName(textureName)
        { }

        void *getTextureHandle() { return m_textureHandle; };
        std::string &getTextureName() { return m_textureName; };

    protected:
        void *m_textureHandle;
        std::string m_textureName;
    };

    class TextureTargetI: public TextureI
    {
    public:
        TextureTargetI(void *textureHandle)
        : TextureI(textureHandle, "")
        { };
    };
};

#endif /* texture_interface_h */
