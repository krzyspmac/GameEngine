//
//  path_finder_graph.cpp
//  Engine
//
//  Created by krzysp on 27/12/2021.
//

#include "path_finder_graph.hpp"
#include "path_finder_line_graph_node.hpp"
#include "path_finder_helper.hpp"

using namespace engine;

#define MAX_ITERATION 1024

PathFinderGraph::PathFinderGraph(std::vector<Line> lines)
: PathFinderGraphI(lines)
{
    Prepare();
}

PathFinderLineGraphNodeI *PathFinderGraph::GetNodeForPoint(Vector2 &point)
{
    for (auto it = std::begin(m_nodes); it != std::end(m_nodes); ++it)
    {
        PathFinderLineGraphNodeI *node = it->get();
        Vector2 *nodePoint = node->GetPoint();
        if (Vector2Equals(point, *nodePoint))
        {
            return node;
        }

    }
    return NULL;
}

void PathFinderGraph::Prepare()
{
    // Store a list of graph nodes. The number of nodes is equal to the cout of vertices in each line.
    for (auto it = std::begin(m_connectingLines); it != std::end(m_connectingLines); ++it)
    {
        Line *line = &(*it);
        Vector2 &p1 = line->GetP1();
        Vector2 &p2 = line->GetP2();

        PathFinderLineGraphNodeI *nodeP1 = GetNodeForPoint(p1);
        if (!nodeP1)
        {
            nodeP1 = new PathFinderLineGraphNode(&(p1));
            m_nodes.emplace_back(std::move(nodeP1));
        }

        PathFinderLineGraphNodeI *nodeP2 = GetNodeForPoint(p2);
        if (!nodeP2)
        {
            nodeP2 = new PathFinderLineGraphNode(&(p2));
            m_nodes.emplace_back(std::move(nodeP2));
        }
    }

    // Go through each point node and check if it connects, via line,
    // to any other node.
    for (auto it = std::begin(m_nodes); it != std::end(m_nodes); ++it)
    {
        PathFinderLineGraphNodeI *node = it->get();
        Vector2 *nodePoint = node->GetPoint();

        for (auto pit = std::begin(m_nodes); pit != std::end(m_nodes); ++pit)
        {
            PathFinderLineGraphNodeI *otherNode = pit->get();
            Vector2 *otherNodePoint = otherNode->GetPoint();

            if (node == otherNode)
            {
                // skip the same items
                continue;
            }

            for (auto lit = std::begin(m_connectingLines); lit != std::end(m_connectingLines); ++lit)
            {
                Line &line = *lit;
                if (line.HasVertex(*nodePoint) && line.HasVertex(*otherNodePoint))
                {
                    if (!node->HasConnectionWithPoint(otherNodePoint))
                    {
                        node->AddConnection(otherNode);
                    }
                }
            }
        }
    }
};

void PathFinderGraph::DistanceToPoint(PathFinderBaseI *sender, std::vector<Polygon> &polygons, Vector2 &startingPoint, Vector2 &targetPoint, std::vector<PathFinderLineGraphNodeI*> *pathStack)
{
    m_curIteration = 0;

    // Get a list of all line-of-sight points that the starting point sees and make that
    // out starting point list.

    std::vector<PathFinderLineGraphNodeI*> visibleNodes;

    for (auto it = std::begin(m_nodes); it != std::end(m_nodes); ++it)
    {
        PathFinderLineGraphNodeI *node = it->get();
        Line line(startingPoint, *node->GetPoint());

        bool intersectsAnyLine = PathFinderUtils::IntersectsAnyline(line, sender->GetAllPoint(), sender->GetAllLines());
        bool intesectsPolygon = false;

        std::for_each(polygons.begin(), polygons.end(), [&](Polygon &poly){
            if (intesectsPolygon) { return; };

            if (poly.DoesLineIntersect(line))
            {
                intesectsPolygon = true;
            }
        });

//        if (intesectsPolygon)
//        {
//            printf("intersects!");
//        }

        if (!intersectsAnyLine && !intesectsPolygon)
        {
            visibleNodes.emplace_back(node);
        }
    }

    for (auto it = std::begin(visibleNodes); it != std::end(visibleNodes); ++it)
    {
        pathStack->clear();

        if (++m_curIteration >= MAX_ITERATION)
        {
            return;
        }

        PathFinderLineGraphNodeI *node = *it;
        Vector2 &point = *node->GetPoint();

        if (!PathFinderUtils::IsPointWithingViewport(point))
        {
            continue;
        }

        // Check if we can see the first node
        Line lineToFirstNode(startingPoint, point);

        if (PathFinderUtils::IntersectsAnyline(lineToFirstNode, sender->GetAllPoint(), sender->GetAllLines()))
        {
            continue;
        }

        sender->DidStart(lineToFirstNode.GetLength());

        node->DistanceToPoint(sender, targetPoint, pathStack);
    }
}
