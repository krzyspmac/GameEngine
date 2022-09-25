//
//  texture_interface.h
//  RendererAppSDL
//
//  Created by krzysp on 20/12/2021.
//

#ifndef texture_interface_h
#define texture_interface_h

#include "common.h"
#include "interfaces.h"

namespace engine
{

    /** Defines an abstract interface for the texture. Differnet back-end provide different concrete instances.
        */
    class TextureI
    {
        Vector2 m_textureSize;
    public:
        TextureI(void *textureHandle, std::string textureName, Vector2 size)
            : m_textureHandle(textureHandle), m_textureName(textureName), m_textureSize(size)
        { }

        void *getTextureHandle() { return m_textureHandle; };
        std::string &getTextureName() { return m_textureName; };
        void SetSize(Vector2 size) { m_textureSize = size; };
        Vector2& GetSize() { return m_textureSize; };

    protected:
        void *m_textureHandle;
        std::string m_textureName;
    };

    /** Defines an abstract interface for the target texture that gets the current rendering queue's rendering pass.
     */
    class TextureTargetI: public TextureI
    {
    public:
        TextureTargetI(void *textureHandle, Vector2 size)
            : TextureI(textureHandle, "", size)
        { };
    };
};

#endif /* texture_interface_h */
