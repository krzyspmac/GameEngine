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
#include "path_finder_helper.hpp"
#include <iostream>
#include <limits>

using namespace engine;

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

WalkingBoxes::~WalkingBoxes()
{
    delete m_lineGraph;
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

    // At the beginning add all the polygon lines. Those will be the connecting lines
    // as well.
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

    for (int i = 0; i < m_calculatedPath.size(); i++)
    {
        if (i + 1 >= m_calculatedPath.size())
        {
            break;
        }
        Vector2 &nodePoint = m_calculatedPath.at(i);
        Vector2 &nextNodePoint = m_calculatedPath.at(i+1);
        provider.RenderSetColor(255, 255, 0, 255);
        provider.RenderDrawLine(nodePoint.x, nodePoint.y, nextNodePoint.x, nextNodePoint.y);
    }
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

void WalkingBoxes::CalculatePathTo(Vector2 fromPoint, Vector2 toPoint)
{
    m_startPosition = fromPoint;
    m_targetPosition = toPoint;

    Line myLine(fromPoint, toPoint);

    // should check if the point is not iside a polygon; if so - snap it out of it


    // Can a clear line of slight be established?
    bool intersects = IntersectsAnyline(myLine);
    if (!intersects)
    {
        m_calculatedPath.clear();
        m_calculatedPath.insert(std::begin(m_calculatedPath), m_startPosition);
        m_calculatedPath.push_back(m_targetPosition);
    }
    else
    {
        // Go through each point and connected points until a clear
        // line of slight can be established between the testing
        // point and the target provided.
        m_maxDistance = std::numeric_limits<float>().max()-1;

        EngineProviderI &provider = GetMainEngine()->getProvider();
        Uint64 start = provider.GetTicks();
        m_lineGraph->DistanceToPoint(this, fromPoint, toPoint, &m_tempPathStack);
        Uint64 end = provider.GetTicks();
        Uint64 delta = end - start;
        printf("calculate took %d ms\n", delta);
    }

    printf("asdda");
}

void WalkingBoxes::DidStart(float initialDistance)
{
    m_startingDistance = initialDistance;
}

void WalkingBoxes::DidFind()
{
    bool shouldAddPath = false;

    float thisPathDistance = PathFinderLineGraphNode::RPathDistance(&m_tempPathStack) + m_startingDistance;
    if (thisPathDistance < m_maxDistance)
    {
        m_maxDistance = thisPathDistance;
        shouldAddPath = true;
    }

    if (shouldAddPath)
    {
        m_calculatedPath.clear();

        m_calculatedPath = PathFinderUtils::ListOfNodesToVectors(&m_tempPathStack);
        m_calculatedPath.insert(std::begin(m_calculatedPath), m_startPosition);
        m_calculatedPath.push_back(m_targetPosition);
    }
}
