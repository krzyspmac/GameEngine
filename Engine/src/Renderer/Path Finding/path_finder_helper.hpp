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

    /// Various helpers for the path finding classes.
    class PathFinderUtils
    {
    public:
        /// Checks if the list contains a point.
        static bool PointListIncludesPoint(Vector2 &point, std::vector<Vector2> &points);

        /// Checks if the line intersects any other line previously setup.
        static std::vector<Line*> IntersectsLines(Line &myLine, std::vector<Line> &m_allLines);

        /// Checks if the line intersects any other line previously setup.
        /// Additionally checks if the line does not lie on ny vertex.
        static bool IntersectsAnyline(Line &myLine, std::vector<Vector2> &m_allPoint, std::vector<Line> &m_allLines);

        /// Check if the point is within a viewport. Uses the engine methods.
        static bool IsPointWithingViewport(Vector2 &point);

        /// Check if the lines are intercting.
        static char GetLineIntersection(float p0_x, float p0_y, float p1_x, float p1_y,
                                        float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y);

        /// Convert a list of nodes to a regular point path. Has the option to "nudge" the position
        /// away from the node verted in order to get rid of the `crossing the polygon when on a
        /// polygon line issue`.
        static std::vector<Vector2> ListOfNodesToVectors(std::vector<PathFinderLineGraphNodeI*>*, float);

        /// Convert a list of nodes to a regular Path. Takes info account the starting & ending points.
        /// Has the option to "nudge" the position
        /// away from the node verted in order to get rid of the `crossing the polygon when on a
        /// polygon line issue`.
        /// The caller may take ownership of the resulting PathI (std::move).
        static std::unique_ptr<PathI>NodesToPath(std::vector<PathFinderLineGraphNodeI*> *nodes, Vector2 startingPostion, Vector2 endingPosition, float nudgeFactor);
    };
};

#endif /* path_finder_helper_hpp */
