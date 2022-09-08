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

namespace engine {

    typedef struct Rotation {

        float angle;
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

};

#endif /* rotation_h */
