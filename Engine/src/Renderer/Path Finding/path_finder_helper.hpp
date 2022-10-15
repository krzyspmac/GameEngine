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

#ifndef path_finder_helper_hpp
#define path_finder_helper_hpp

#include "path_finder_interface.h"
#include "interfaces.h"

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
