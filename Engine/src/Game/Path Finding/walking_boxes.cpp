//
//  walking_boxes.cpp
//  Engine
//
//  Created by krzysp on 26/12/2021.
//

#include "walking_boxes.hpp"
#include "engine_provider_interface.h"
#include "engine_interface.h"
#include "path_finder_line_graph_node.hpp"
#include <iostream>
#include <limits>

using namespace engine;

static int max_iteration = 1024;
static int cur_iteration = 0;
/*
class LineGraph
{
public:
    LineGraph(std::vector<Line> lines): m_connectingLines(lines)
    {
        Prepare();
    };

public:

    PathFinderLineGraphNodeI *GetNodeForPoint(Vector2 &point)
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

    void Prepare()
    {
        // Store a list of graph nodes. The number of nodes is equal to the number of lines.
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

    float DistanceToPoint(WalkingBoxes *sender, Vector2 &startingPoint, Vector2 &targetPoint, float startingDistance, std::vector<PathFinderLineGraphNodeI*> *pathStack)
    {
        pathStack->clear();
        cur_iteration = 0;

        for (auto it = std::begin(m_nodes); it != std::end(m_nodes); ++it)
        {
            if (++cur_iteration >= max_iteration) {
                return false;
            }

            PathFinderLineGraphNodeI *node = it->get();
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
        return 0;
    }

    std::vector<std::unique_ptr<PathFinderLineGraphNodeI>>& GetNodes() { return m_nodes; };

public:
    std::vector<Line> m_connectingLines;
    std::vector<std::unique_ptr<PathFinderLineGraphNodeI>> m_nodes;

    std::vector<PathFinderLineGraphNodeI*> m_path;
};

*/

std::vector<PathFinderLineGraphNodeI*> pathStack;

WalkingBoxes::WalkingBoxes(std::vector<Polygon> polygonList)
: m_polygons(polygonList)
{
    EngineProviderI &provider = GetMainEngine()->getProvider();

    Uint64 start = provider.GetTicks();
    Prepare();
    Uint64 end = provider.GetTicks();
    Uint64 delta = end - start;
    printf("Prepare took %d ms", delta);
}

void WalkingBoxes::Prepare()
{
    // Join all points into one array
    for (auto it = std::begin(m_polygons); it != std::end(m_polygons); ++it)
    {
        Polygon &polygon = *it;
        std::vector<Vector2> points = polygon.GetPoints();

        for (auto pit = std::begin(points); pit != std::end(points); ++pit)
        {
            m_allPoint.push_back(*pit);
        }
    }

    // Join all lines into one array
    //std::vector<Line> allLines;
    for (auto it = std::begin(m_polygons); it != std::end(m_polygons); ++it)
    {
        Polygon &polygon = *it;
        std::vector<Line> lines = polygon.GetLines();

        for (auto pit = std::begin(lines); pit != std::end(lines); ++pit)
        {
            m_allLines.push_back(*pit);
        }
    }



    // At the end add all the polygon lines as those are parts of the
    // grid as well.
    for (auto cPoint = std::begin(m_polygons); cPoint != std::end(m_polygons); ++cPoint)
    {
        Polygon &polygon = *cPoint;
        std::vector<Line> &polygonLines = polygon.GetLines();

        for (auto pit = std::begin(polygonLines); pit != std::end(polygonLines); ++pit)
        {
            m_connectionLines.push_back(*pit);
        }
    }

    // Make a line connection from each point in each polygon
    // to each other point in every other polygon.
    size_t polyCount = m_polygons.size();
    for (int i = 0; i < polyCount; i++)
    {
        if (i+1 >= polyCount)
        {
            break;;
        }

        Polygon &polygon = m_polygons.at(i);
        Polygon &nextPolygon = m_polygons.at(i+1);

        std::vector<Vector2> &polygonPoints = polygon.GetPoints();
        std::vector<Vector2> &otherPolygonPoints = nextPolygon.GetPoints();

        for (auto cPoint = std::begin(polygonPoints); cPoint != std::end(polygonPoints); ++cPoint)
        {
            for (auto tPoint = std::begin(otherPolygonPoints); tPoint != std::end(otherPolygonPoints); ++tPoint)
            {
                Vector2 &p0 = *cPoint;
                Vector2 &p1 = *tPoint;

                bool intersects = false;

                for (auto lit = std::begin(m_allLines); lit != std::end(m_allLines); ++lit)
                {
                    Line &line = *lit;
                    Vector2 &p2 = line.GetP1();
                    Vector2 &p3 = line.GetP2();

                    float i_x;
                    float i_y;

                    if (PathFinderUtils::get_line_intersection(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, &i_x, &i_y))
                    {
                        Vector2 intersectionPoint;
                        intersectionPoint.x = i_x;
                        intersectionPoint.y = i_y;

                        if (!PathFinderUtils::IsVertexPoint(intersectionPoint, m_allPoint))
                        {
                            intersects = true;
                            break;
                        }
                    }
                }

                if (!intersects)
                {
                    m_connectionLines.push_back(Line(p0, p1));
                }
            }
        }
    }

    m_lineGraph = new PathFinderGraph(m_connectionLines);
}

bool WalkingBoxes::IntersectsAnyline(Line &myLine)
{
    Vector2 &p0 = myLine.GetP1();
    Vector2 &p1 = myLine.GetP2();

    bool intersects = false;

    for (auto lit = std::begin(m_allLines); lit != std::end(m_allLines); ++lit)
    {
        Line &line = *lit;
        Vector2 &p2 = line.GetP1();
        Vector2 &p3 = line.GetP2();

        float i_x;
        float i_y;

        if (PathFinderUtils::get_line_intersection(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, &i_x, &i_y))
        {
            Vector2 intersectionPoint;
            intersectionPoint.x = i_x;
            intersectionPoint.y = i_y;

            if (!PathFinderUtils::IsVertexPoint(intersectionPoint, m_allPoint))
            {
                intersects = true;
                break;
            }
        }
    }

    return intersects;
}

void WalkingBoxes::Draw()
{
    EngineProviderI &provider = GetMainEngine()->getProvider();

    /// redner lines
    for (auto lit = std::begin(m_connectionLines); lit != std::end(m_connectionLines); ++lit)
    {
        provider.RenderSetColor(255, 0, 0, 100);
        DrawLine(*lit);
    }

    /// render polygons
    for (auto it = std::begin(m_polygons); it != std::end(m_polygons); ++it)
    {
        Polygon &polygon = *it;
        std::vector<Line> &lines = polygon.GetLines();

        for (auto lit = std::begin(lines); lit != std::end(lines); ++lit)
        {
            provider.RenderSetColor(255, 255, 255, 120);
            DrawLine(*lit);
        }
    }

//
//    for (auto it = std::begin(m_points); it != std::end(m_points); ++it)
//    {
//        provider.RenderSetColor(0, 255, 255, 255);
//        DrawPoint(*it);
//    }
//
//    for (auto lit = std::begin(m_path); lit != std::end(m_path); ++lit)
//    {
//        provider.RenderSetColor(255, 255, 0, 255);
//        DrawLine(*lit);
//    }

#if 1 // render path

    Uint64 ticks = GetMainEngine()->getProvider().GetTicks();
    Uint64 seconds = ticks / 3000;
    Uint32 frameCount = m_arrayOfNodesArray.size();
    Uint32 frameNo = (seconds % frameCount);

    int pos = frameNo;
    if (pos < m_arrayOfNodesArray.size())
    {
        std::vector<void*> &pathTaken = m_arrayOfNodesArray.at(pos);

        for (int i = 0; i < pathTaken.size(); i++)
        {
            if (i + 1 >= pathTaken.size())
            {
                break;
            }
            PathFinderLineGraphNodeI *node = (PathFinderLineGraphNodeI*)pathTaken.at(i);
            PathFinderLineGraphNodeI *nextNode = (PathFinderLineGraphNodeI*)pathTaken.at(i+1);

            Vector2 nodePoint = *node->GetPoint();
            Vector2 nextNodePoint = *nextNode->GetPoint();

            Line line(nodePoint, nextNodePoint);
            provider.RenderSetColor(255, 255, 0, 255);
            provider.RenderDrawLine(nodePoint.x, nodePoint.y, nextNodePoint.x, nextNodePoint.y);

        }
    }
#endif
}

void WalkingBoxes::DrawLine(Line &line)
{
    EngineProviderI &provider = GetMainEngine()->getProvider();
    Vector2 &p1 = line.GetP1();
    Vector2 &p2 = line.GetP2();
    provider.RenderDrawLine(p1.x, p1.y, p2.x, p2.y);
}

void WalkingBoxes::DrawPoint(Vector2 &point)
{
    EngineProviderI &provider = GetMainEngine()->getProvider();
    provider.RenderDrawPoint(point.x, point.y);
}

static float distance = 0;
static float maxDistance = 0;

void WalkingBoxes::CalculatePathTo(Vector2 fromPoint, Vector2 toPoint)
{
    m_points.push_back(toPoint);

    Line myLine(fromPoint, toPoint);

    // should check if the point is not iside a polygon; if so - snap it out of it

    bool intersects = IntersectsAnyline(myLine);
    if (!intersects)
    {
        m_path.push_back(myLine);
    }
    else
    {
        // Go through each point and connected points until a clear
        // line of slight can be established between the testing
        // point and the target provided.
        maxDistance = std::numeric_limits<float>().max()-1;

        m_lineGraph->DistanceToPoint(this, fromPoint, toPoint, &pathStack);
    }

    printf("asdda");
}

void WalkingBoxes::DidStart(float initialDistance)
{
    distance = initialDistance;
}

void WalkingBoxes::DidFind()
{
    bool shouldAddPath = false;

    float thisPathDistance = PathFinderLineGraphNode::RPathDistance(&pathStack) + distance;
    if (thisPathDistance < maxDistance)
    {
        maxDistance = thisPathDistance;
        shouldAddPath = true;
    }

    if (shouldAddPath)
    {
        m_arrayOfNodesArray.clear();

        std::vector<void*> nodes;
        for (auto it = std::begin(pathStack); it != std::end(pathStack); ++it)
        {
            PathFinderLineGraphNodeI *node = *it;
            nodes.emplace_back(node);
        }
        m_arrayOfNodesArray.emplace_back(nodes);

        printf("Found at %d steps, distance = %f\n", nodes.size(), thisPathDistance);
    }
}
