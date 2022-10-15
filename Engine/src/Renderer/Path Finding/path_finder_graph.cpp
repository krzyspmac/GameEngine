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

#include "path_finder_graph.hpp"
#include "path_finder_line_graph_node.hpp"
#include "path_finder_helper.hpp"
#include <iostream>
#include "polygon.hpp"

using namespace engine;

#define MAX_ITERATION 1024

PathFinderGraph::PathFinderGraph(std::vector<Polygon> polygons, std::vector<Line> lines)
: PathFinderGraphI(polygons, lines)
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
    return nullptr;
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

    // Go through polygon lines to create vertex normals
    std::for_each(m_polygons.begin(), m_polygons.end(), [&](Polygon &poly){
        std::vector<Line> lines = poly.GetLines();
        size_t countLines = lines.size();
        for (size_t i = 0; i < countLines; i++)
        {
            if (i+1 >= countLines) { continue; }

            Line &first = lines.at(i);
            Line &second = lines.at(i+1);

            Vector2 firstNormal = first.GetNormal();
            Vector2 secondNormal = second.GetNormal();
            Vector2 avg = Vector2Make((firstNormal.x + secondNormal.x)/1, (firstNormal.y + secondNormal.y)/1);
            avg = Vector2Normalized(avg);

            PathFinderLineGraphNodeI *node = GetNodeForPoint(first.GetP2());
            if (node != nullptr) { node->SetNormal(avg); };
        }

    });

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

    // Check if we have a clear line-of-sight path right at the start.
    Line targetLine(startingPoint, targetPoint);
    if (sender->PointInsidePolygons(targetPoint, NULL)) { return; }

    // If so it's a hit!
    if (!sender->IntersectsAnyline(targetLine))
    {
        std::vector<PathFinderLineGraphNodeI*> nodes;
        std::unique_ptr<PathI> path = PathFinderUtils::NodesToPath(&nodes, startingPoint, targetPoint, 3);
        sender->DidFindPath(path);
        return;
    }

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

        node->DistanceToPoint(sender, startingPoint, targetPoint, pathStack);
    }
}

bool PathFinderGraph::PointInsidePolygons(Vector2 &point, Polygon **outPolygon)
{
    for (auto it = std::begin(m_polygons); it != std::end(m_polygons); ++it)
    {
        if (it->IsPointInside(point))
        {
            if (outPolygon != nullptr) { *outPolygon = &(*it); };
            return true;
        }
    }
    return false;
}
