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
#include "general.hpp"
#include "common.h"

namespace engine
{
    typedef struct Vector1
    {
        float value;

        Vector1()
        {
            this->value = 0.0f;
        }

        Vector1(float value)
        {
            this->value = value;
        }

        Vector1(Vector1 *other)
        {
            this->value = other->value;
        }
    } Vector1;

    typedef struct Vector2
    {
        float x;
        float y;

        Vector2()
        {
            this->x = 0;
            this->y = 0;
        };

        Vector2(float x, float y)
        {
            this->x = x;
            this->y = y;
        };

        Vector2(Vector2 *other)
        {
            this->x = other->x;
            this->y = other->y;
        };

        static Vector2 shared()
        {
            return Vector2();
        };

        double length()
        {
            return sqrt((this->x * this->x) + (this->y * this->y));
        };

        double length_squqred()
        {
            return ((this->x * this->x) + (this->y * this->y));
        };

        bool is_unit()
        {
            return length_squqred() == 1.0;
        }

        void normalize()
        {
            double len = this->length();

            if (len != 0.0 && len != 1.0)
            {
                this->x /= len;
                this->y /= len;
            }
        }

        Vector2 normalized()
        {
            Vector2 copy = Vector2(this);
            copy.normalize();
            return copy;
        }

        void inverse()
        {
            this->x = -this->x;
            this->y = -this->y;
        }

        Vector2 inversed()
        {
            Vector2 copy = Vector2(this);
            copy.inverse();
            return copy;
        }

        Vector2 operator * (double value)
        {
            return Vector2(this->x * value, this->y * value);
        };

        Vector2 operator + (Vector2 const &rhs)
        {
            return Vector2(this->x + rhs.x, this->y + rhs.y);
        };

        Vector2 operator += (Vector2 const &rhs)
        {
            return Vector2(this->x + rhs.x, this->y + rhs.y);
        };

        Vector2 operator *= (double value)
        {
            return Vector2(this->x * value, this->y * value);
        }

        bool operator == (Vector2 const &rhs)
        {
            return this->x == rhs.x && this->y == rhs.y;
        };

    } Vector2;

    const Vector2 Vector2Zero = {0, 0};

    inline Vector2 Vector2Make(float x, float y)
    {
        Vector2 result;
        result.x = x;
        result.y = y;
        return result;;
    };

    /** {2,2} */
    inline Vector2 VectorMake(std::string def)
    {
        static std::string delimiter = ",";
        if (size_t delimPos = def.find(delimiter))
        {
            std::string xStr = def.substr(0, delimPos);
            trim(xStr);
            float x = xStr.size() > 0 ? std::stof(xStr) : 0;

            std::string yStr = def.substr(delimPos+1, def.size() - delimPos);
            trim(yStr);
            float y = yStr.size() > 0 ? std::stof(yStr) : 0;

            return Vector2Make(x, y);
        }
        else
        {
            return Vector2Zero;
        }
    }

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

    inline float Vector2Distance2(Vector2 v, Vector2 w)
    {
        return sqr(v.x - w.x) + sqr(v.y - w.y);
    }

    inline float Vector2Distance2Squared(Vector2 p, Vector2 v, Vector2 w)
    {
        float l2 = Vector2Distance2(v, w);
        if (l2 == 0) { return Vector2Distance2(p, v); }

        float t = ((p.x - v.x) * (w.x - v.x) + (p.y - v.y) * (w.y - v.y)) / l2;
        t = MAX(0, MIN(1, t));

        return Vector2Distance2(p, Vector2Make(v.x + t * (w.x - v.x), v.y + t * (w.y - v.y)));
    }
};

#endif /* vector2_hpp */
