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
        return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
    }

    inline Vector2 Vector2Add(Vector2 &p1, Vector2 &p2)
    {
        return Vector2Make(p1.x + p2.x, p1.y + p2.y);
    }

    inline Vector2 Vector2GetDiff(Vector2 &first, Vector2 &second)
    {
        Vector2 result;
        result.x = first.x - second.x;
        result.y = first.y - second.y;
        return result;
    }

    inline Vector2 Vector2PerpendicularClockwise(Vector2& p)
    {
        return Vector2Make(p.y, -p.x);
    }

    inline Vector2 Vector2PerpendicularCounterClockwise(Vector2& p)
    {
        return Vector2Make(-p.y, p.x);
    }

    inline Vector2 Vector2FromLine(Vector2& p1, Vector2& p2)
    {
        return Vector2Make(p1.x-p2.x, p1.y-p2.y);
    }

    inline Vector2 Vector2Normalized(Vector2& value)
    {
        Vector2 v = Vector2Make(value.x, value.y);

        float length = sqrt(v.x * v.x + v.y * v.y);

        // normalize vector
        v.x /= length;
        v.y /= length;

        return v;
    }

    inline Vector2 Vector2Scaled(Vector2 value, float scale)
    {
        Vector2 v = Vector2Make(value.x, value.y);
        v.x *= scale;
        v.y *= scale;
        return v;
    }
};

#endif /* vector2_hpp */
