//
//  walking_boxes.cpp
//  Engine
//
//  Created by krzysp on 26/12/2021.
//

#include <iostream>
#include <limits>
#include "path_finder.hpp"
#include "engine_provider_interface.h"
#include "engine_interface.h"
#include "path_finder_line_graph_node.hpp"
#include "path_finder_helper.hpp"
#include "path.hpp"
#include "performance.hpp"

#define RENDER_CONNECTION_LINES         1
#define RENDER_POLYGONS                 1
#define RENDER_CALCULATED_PATH          1

using namespace engine;

static Vector2 recalculatedPosition = Vector2Zero;

PathFinder::PathFinder(std::vector<Polygon> polygonList)
: m_polygons(polygonList)
{
    performanceMeasure("PathFinder::init", [&]{
        Prepare();
    });
}

PathFinder::~PathFinder()
{
    delete m_lineGraph;
}

void PathFinder::Prepare()
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

bool PathFinder::IntersectsAnyline(Line &myLine)
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

void PathFinder::Draw()
{
    EngineProviderI &provider = GetMainEngine()->getProvider();

#if RENDER_CONNECTION_LINES
    provider.RenderSetColor(255, 0, 0, 100);
    std::for_each(m_connectionLines.begin(), m_connectionLines.end(), [&](Line &p) { DrawLine(p); });
#endif

#if RENDER_POLYGONS
    provider.RenderSetColor(255, 255, 255, 120);
    std::for_each(m_polygons.begin(), m_polygons.end(), [&](Polygon &p) {
        std::for_each(p.GetLines().begin(), p.GetLines().end(), [&](Line &l) {
            DrawLine(l);
        });
    });
#endif

#if RENDER_CALCULATED_PATH
    provider.RenderSetColor(255, 255, 0, 255);
    Vector2 *previous = nullptr;
    std::for_each(m_calculatedPath.begin(), m_calculatedPath.end(), [&](Vector2 &v) {
        if (previous)
        {
            provider.RenderDrawLine(previous->x, previous->y, v.x, v.y);
        }
        previous = &v;
    });
#endif
}

void PathFinder::DrawLine(Line &line)
{
    EngineProviderI &provider = GetMainEngine()->getProvider();
    Vector2 &p1 = line.GetP1();
    Vector2 &p2 = line.GetP2();
    provider.RenderDrawLine(p1.x, p1.y, p2.x, p2.y);
}

void PathFinder::DrawPoint(Vector2 &point)
{
    EngineProviderI &provider = GetMainEngine()->getProvider();
    provider.RenderDrawPoint(point.x, point.y);
}

bool PathFinder::PointInsidePolygons(Vector2 &point, Polygon **outPolygon)
{
    for (auto it = std::begin(m_polygons); it != std::end(m_polygons); ++it)
    {
        bool containsPoint = it->IsPointInside(point);
        if (containsPoint)
        {
            if (outPolygon)
            {
                *outPolygon = &(*it);
            }
            return true;
        }
    }

    return false;
}

PathI *PathFinder::CalculatePath(Vector2 fromPoint, Vector2 toPoint)
{
    m_startPosition = fromPoint;
    m_targetPosition = toPoint;

    Line myLine(fromPoint, m_targetPosition);

    // should check if the point is not iside a polygon; if so - snap it out of it
    EngineProviderI &provider = GetMainEngine()->getProvider();
    Uint64 start = provider.GetTicks();

    // TODO: needs work due to issues with offending vertices when snapping out of the polygon
    Polygon *offendingPolygon = NULL;
    if (PointInsidePolygons(m_targetPosition, &offendingPolygon))
    {
//        Vector2 recalculated;
//        if (offendingPolygon->NearestPointOutsideFrom(m_targetPosition, &recalculated))
//        {
//            if (!PointInsidePolygons(recalculated, NULL))
//            {
//                m_targetPosition = recalculated;
//                recalculatedPosition = m_targetPosition;
//            }
//            else
//            {
                // cannot walk there!
                return NULL;
                //return Path();
//            }
//        }
    }

    Uint64 end = provider.GetTicks();
    Uint64 delta = end - start;
    printf("contains point took %d ms\n", delta);

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

        performanceMeasure("path", [&](void) {
            m_lineGraph->DistanceToPoint(this, fromPoint, m_targetPosition, &m_tempPathStack);
        });
    }

    return new Path(m_calculatedPath);
}

void PathFinder::DidStart(float initialDistance)
{
    m_startingDistance = initialDistance;
}

void PathFinder::DidFind()
{
    bool shouldAddPath = false;

    float endingDistance = 0;
    if (m_tempPathStack.size() > 0)
    {
        if (!PointInsidePolygons(m_targetPosition, NULL))
        {
            PathFinderLineGraphNodeI *last = m_tempPathStack.at(m_tempPathStack.size()-1);
            Line lastLine(*last->GetPoint(), m_targetPosition);
            endingDistance = lastLine.GetLength();
        }
    }

    float thisPathDistance = PathFinderLineGraphNode::RPathDistance(&m_tempPathStack) + m_startingDistance + endingDistance;

    if (thisPathDistance < m_maxDistance)
    {
        m_maxDistance = thisPathDistance;
        shouldAddPath = true;
    }

    if (shouldAddPath)
    {
        printf("CHOSEN with distance = %f\n\n", thisPathDistance);
        m_calculatedPath.clear();

        m_calculatedPath = PathFinderUtils::ListOfNodesToVectors(&m_tempPathStack);
        m_calculatedPath.insert(std::begin(m_calculatedPath), m_startPosition);
        if (!PointInsidePolygons(m_targetPosition, NULL))
        {
            m_calculatedPath.push_back(m_targetPosition);
        }

        Path path(m_calculatedPath);
    }
}
