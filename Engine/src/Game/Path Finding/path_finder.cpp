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

#define RENDER_DEBUG_LINES              1

#define RENDER_CONNECTION_LINES         1
    #define RENDER_CONNECTION_LINES_C   255, 0, 0, 100
#define RENDER_POLYGONS                 1
    #define RENDER_POLYGONS_C           255, 255, 255, 120
#define RENDER_CALCULATED_PATH          1
    #define RENDER_CALCULATED_PATH_C    255, 255, 0, 255
#define RENDER_LINE_NORMALS             1
    #define RENDER_LINE_NORMALS_C       255, 255, 0, 255
#define RENDER_VERTEX_NORMAL            1
    #define RENDER_VERTEX_NORMAL_C      0, 255, 0, 255
#define RENDER_NUDGED_LINE              1
    #define RENDER_NUDGED_LINE_C        0, 255, 0, 255

using namespace engine;

PathFinder::PathFinder(std::vector<Polygon> polygonList)
: m_polygons(polygonList), m_lineGraph(nullptr), m_nudgedLine(nullptr)
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
            m_allPoints.push_back(v);
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

                    if (PathFinderUtils::GetLineIntersection(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, &i_x, &i_y))
                    {
                        Vector2 intersectionPoint;
                        intersectionPoint.x = i_x;
                        intersectionPoint.y = i_y;

                        if (!PathFinderUtils::PointListIncludesPoint(intersectionPoint, m_allPoints))
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

    m_lineGraph = std::unique_ptr<PathFinderGraphI>(new PathFinderGraph(m_polygons, m_connectionLines));
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

        if (PathFinderUtils::GetLineIntersection(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, &i_x, &i_y))
        {
            Vector2 intersectionPoint;
            intersectionPoint.x = i_x;
            intersectionPoint.y = i_y;

            if (!PathFinderUtils::PointListIncludesPoint(intersectionPoint, m_allPoints))
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
#if RENDER_DEBUG_LINES
    EngineProviderI &provider = GetMainEngine()->getProvider();

#if RENDER_CONNECTION_LINES
    provider.RenderSetColor(RENDER_CONNECTION_LINES_C);
    std::for_each(m_connectionLines.begin(), m_connectionLines.end(), [&](Line &p) {
        DrawLine(p);
    });
#endif

#if RENDER_POLYGONS
    provider.RenderSetColor(RENDER_POLYGONS_C);
    std::for_each(m_polygons.begin(), m_polygons.end(), [&](Polygon &p) {
        std::for_each(p.GetLines().begin(), p.GetLines().end(), [&](Line &l) {
            DrawLine(l);
        });
    });
#endif

#if RENDER_CALCULATED_PATH
    provider.RenderSetColor(RENDER_CALCULATED_PATH_C);
    if (m_calculatedPath != NULL)
    {
        Vector2 *previous = nullptr;
        std::vector<Vector2> &points = m_calculatedPath.get()->GetPath();
        std::for_each(points.begin(), points.end(), [&](Vector2 &v) {
            if (previous)
            {
                provider.RenderDrawLine(previous->x, previous->y, v.x, v.y);
            }
            previous = &v;
        });
    }
#endif

#if RENDER_LINE_NORMALS
    provider.RenderSetColor(RENDER_LINE_NORMALS_C);
    std::for_each(m_allLines.begin(), m_allLines.end(), [&](Line &l){
        Line nl = l.MakeNormalLine(10);
        provider.RenderDrawLine(nl.GetP1().x, nl.GetP1().y, nl.GetP2().x, nl.GetP2().y);
    });
#endif

#if RENDER_VERTEX_NORMAL
    provider.RenderSetColor(RENDER_VERTEX_NORMAL_C);
    for (auto it = std::begin(m_lineGraph->GetNodes()); it != std::end(m_lineGraph->GetNodes()); ++it)
    {
        PathFinderLineGraphNodeI *node = it->get();
        Vector2 normal = Vector2Scaled(node->GetNormal(), 10);
        Vector2 &p1 = *node->GetPoint();
        Vector2 p2 = Vector2Add(p1, normal);
        provider.RenderDrawLine(p1.x, p1.y, p2.x, p2.y);
    }
#endif

#if RENDER_NUDGED_LINE
    if (m_nudgedLine != nullptr)
    {
        provider.RenderDrawLine(m_nudgedLine->GetP1().x, m_nudgedLine->GetP1().y, m_nudgedLine->GetP2().x, m_nudgedLine->GetP2().y);
    }
#endif

#endif // RENDER_DEBUG_LINES
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
    m_targetPosition = NudgedPosition(toPoint);

    m_maxDistance = std::numeric_limits<float>().max()-1;

    m_calculatedPath.reset();

    performanceMeasure("path", [&](void) {
        m_lineGraph->DistanceToPoint(this, m_polygons, fromPoint, m_targetPosition, &m_tempPathStack);
    });

    return m_calculatedPath.get();
}

Vector2 PathFinder::NudgedPosition(Vector2 position)
{
    float maxDistance = std::numeric_limits<float>().max()-1;

    std::for_each(m_polygons.begin(), m_polygons.end(), [&](Polygon &poly){
        std::for_each(poly.GetLines().begin(), poly.GetLines().end(), [&](Line &line){
            float distance = line.DistanceToPoint(position);
            if (distance < maxDistance)
            {
                maxDistance = distance;
                m_nudgedLine = &line;
            }
        });
    });

    if (m_nudgedLine != nullptr)
    {
        Vector2 normal = m_nudgedLine->GetNormal();
        Vector2 scaled = Vector2Scaled(normal, maxDistance + 1);
        Vector2 newPosition = Vector2Add(position, scaled);
        return newPosition;;
    }
    else
    {
        return position;
    }
}

void PathFinder::DidFindPath(std::unique_ptr<PathI> &path)
{
    float distance = path->GetDistance();
    if (distance < m_maxDistance)
    {
        m_maxDistance = distance;
        m_calculatedPath = std::move(path);
    }
}
