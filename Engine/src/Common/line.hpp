//
//  line.hpp
//  Engine
//
//  Created by krzysp on 28/12/2021.
//

#ifndef line_hpp
#define line_hpp

#include <common.h>
#include "common_engine_impl.h"
#include <iostream>

namespace engine
{

    class Line
    {
    public:
        Line(Vector2 &p1, Vector2 &p2)
            : p1(p1), p2(p2)
        {
            length = sqrt(pow(p1.x - p1.y, 2) + pow(p2.x - p2.y, 2));
        };

        Vector2 &GetP1() { return p1; };
        Vector2 &GetP2() { return p2; };
        float GetLength() { return length; };

        friend bool operator== (Line &lhs, Line &rhs)
        {
            return Vector2Equals(lhs.p1, rhs.p1) && Vector2Equals(lhs.p2, rhs.p2);
        }

        bool ConnectsToLine(Line &other)
        {
            return  Vector2Equals(p1, other.p1)
            ||      Vector2Equals(p2, other.p2)
            ||      Vector2Equals(p1, other.p2)
            ||      Vector2Equals(p2, other.p1)
            ;
        }

        bool HasVertex(Vector2 &point)
        {
            return  Vector2Equals(p1, point)
            ||      Vector2Equals(p2, point)
            ;
        }

    private:
        Vector2 p1;
        Vector2 p2;
        float length;
    };
};

#endif /* line_hpp */
