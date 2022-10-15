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

#ifndef path_finder_line_graph_node_hpp
#define path_finder_line_graph_node_hpp

#include "interfaces.h"
#include "path_finder_interface.h"
namespace engine
{

    class PathFinderLineGraphNode: public PathFinderLineGraphNodeI
    {
    public:
        PathFinderLineGraphNode(Vector2 *point): PathFinderLineGraphNodeI(point) { };

    public:
        static void RPathClearUpTo(std::vector<PathFinderLineGraphNodeI*> *pathStack, PathFinderLineGraphNodeI *upToHere);
        static bool RPathContains(std::vector<PathFinderLineGraphNodeI*> *pathStack, PathFinderLineGraphNodeI *targetNode);
        static float RPathDistance(std::vector<PathFinderLineGraphNodeI*> *pathStack);

    public:
        void AddConnection(PathFinderLineGraphNodeI *node);
        std::vector<PathFinderLineGraphNodeI*>& GetConnections();
        bool HasConnectionWithPoint(Vector2 *point);
        void DistanceToPoint(PathFinderBaseI *sender, Vector2 &startingPoint, Vector2 &targetPoint, std::vector<PathFinderLineGraphNodeI*> *pathStack);
    };

};

#endif /* path_finder_line_graph_node_hpp */
