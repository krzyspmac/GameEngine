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
: m_polygons(polygonList), m_lineGraph(nullptr)
{
    performanceMeasure("PathFinder::init", [&]{
        Prepare();
    });
}

PathFinder::~PathFinder()
{
}

void PathFinder::Prepare()
{
    // Join all points into one array.
    std::for_each(m_polygons.begin(), m_polygons.end(), [&](Polygon &p){
        std::for_each(p.GetPoints().begin(), p.GetPoints().end(), [&](Vector2 &v){
            m_allPoint.push_back(v);
        });
    });

    // Join all lines into one array.
    // Also all polygon lines are "connecting" lines, so add them as well.
    std::for_each(m_polygons.begin(), m_polygons.end(), [&](Polygon &p){
        std::for_each(p.GetLines().begin(), p.GetLines().end(), [&](Line &l) {
            m_allLines.push_back(l);
            m_connectionLines.push_back(l);
        });
    });

    // Make a line connection from each point in each polygon
    // to each other point in every other polygon.
    // Get rid of connections that cross any existing line.
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

    m_lineGraph = std::unique_ptr<PathFinderGraphI>(new PathFinderGraph(m_connectionLines));
}

bool PathFinder::IntersectsAnyline(Line &myLine)
{
    Vector2 &p0 = myLine.GetP1();
    Vector2 &p1 = myLine.GetP2();

    bool intersects = false;

    std::all_of(m_allLines.begin(), m_allLines.end(), [&](Line &line){
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
                return false;
            }
        }

        return true;
    });

    return intersects;
}

void PathFinder::Draw()
{
    EngineProviderI &provider = GetMainEngine()->getProvider();

#if RENDER_CONNECTION_LINES
    provider.RenderSetColor(255, 0, 0, 100);
    std::for_each(m_connectionLines.begin(), m_connectionLines.end(), [&](Line &p) {
        DrawLine(p);
    });
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

    // Draw each normal vector for each line
    std::for_each(m_allLines.begin(), m_allLines.end(), [&](Line &l){
        Line nl = l.MakeNormalLine(10);
        provider.RenderDrawLine(nl.GetP1().x, nl.GetP1().y, nl.GetP2().x, nl.GetP2().y);

//        Vector2 &p1 = l.GetP1();
//        Vector2 p1n = Vector2Add(p1, l.GetP1OutsideVector());
//        p1n = Vector2Scaled(p1n, 2);
//        Line p1nl(p1, p1n);
//        provider.RenderDrawLine(p1nl.GetP1().x, p1nl.GetP1().y, p1nl.GetP2().x, p1nl.GetP2().y);
//
//        Vector2 &p2 = l.GetP2();
//        Vector2 p2n = Vector2Add(p2, l.GetP2OutsideVector());
//        p2n = Vector2Scaled(p2n, 2);
//        Line p2nl(p2, p2n);
//        provider.RenderDrawLine(p2nl.GetP1().x, p2nl.GetP1().y, p2nl.GetP2().x, p2nl.GetP2().y);
    });

    // Draw each normal vector for each vertice in the graph
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
        m_calculatedPath.clear();

        performanceMeasure("path", [&](void) {
            m_lineGraph->DistanceToPoint(this, m_polygons, fromPoint, m_targetPosition, &m_tempPathStack);
        });
    }

    return new Path(m_calculatedPath);
}

Vector2 PathFinder::NudgedPosition(Vector2 position)
{
    return Vector2Zero;
}

void PathFinder::DidStart(float initialDistance)
{
    m_startingDistance = initialDistance;
}

void PathFinder::DidFind()
{
    float endingDistance = (!m_tempPathStack.empty() && !PointInsidePolygons(m_targetPosition, NULL))
    ?   Vector2Distance(*m_tempPathStack.back()->GetPoint(), m_targetPosition)
    :   0
    ;

    bool insideAnyPolygon = false;
    for (auto it = std::begin(m_tempPathStack); it != std::end(m_tempPathStack); ++it)
    {
        PathFinderLineGraphNodeI *node = *it;
        Vector2 &point = *node->GetPoint();
        if (PointInsidePolygons(point, NULL))
        {
            insideAnyPolygon = true;
            break;
        }
    }

    if (!insideAnyPolygon)
    {
        float distance = PathFinderLineGraphNode::RPathDistance(&m_tempPathStack) + m_startingDistance + endingDistance;
        if (distance < m_maxDistance)
        {
            m_maxDistance = distance;

            m_calculatedPath.clear();

            m_calculatedPath = PathFinderUtils::ListOfNodesToVectors(&m_tempPathStack);
            m_calculatedPath.insert(std::begin(m_calculatedPath), m_startPosition);
            if (!PointInsidePolygons(m_targetPosition, NULL))
            {
                m_calculatedPath.push_back(m_targetPosition);
            }
        }
    }
}
