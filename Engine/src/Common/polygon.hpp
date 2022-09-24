//
//  polygon.hpp
//  Engine
//
//  Created by krzysp on 26/12/2021.
//

#ifndef polygon_hpp
#define polygon_hpp

#include "common.h"
#include "common_engine_impl.h"
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
