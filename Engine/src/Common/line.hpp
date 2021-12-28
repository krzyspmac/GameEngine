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
            length = Vector2Distance(p1, p2);
            centerPoint = Vector2Make((p2.x+p1.x)/2, (p2.y+p1.y)/2);
            lineVector = Vector2FromLine(p1, p2);

            normalVector = Vector2PerpendicularClockwise(lineVector);
            normalVector = Vector2Normalized(normalVector);
        };

        Vector2 &GetP1() { return p1; };
        Vector2 &GetP2() { return p2; };
        Vector2 &GetCenter() { return centerPoint; };
        Vector2 &GetNormal() { return normalVector; };

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

        Line MakeNormalLine(float vectorScale)
        {
            Vector2 normal = Vector2Scaled(GetNormal(), vectorScale);
            Vector2 &lineCenter = GetCenter();
            Vector2 lineCenterExtended = Vector2Make(lineCenter.x + normal.x, lineCenter.y + normal.y);
            return Line(lineCenter, lineCenterExtended);
        }

    private:
        Vector2 p1;
        Vector2 p2;
        Vector2 centerPoint;
        Vector2 lineVector;
        float length;
        Vector2 normalVector; // from the middle of the line
    };
};

#endif /* line_hpp */
