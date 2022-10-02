// Copyright (c) 2022 Krzysztof Pawłowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

#include "polygon.hpp"
#include "path_finder_helper.hpp"
#include "engine.hpp"
#include "function.hpp"

#define FLOAT_MAX   32000

using namespace engine;

Polygon::Polygon(std::vector<Vector2> points)
: m_points(points)
{
    if (points.empty()) { return; }

    /// Make lines out of.
    size_t size = points.size();
    for (int i = 0; i < size; i++)
    {
        if (i+1 >= size) { break; }
        m_lines.push_back(Line(points.at(i), points.at(i+1)));
    }

    // Be sure to add the last line.
    // TODO: check if needed
    Vector2 &first = points.at(0);
    Vector2 &last = points.at(size-1);
    if (!Vector2Equals(first, last)) { m_lines.push_back(Line(last, first)); }

    // Check if we don't have to flip normals
    std::for_each(m_lines.begin(), m_lines.end(), [&](Line &l){
        Vector2 p = Vector2Add(l.GetCenter(), l.GetNormal());
        if (IsPointInside(p)) { l.InverseNormal(); };
    });
}

bool Polygon::ContainsLine(Line &someLine)
{
    for (auto it = std::begin(m_lines); it != std::end(m_lines); ++it)
    {
        if (*it == someLine) { return true; }
    }
    return false;
}

bool Polygon::IsPointVertex(Vector2 &point)
{
    return PathFinderUtils::PointListIncludesPoint(point, m_points);
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
        if (IsPointInside(checkPoint)) { return true; }
    }

    return false;
}

bool Polygon::NearestPointOutsideFrom(Vector2 &point, Vector2 *outPosition)
{
    std::cout << "Not implemented" << std::endl;
    return false;
}
