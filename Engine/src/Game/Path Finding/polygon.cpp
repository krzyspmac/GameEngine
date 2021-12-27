//
//  polygon.cpp
//  Engine
//
//  Created by krzysp on 26/12/2021.
//

#include "polygon.hpp"

using namespace engine;

Polygon::Polygon(std::vector<Vector2> points)
: m_points(points)
{
    size_t size = points.size();
    if (size < 1)
    {
        return;
    }

    for (int i = 0; i < size; i++)
    {
        if (i+1 >= size)
        {
            break;
        }

        Vector2 &p1 = points.at(i);
        Vector2 &p2 = points.at(i+1);
        m_lines.push_back(Line(p1, p2));
    }

    Vector2 &first = points.at(0);
    Vector2 &last = points.at(size-1);
    if (!Vector2Equals(first, last))
    {
        m_lines.push_back(Line(last, first));
    }
}

bool Polygon::ContainsLine(Line &someLine)
{
    for (auto it = std::begin(m_lines); it != std::end(m_lines); ++it)
    {
        Line &line = *it;
        if (line == someLine)
        {
            return true;
        }
    }
    return false;
}
