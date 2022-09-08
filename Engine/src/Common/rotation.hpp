//
//  rotation.hpp
//  Engine
//
//  Created by krzysp on 08/09/2022.
//

#ifndef rotation_h
#define rotation_h

#include <stdio.h>
#include <math.h>
#include "general.hpp"
#include "common.h"
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
