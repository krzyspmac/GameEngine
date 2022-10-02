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

#ifndef polygon_hpp
#define polygon_hpp

#include <common.h>
#include "interfaces.h"
#include <iostream>

namespace engine
{
    /// Holds a list of points, by default connected to each other.
    /// Check if the polygon is closed, if not - closes it.
    /// Using line's normals and checks if they have to be flipped
    /// or not.
    class Polygon
    {
    public:
        Polygon(std::vector<Vector2> list);

    public:
        std::vector<Line> &GetLines() { return m_lines; };
        bool ContainsLine(Line&);
        std::vector<Vector2> &GetPoints() { return m_points; };
        bool IsPointVertex(Vector2&);
        bool IsPointInside(Vector2&);
        bool DoesLineIntersect(Line&);
        bool NearestPointOutsideFrom(Vector2 &point, Vector2 *outPoint);

    private:
        std::vector<Vector2> m_points;
        std::vector<Line> m_lines;
    };
};

#endif /* polygon_hpp */
