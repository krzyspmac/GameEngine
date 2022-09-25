//
//  path_finder_line_graph_node.hpp
//  Engine
//
//  Created by krzysp on 27/12/2021.
//

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
