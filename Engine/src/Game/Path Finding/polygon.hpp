//
//  polygon.hpp
//  Engine
//
//  Created by krzysp on 26/12/2021.
//

#ifndef polygon_hpp
#define polygon_hpp

#include <common.h>
#include "common_engine_impl.h"
#include <iostream>

namespace engine
{

    class Line
    {
    public:
        Line(Vector2 p1, Vector2 p2)
            : p1(p1), p2(p2)
        {
        };

        Vector2 &GetP1() { return p1; };
        Vector2 &GetP2() { return p2; };

        friend bool operator== (Line &lhs, Line &rhs)
        {
            return Vector2Equals(lhs.p1, rhs.p1) && Vector2Equals(lhs.p2, rhs.p2);
        }

    private:
        Vector2 p1;
        Vector2 p2;
    };

    class Polygon
    {
    public:
        Polygon(std::vector<Vector2> list);

        std::vector<Line> &GetLines() { return m_lines; };
        bool ContainsLine(Line&);
        std::vector<Vector2> &GetPoints() { return m_points; };
    private:
        std::vector<Vector2> m_points;
        std::vector<Line> m_lines;
    };
};

#endif /* polygon_hpp */
