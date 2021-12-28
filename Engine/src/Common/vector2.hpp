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
        return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p2.y, 2));
    }

    inline Vector2 Vector2GetDiff(Vector2 &first, Vector2 &second)
    {
        Vector2 result;
        result.x = first.x - second.x;
        result.y = first.y - second.y;
        return result;
    }
};

#endif /* vector2_hpp */
