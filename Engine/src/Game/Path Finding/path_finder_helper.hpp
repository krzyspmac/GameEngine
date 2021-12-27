//
//  path_finder_helper.hpp
//  Engine
//
//  Created by krzysp on 27/12/2021.
//

#ifndef path_finder_helper_hpp
#define path_finder_helper_hpp

#include "path_finder_interface.h"
#include "common_engine_impl.h"

namespace engine
{

    class PathFinderUtils
    {
    public:
        static bool IsIntersecting(Vector2 a, Vector2 b, Vector2 c, Vector2 d);
        static bool IsVertexPoint(Vector2 &point, std::vector<Vector2> &points);
        static bool IntersectsAnyline(Line &myLine, std::vector<Vector2> &m_allPoint, std::vector<Line> &m_allLines);
        static bool IsPointWithingViewport(Vector2 &point);
        static char get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y,
                                          float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y);
        static std::vector<Vector2> ListOfNodesToVectors(std::vector<PathFinderLineGraphNodeI*>*);
    };
};

#endif /* path_finder_helper_hpp */
