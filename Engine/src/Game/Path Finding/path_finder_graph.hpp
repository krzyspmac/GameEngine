//
//  path_finder_graph.hpp
//  Engine
//
//  Created by krzysp on 27/12/2021.
//

#ifndef path_finder_graph_hpp
#define path_finder_graph_hpp

#include "path_finder_interface.h"
#include <iostream>

namespace engine
{

    class PathFinderGraph: public PathFinderGraphI
    {
    public:
        PathFinderGraph(std::vector<Line> lines);

    private:
        PathFinderLineGraphNodeI *GetNodeForPoint(Vector2 &point);
        void Prepare();

    public:
        void DistanceToPoint(PathFinderBaseI *sender, Vector2 &startingPoint, Vector2 &targetPoint, std::vector<PathFinderLineGraphNodeI*> *pathStack);
    };
};

#endif /* path_finder_graph_hpp */
