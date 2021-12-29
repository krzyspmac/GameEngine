//
//  polygon.cpp
//  Engine
//
//  Created by krzysp on 26/12/2021.
//

#include "polygon.hpp"
#include "path_finder_helper.hpp"
#include "engine.hpp"
#include "function.hpp"

#define FLOAT_MAX   32000

using namespace engine;

class Vector2Sorter {
    Vector2 startPosition;
public:
    Vector2Sorter(Vector2 value) : startPosition(value) { }

    bool operator()(Vector2 &lhs, Vector2 &rhs)
    {
        return Vector2Distance(startPosition, lhs) < 0 < Vector2Distance(startPosition, rhs);
//        return false;//SortFunction(o1, o2, type_ );
    }
};

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

    size_t countLines = m_lines.size();
    for (size_t i = 0; i < countLines; i++)
    {
        if (i+1 >= countLines) { continue; }

        Line &first = m_lines.at(i);
        Line &second = m_lines.at(i+1);

        Vector2 firstNormal = first.GetNormal();
        Vector2 secondNormal = second.GetNormal();
        Vector2 avg = Vector2Make((firstNormal.x + secondNormal.x)/2, (firstNormal.y + secondNormal.y)/2);
        avg = Vector2Normalized(avg);
        first.SetP2OutsideVector(avg);
        second.SetP1OutsideVector(avg);
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

bool Polygon::IsPointVertex(Vector2 &point)
{
    return PathFinderUtils::IsVertexPoint(point, m_points);
}

bool Polygon::IsPointInside(Vector2 &point)
{
    Vector2 rightPoint = Vector2Make(FLOAT_MAX, point.y);
    Line    rightLine(point, rightPoint);

    std::vector<Line*> touchedLines = PathFinderUtils::IntersectsLines(rightLine, m_lines);



    return touchedLines.size() % 2 != 0;
}

bool Polygon::DoesLineIntersect(Line &line)
{
    Vector2 &p1 = line.GetP1();
    Vector2 &p2 = line.GetP2();
    float minX = MIN(p1.x, p2.x);
    float maxX = MAX(p1.x, p2.x);
    Function f(p1, p2);

    for (float x = minX; x <= maxX; x++)
    {
        float y = f.f(x);
        Vector2 checkPoint = Vector2Make(x, y);
        if (IsPointInside(checkPoint))
        {
            return true;
        }
    }

    return false;
}

bool Polygon::NearestPointOutsideFrom(Vector2 &point, Vector2 *outPosition)
{
    // Brute force for the moment
    Size &viewportSize = GetMainEngine()->GetViewport();
    Vector2 temp;
    std::vector<Vector2> positions;
//    Vector2 down

    temp = Vector2Make(point.x, point.y);
    while (temp.y < viewportSize.height)
    {
        temp.y += 1;
        if (!IsPointInside(temp))
        {
            positions.push_back(temp);
            break;
        }
    }
//
//    temp = Vector2Make(point.x, point.y);
//    while (temp.y >= 0)
//    {
//        temp.y -= 1;
//        if (!IsPointInside(temp))
//        {
//            positions.push_back(temp);
//            break;
//        }
//    }
//
//    temp = Vector2Make(point.x, point.y);
//    while (temp.x >= 0)
//    {
//        temp.x -= 1;
//        if (!IsPointInside(temp))
//        {
//            positions.push_back(temp);
//            break;
//        }
//    }
//
//    temp = Vector2Make(point.x, point.y);
//    while (temp.x <= viewportSize.width)
//    {
//        temp.x += 1;
//        if (!IsPointInside(temp))
//        {
//            positions.push_back(temp);
//            break;
//        }
//    }

    std::sort(positions.begin(), positions.end(), Vector2Sorter(point) );
    if (positions.size() > 0)
    {
        if (outPosition)
        {
            *outPosition = positions.at(0);
        }
        return true;
    }
    else
    {
        return false;
    }
}
