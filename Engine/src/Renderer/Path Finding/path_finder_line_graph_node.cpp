//
//  path_finder_line_graph_node.cpp
//  Engine
//
//  Created by krzysp on 27/12/2021.
//

#include "path_finder_line_graph_node.hpp"
#include "path_finder_helper.hpp"

using namespace engine;

void PathFinderLineGraphNode::AddConnection(PathFinderLineGraphNodeI *node)
{
    m_connectingNodes.emplace_back(node);
}

std::vector<PathFinderLineGraphNodeI*>& PathFinderLineGraphNode::GetConnections()
{
    return m_connectingNodes;
}

bool PathFinderLineGraphNode::HasConnectionWithPoint(Vector2 *point)
{
    Vector2 &targetPoint = *point;

    for (auto it = std::begin(m_connectingNodes); it != std::end(m_connectingNodes); ++it)
    {
        if (Vector2Equals(targetPoint, *((*it)->GetPoint())))
        {
            return true;
        }
    }
    return false;
}

void PathFinderLineGraphNode::RPathClearUpTo(std::vector<PathFinderLineGraphNodeI*> *pathStack, PathFinderLineGraphNodeI *upToHere)
{
    int foundIndex = -1;

    for (int i = 0; i < pathStack->size(); i++)
    {
        PathFinderLineGraphNodeI *node = pathStack->at(i);
        if (node == upToHere)
        {
            foundIndex = i;
            break;
        }
    }

    for (size_t i = pathStack->size()-1; i > foundIndex; i--)
    {
        pathStack->pop_back();
    }
}

bool PathFinderLineGraphNode::RPathContains(std::vector<PathFinderLineGraphNodeI*> *pathStack, PathFinderLineGraphNodeI *targetNode)
{
    for (int i = 0; i < pathStack->size(); i++)
    {
        if (pathStack->at(i) == targetNode) { return true; }
    }

    return false;
}

float PathFinderLineGraphNode::RPathDistance(std::vector<PathFinderLineGraphNodeI*> *pathStack)
{
    float distance = 0;
    size_t count = pathStack->size();

    for (int i = 0; i < count; i++)
    {
        if (i+1 >= count) { break; }

        PathFinderLineGraphNodeI *node = pathStack->at(i);
        PathFinderLineGraphNodeI *nextNode = pathStack->at(i+1);

        Vector2 nodePoint = *node->GetPoint();
        Vector2 nextNodePoint = *nextNode->GetPoint();

        Line line(nodePoint, nextNodePoint);
        distance += line.GetLength();
    }

    return distance;
}

void PathFinderLineGraphNode::DistanceToPoint(PathFinderBaseI *sender, Vector2 &startingPoint, Vector2 &targetPoint, std::vector<PathFinderLineGraphNodeI*> *pathStack)
{
    pathStack->emplace_back(this); // put back to the stack; we don't want to traverse the same point again

    Line targetLine(*m_point, targetPoint);
    if (!PathFinderUtils::IntersectsAnyline(targetLine, sender->GetAllPoint(), sender->GetAllLines()))
    {
        // If there's a connection and we're not crossing any other lines it's a hit!
        std::unique_ptr<PathI> path = PathFinderUtils::NodesToPath(pathStack, startingPoint, targetPoint, 3);
        sender->DidFindPath(path);
    }

    if (m_connectingNodes.size() < 1)
    {
        // Can't go anywhere further.
        return;
    }

    // tmp; take the shortest distance from the connected nodes
    float distance = std::numeric_limits<float>().max()-1;

    PathFinderLineGraphNodeI *shortest = nullptr;
    for (auto it = std::begin(m_connectingNodes); it != std::end(m_connectingNodes); ++it)
    {
        PathFinderLineGraphNodeI *node = *it;
        if (RPathContains(pathStack, node)) { continue; }

        Vector2 *point = node->GetPoint();
        if (!PathFinderUtils::IsPointWithingViewport(*point)) { continue; }


        Line l(*(this->GetPoint()), *point);
        float thisDistance = l.GetLength();
        if (thisDistance < distance)
        {
            distance = thisDistance;
            shortest = *it;
        }
    }

    if (shortest != nullptr)
    {
        shortest->DistanceToPoint(sender, startingPoint, targetPoint, pathStack);
    }
    else
    {
        for (auto it = std::begin(m_connectingNodes); it != std::end(m_connectingNodes); ++it)
        {
                // clear all traversed point up to certain point; should be somewhere at the end
            PathFinderLineGraphNode::RPathClearUpTo(pathStack, this);

            PathFinderLineGraphNodeI *node = *it;
            if (RPathContains(pathStack, node)) { continue; }

            Vector2 *point = node->GetPoint();
            if (!PathFinderUtils::IsPointWithingViewport(*point)) { continue; }

            // iterate further
            node->DistanceToPoint(sender, startingPoint, targetPoint, pathStack);
        }
    }
}
