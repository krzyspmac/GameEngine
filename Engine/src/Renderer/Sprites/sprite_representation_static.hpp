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

#ifndef sprite_draw_hpp
#define sprite_draw_hpp

#include "sprite_draw_interface.h"
#include "drawable_interface.h"

namespace engine
{

    class SpriteRepresentationStatic: public SpriteRepresentationI
    {
    public:
        SpriteRepresentationStatic(SpriteAtlasItemI *spriteAtlasItem);
        virtual ~SpriteRepresentationStatic() { };
        
    public: // AnimatablePropertiesI
        void SetScale(float x);
        void SetPosition(Vector2 &pos);
        Vector2& GetPosition() { return m_position; };
        Size& GetSize() { return m_sprite->GetSize(); };
        void SetZPosition(float zPos);
        SpriteAtlasItemI *GetSpriteAtlasItem() { return m_sprite; };
        void SetRotation(Rotation rotation);

    public: // SpriteRepresentationI
        void DrawAt(int x, int y);
        void Draw();

    public:

    private:
        SpriteAtlasItemI *m_sprite;
    };
};


#endif /* sprite_draw_hpp */
