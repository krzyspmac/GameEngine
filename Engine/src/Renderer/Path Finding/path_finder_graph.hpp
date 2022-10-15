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

#ifndef path_finder_graph_hpp
#define path_finder_graph_hpp

#include "path_finder_interface.h"
#include "polygon.hpp"
#include <iostream>

namespace engine
{

    class PathFinderGraph: public PathFinderGraphI
    {
    public:
        PathFinderGraph(std::vector<Polygon> polygons, std::vector<Line> lines);

    private:
        PathFinderLineGraphNodeI *GetNodeForPoint(Vector2 &point);
        void Prepare();
        bool PointInsidePolygons(Vector2 &point, Polygon **outPolygon);

    public:
        void DistanceToPoint(PathFinderBaseI *sender, std::vector<Polygon> &polygons, Vector2 &startingPoint, Vector2 &targetPoint, std::vector<PathFinderLineGraphNodeI*> *pathStack);

    private:
        int m_curIteration;
    };
};

#endif /* path_finder_graph_hpp */
