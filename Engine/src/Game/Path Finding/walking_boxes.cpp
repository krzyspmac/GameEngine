//
//  walking_boxes.cpp
//  Engine
//
//  Created by krzysp on 26/12/2021.
//

#include "walking_boxes.hpp"
#include "engine_provider_interface.h"
#include "engine_interface.h"
#include <iostream>

using namespace engine;

char get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y,
                           float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y);

bool IsIntersecting(Vector2 a, Vector2 b, Vector2 c, Vector2 d)
{
    float denominator = ((b.x - a.x) * (d.y - c.y)) - ((b.y - a.y) * (d.x - c.x));
    float numerator1 = ((a.y - c.y) * (d.x - c.x)) - ((a.x - c.x) * (d.y - c.y));
    float numerator2 = ((a.y - c.y) * (b.x - a.x)) - ((a.x - c.x) * (b.y - a.y));

    // Detect coincident lines (has a problem, read below)
    if (denominator == 0) return numerator1 == 0 && numerator2 == 0;

    float r = numerator1 / denominator;
    float s = numerator2 / denominator;

    return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
}

bool IsVertexPoint(Vector2 &point, std::vector<Vector2> &points)
{
    for (auto it = std::begin(points); it != std::end(points); ++it)
    {
        Vector2 &vp = *it;
        if (vp.x == point.x && vp.y == point.y)
        {
            return true;
        }
    }
    return false;
}

static bool LineSegmentsCross(Vector2 a, Vector2 b, Vector2 c, Vector2 d)
{
    float denominator = ((b.x - a.x) * (d.y - c.y)) - ((b.y - a.y) * (d.x - c.x));

    if (denominator == 0)
    {
        return false;
    }

    float numerator1 = ((a.y - c.y) * (d.x - c.x)) - ((a.x - c.x) * (d.y - c.y));

    float numerator2 = ((a.y - c.y) * (b.x - a.x)) - ((a.x - c.x) * (b.y - a.y));

    if (numerator1 == 0 || numerator2 == 0)
    {
        return false;
    }

    float r = numerator1 / denominator;
    float s = numerator2 / denominator;

    return (r > 0 && r < 1) && (s > 0 && s < 1);
}


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
    std::vector<Vector2> allPoints;
    for (auto it = std::begin(m_polygons); it != std::end(m_polygons); ++it)
    {
        Polygon &polygon = *it;
        std::vector<Vector2> points = polygon.GetPoints();

        for (auto pit = std::begin(points); pit != std::end(points); ++pit)
        {
            allPoints.push_back(*pit);
        }
    }

    // Join all lines into one array
    std::vector<Line> allLines;
    for (auto it = std::begin(m_polygons); it != std::end(m_polygons); ++it)
    {
        Polygon &polygon = *it;
        std::vector<Line> lines = polygon.GetLines();

        for (auto pit = std::begin(lines); pit != std::end(lines); ++pit)
        {
            allLines.push_back(*pit);
        }
    }

    // Make a line connection from each
    int polyCount = m_polygons.size();
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

                for (auto lit = std::begin(allLines); lit != std::end(allLines); ++lit)
                {
                    Line &line = *lit;
                    Vector2 &p2 = line.GetP1();
                    Vector2 &p3 = line.GetP2();

                    float i_x;
                    float i_y;

                    if (get_line_intersection(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, &i_x, &i_y))
                    {
                        Vector2 intersectionPoint;
                        intersectionPoint.x = i_x;
                        intersectionPoint.y = i_y;

                        if (!IsVertexPoint(intersectionPoint, allPoints))
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

#if 0
    // Make a line between each point and any other point. Check if the line
    // does not cross any other polygon line.
    for (auto cPoint = std::begin(allPoints); cPoint != std::end(allPoints); ++cPoint)
    {
        for (auto tPoint = std::begin(allPoints); tPoint != std::end(allPoints); ++tPoint)
        {
            Vector2 &p0 = *cPoint;
            Vector2 &p1 = *tPoint;

            if (Vector2Equals(p0, p1))
            {
                continue;
            }
            bool intersects = false;
            for (auto lit = std::begin(allLines); lit != std::end(allLines); ++lit)
            {
                Line &line = *lit;
                Vector2 &p2 = line.GetP1();
                Vector2 &p3 = line.GetP2();

                float i_x;
                float i_y;

                if (get_line_intersection(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, &i_x, &i_y))
                {
                    Vector2 intersectionPoint;
                    intersectionPoint.x = i_x;
                    intersectionPoint.y = i_y;

                    printf("asD");
                    //if (!Vector2Equals(intersectionPoint, p0) && !Vector2Equals(intersectionPoint, p1) && !Vector2Equals(intersectionPoint, p2), !Vector2Equals(intersectionPoint, p3))
                    if (!IsVertexPoint(intersectionPoint, allPoints))
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
#endif
}

bool WalkingBoxes::IntersectsAnyline(Line &line)
{
    return false;
}

void WalkingBoxes::Draw()
{
    EngineProviderI &provider = GetMainEngine()->getProvider();

    for (auto lit = std::begin(m_connectionLines); lit != std::end(m_connectionLines); ++lit)
    {
        provider.RenderSetColor(255, 0, 0, 255);
        DrawLine(*lit);
    }

    for (auto it = std::begin(m_polygons); it != std::end(m_polygons); ++it)
    {
        Polygon &polygon = *it;
        std::vector<Line> &lines = polygon.GetLines();

        for (auto lit = std::begin(lines); lit != std::end(lines); ++lit)
        {
            provider.RenderSetColor(255, 255, 255, 255);
            DrawLine(*lit);
        }
    }

}

void WalkingBoxes::DrawLine(Line &line)
{
    EngineProviderI &provider = GetMainEngine()->getProvider();
    Vector2 &p1 = line.GetP1();
    Vector2 &p2 = line.GetP2();
    provider.RenderDrawLine(p1.x, p1.y, p2.x, p2.y);
}

// Andre LeMothe's "Tricks of the Windows Game Programming Gurus".
// Returns 1 if the lines intersect, otherwise 0. In addition, if the lines
// intersect the intersection point may be stored in the floats i_x and i_y.
char get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y,
    float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y)
{
    float s1_x, s1_y, s2_x, s2_y;
    s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

    float s, t;
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        // Collision detected
        if (i_x != NULL)
            *i_x = p0_x + (t * s1_x);
        if (i_y != NULL)
            *i_y = p0_y + (t * s1_y);
        return 1;
    }

    return 0; // No collision
}
