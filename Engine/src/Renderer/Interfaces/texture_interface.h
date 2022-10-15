// Copyright (c) 2022 Krzysztof Pawłowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef texture_interface_h
#define texture_interface_h

#include "common.h"
#include "vector2.hpp"

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
