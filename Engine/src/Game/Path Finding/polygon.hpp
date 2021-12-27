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
#include "path_finder_line.hpp"

namespace engine
{

    class Polygon
    {
    public:
        Polygon(std::vector<Vector2> list);

        std::vector<Line> &GetLines() { return m_lines; };
        bool ContainsLine(Line&);
        std::vector<Vector2> &GetPoints() { return m_points; };
        bool IsPointVertex(Vector2&);
        bool IsPointInside(Vector2&);
        bool NearestPointOutsideFrom(Vector2 &point, Vector2 *outPoint);
    private:
        std::vector<Vector2> m_points;
        std::vector<Line> m_lines;
    };
};

#endif /* polygon_hpp */
