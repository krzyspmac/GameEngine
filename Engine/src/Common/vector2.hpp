//
//  vector2.hpp
//  Engine
//
//  Created by krzysp on 28/12/2021.
//

#ifndef vector2_hpp
#define vector2_hpp

#include <stdio.h>
#include <math.h>

namespace engine
{

    typedef struct Vector2
    {
        float x;
        float y;
    } Vector2;

    const Vector2 Vector2Zero = {0, 0};

    inline Vector2 Vector2Make(float x, float y)
    {
        Vector2 result;
        result.x = x;
        result.y = y;
        return result;;
    };

    inline bool Vector2Equals(Vector2 &first, Vector2 &second)
    {
        return first.x == second.x && first.y == second.y;
    };

    inline float Vector2Distance(Vector2 &p1, Vector2 &p2)
    {
        return sqrt(pow(p1.x - p1.y, 2) + pow(p2.x - p2.y, 2));
    }

};

#endif /* vector2_hpp */
