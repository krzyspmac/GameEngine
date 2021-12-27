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
#include <limits>

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

bool IntersectsAnyline(Line &myLine, std::vector<Vector2> &m_allPoint, std::vector<Line> m_allLines)
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

        if (get_line_intersection(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, &i_x, &i_y))
        {
            Vector2 intersectionPoint;
            intersectionPoint.x = i_x;
            intersectionPoint.y = i_y;

            if (!IsVertexPoint(intersectionPoint, m_allPoint))
            {
                intersects = true;
                break;
            }
        }
    }

    return intersects;
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

bool IsPointWithingViewport(Vector2 &point)
{
    Size &viewportSize = GetMainEngine()->GetViewport();
    if (point.x > 0 && point.x < viewportSize.width && point.y > 0 && point.y < viewportSize.height)
    {
        return true;
    }
    else
    {
        return false;
    }
}

class LineGraphNode: public PathFinderLineGraphNodeI
{
public:
    LineGraphNode(Vector2 *point): PathFinderLineGraphNodeI(point),  m_point(point)
    { }

public:
    Vector2 *GetPoint() { return m_point; };

    void AddConnection(LineGraphNode *node) { m_connectingNodes.emplace_back(node); };
    std::vector<LineGraphNode*>& GetConnectings() { return m_connectingNodes; };
    bool HasConnection(Vector2 *point)
    {
        Vector2 &targetPoint = *point;

        for (auto it = std::begin(m_connectingNodes); it != std::end(m_connectingNodes); ++it)
        {
            LineGraphNode *stored = *it;
            Vector2 *storedPointEx = stored->GetPoint();
            Vector2 &storedPoint = *(storedPointEx);

            if (Vector2Equals(targetPoint, storedPoint))
            {
                return true;
            }
        }
        return false;
    }

    static void RPathClearUpTo(std::vector<PathFinderLineGraphNodeI*> *pathStack, LineGraphNode *upToHere)
    {
        int foundIndex = -1;

        for (int i = 0; i < pathStack->size(); i++)
        {
            PathFinderLineGraphNodeI *node = pathStack->at(i);
            if (node == upToHere)
            {
                foundIndex = i;
            }
        }

        for (int i = pathStack->size()-1; i > foundIndex; i--)
        {
            pathStack->pop_back();
        }
    }

    static bool RPathContains(std::vector<PathFinderLineGraphNodeI*> *pathStack, LineGraphNode *targetNode)
    {
        for (int i = 0; i < pathStack->size(); i++)
        {
            PathFinderLineGraphNodeI *node = pathStack->at(i);
            if (node == targetNode)
            {
                return true;;
            }
        }

        return false;;
    }

    static float RPathDistance(std::vector<PathFinderLineGraphNodeI*> *pathStack)
    {
        float distance = 0;
        size_t count = pathStack->size();

        for (int i = 0; i < count; i++)
        {
            if (i+1 >= count)
            {
                break;;
            }

            PathFinderLineGraphNodeI *node = pathStack->at(i);
            PathFinderLineGraphNodeI *nextNode = pathStack->at(i+1);

            Vector2 nodePoint = *node->GetPoint();
            Vector2 nextNodePoint = *nextNode->GetPoint();

            Line line(nodePoint, nextNodePoint);
            distance += line.GetLength();
        }

        return distance;
    }

    // Go through all the connections until a clear line of sight can be establised
    // between the current point and  targetPoint. Keep track of travelled distance
    // and choose the smallest one.
    // Returns true if the connection can be made
    void DistanceToPoint(PathFinderBaseI *sender, Vector2 &targetPoint, std::vector<PathFinderLineGraphNodeI*> *pathStack)
    {
        pathStack->emplace_back(this); // put back to the stack; we don't want to traverse the same point again

        Line targetLine(*m_point, targetPoint);
        if (!IntersectsAnyline(targetLine, sender->GetAllPoint(), sender->GetAllLines()))
        {
            // If there's a connection and we're not crossing any other lines it's a hit!
            sender->DidFind();
            return;
        }

        if (m_connectingNodes.size() < 1)
        {
            // Can't go anywhere further.
            return;
        }

        for (auto it = std::begin(m_connectingNodes); it != std::end(m_connectingNodes); ++it)
        {
            // clear all traversed point up to certain point; should be somewhere at the end
            LineGraphNode::RPathClearUpTo(pathStack, this);

            LineGraphNode *node = *it;

            if (RPathContains(pathStack, node))
            {
                continue;
            }

            Vector2 *point = node->GetPoint();
            if (!IsPointWithingViewport(*point))
            {
                continue;
            }

            node->DistanceToPoint(sender, targetPoint, pathStack);
        }
    }

private:
    Vector2 *m_point;
    std::vector<LineGraphNode*> m_connectingNodes;
};

static int max_iteration = 1024;
static int cur_iteration = 0;

class LineGraph
{
public:
    LineGraph(std::vector<Line> lines): m_connectingLines(lines)
    {
        Prepare();
    };

public:

    LineGraphNode *GetNodeForPoint(Vector2 &point)
    {
        for (auto it = std::begin(m_nodes); it != std::end(m_nodes); ++it)
        {
            LineGraphNode *node = it->get();
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

            LineGraphNode *nodeP1 = GetNodeForPoint(p1);
            if (!nodeP1)
            {
                nodeP1 = new LineGraphNode(&(p1));
                m_nodes.emplace_back(std::move(nodeP1));
            }

            LineGraphNode *nodeP2 = GetNodeForPoint(p2);
            if (!nodeP2)
            {
                nodeP2 = new LineGraphNode(&(p2));
                m_nodes.emplace_back(std::move(nodeP2));
            }
        }

        // Go through each point node and check if it connects, via line,
        // to any other node.
        for (auto it = std::begin(m_nodes); it != std::end(m_nodes); ++it)
        {
            LineGraphNode *node = it->get();
            Vector2 *nodePoint = node->GetPoint();

            for (auto pit = std::begin(m_nodes); pit != std::end(m_nodes); ++pit)
            {
                LineGraphNode *otherNode = pit->get();
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
                        if (!node->HasConnection(otherNodePoint))
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

            LineGraphNode *node = it->get();
            Vector2 &point = *node->GetPoint();

            if (!IsPointWithingViewport(point))
            {
                continue;
            }

            // Check if we can see the first node
            Line lineToFirstNode(startingPoint, point);

            if (IntersectsAnyline(lineToFirstNode, sender->GetAllPoint(), sender->GetAllLines()))
            {
                continue;
            }

            sender->DidStart(lineToFirstNode.GetLength());

            node->DistanceToPoint(sender, targetPoint, pathStack);
        }
        return 0;
    }

    std::vector<std::unique_ptr<LineGraphNode>>& GetNodes() { return m_nodes; };

public:
    std::vector<Line> m_connectingLines;
    std::vector<std::unique_ptr<LineGraphNode>> m_nodes;

    std::vector<LineGraphNode*> m_path;
};


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

                    if (get_line_intersection(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, &i_x, &i_y))
                    {
                        Vector2 intersectionPoint;
                        intersectionPoint.x = i_x;
                        intersectionPoint.y = i_y;

                        if (!IsVertexPoint(intersectionPoint, m_allPoint))
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

    m_lineGraph = new LineGraph(m_connectionLines);
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

        if (get_line_intersection(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, &i_x, &i_y))
        {
            Vector2 intersectionPoint;
            intersectionPoint.x = i_x;
            intersectionPoint.y = i_y;

            if (!IsVertexPoint(intersectionPoint, m_allPoint))
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
            LineGraphNode *node = (LineGraphNode*)pathTaken.at(i);
            LineGraphNode *nextNode = (LineGraphNode*)pathTaken.at(i+1);

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
        LineGraph *lg = (LineGraph*)m_lineGraph;
        maxDistance = std::numeric_limits<float>().max()-1;

        if (lg->DistanceToPoint(this, fromPoint, toPoint, 0, &pathStack))
        {

        }
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

    float thisPathDistance = LineGraphNode::RPathDistance(&pathStack) + distance;
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
