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

#ifndef rotation_h
#define rotation_h

#include <stdio.h>
#include <math.h>
#include "vector2.hpp"

namespace engine
{
    typedef struct Rotation
    {
        /** Angle in radians */
        float angle;

        /** Point pointing to the anchor position that is used during the rotation
            -1,1       1,1
                  0,0
            -1,-1      1,-1
        */
        Vector2 anchor;

        Rotation()
        {
            this->angle = 0.0f;
            this->anchor = Vector2Zero;
        }

        Rotation(float angle, Vector2 vec)
        {
            this->angle = angle;
            this->anchor = vec;
        }

        static Rotation empty()
        {
            static Rotation empty = Rotation();
            return empty;
        }
    } Rotation;

    inline float DEG2RAD(float angle) {
        return M_PI * angle / 180.f;
    }

    inline float RAD2DEG(float angle) {
        return angle * 180.f / M_PI;
    };
};

#endif /* rotation_h */
