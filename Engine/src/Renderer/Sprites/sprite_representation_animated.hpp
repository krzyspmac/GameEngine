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

#ifndef sprite_draw_animated_hpp
#define sprite_draw_animated_hpp

#include "sprite_draw_interface.h"
#include "sprite_atlas_interface.h"
#include "sprite_representation_static.hpp"

namespace engine
{
    class SpriteRepresentationAnimated: public SpriteRepresentationI
    {
    public:

        SpriteRepresentationAnimated(std::vector<SpriteAtlasItemI*> sprites, int frameAnimationDurationMs);
        virtual ~SpriteRepresentationAnimated();
        
        static SpriteRepresentationAnimated *CreateFromAtlas(std::vector<std::unique_ptr<SpriteAtlasItemI>>& sprites, int frameAnimationDurationMs);

    public:

        /** Sets the scale.
         */
        void SetScale(float x);

        /** Sets the position for the sprite.
         */
        void SetPosition(Vector2 &pos);

        /** Gets the current position for the sprite.
         */
        Vector2& GetPosition() { return m_position; };

        /** Set the rotation and pass it to the drawable */
        void SetRotation(Rotation rotation);

        /** Set Alpha */
        void SetAlpha(float val);


        /** Set the z-axis position.
            Possible values range from 0.0 to 1.0, 0.0 being closest to the "camera" and
            1.0 being further away. Of two object: one being at 1.0 and one being at 0.0
            the one at 0.0 will overlap the one at 1.0.
            */
        void SetZPosition(float zPos);

        /** Sets animation frame duration in ms */
        void SetAnimationFrameDuration(float);

        void Update() {

        }

    public: /** Overrides */

        void SetAcceptsLight(bool val);
        void DrawAt(int x, int y);
        void Draw();
        void SetColorMod(Color4);
        
    private:
        void PrepareAnimation();
        
    private:
        int m_frameAnimationDurationMs;
        std::vector<SpriteRepresentationStatic*> m_sprites;
        int m_maxWidth;
        int m_maxHeight;
    };

};

#endif /* sprite_draw_animated_hpp */
