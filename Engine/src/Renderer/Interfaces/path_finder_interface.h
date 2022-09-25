//
//  path_finding_interface.h
//  Engine
//
//  Created by krzysp on 27/12/2021.
//

#ifndef path_finder_interface_h
#define path_finder_interface_h

#include <iostream>
#include "interfaces.h"
#include "polygon.hpp"

namespace engine
{
    /// Interface for the path result
    class PathI
    {
    public:
        PathI() { };
        PathI(Vector2 from, Vector2 to) { };
        PathI(std::vector<Vector2> path): m_path(path) { }
        virtual ~PathI() { };

    public:
        std::vector<Vector2> &GetPath() { return m_path; };
        virtual std::vector<Line> ToLines() = 0;
        virtual float GetDistance() = 0;
        virtual std::string Description() = 0;
    protected:
        std::vector<Vector2> m_path;
    };

    /// Path finder callbacks
    class PathFinderCallbackI
    {
    public:
        virtual void DidFindPath(std::unique_ptr<PathI>&) = 0;
    };

    /// Path finder data accessors
    class PathFinderDataI
    {
    public:
        ///
        virtual std::vector<Vector2> &GetAllPoint() = 0;

        ///
        virtual std::vector<Line> &GetAllLines() = 0;

    public:
        /// Check if a target line intersects any other line.
        virtual bool IntersectsAnyline(Line &line) = 0;

        /// Checks if a target point is indie any polygon.
        virtual bool PointInsidePolygons(Vector2 &point, Polygon **outPolygon) = 0;

        /// Result is kept internally. The caller should make a copy.
        virtual PathI *CalculatePath(Vector2 fromPoint, Vector2 toPoint) = 0;

        /// Modify the starting point to better suit the algorithm. Limit the number
        /// of errors due to the origin point being on the polygon line.
        virtual Vector2 NudgedPosition(Vector2 position) = 0;
    };

    /// Path finder amalgamated interface
    class PathFinderBaseI: public PathFinderCallbackI, public PathFinderDataI
    {
    };

    // Path finder node
    class PathFinderLineGraphNodeI
    {
    public:
        /// Does not assume ownershop of point. Point must
        /// exists throughout the life of PathFinderLineGraphNodeI.
        PathFinderLineGraphNodeI(Vector2 *point): m_point(point), m_normal({0.f, 0.f}) { };
        virtual ~PathFinderLineGraphNodeI() { };
        
    public:
        ///
        Vector2 *GetPoint() { return m_point; };

        ///
        void SetNormal(Vector2 value) { m_normal = value; };

        ///
        Vector2 &GetNormal() { return m_normal; };

        ///
        virtual void AddConnection(PathFinderLineGraphNodeI *node) = 0;

        ///
        virtual std::vector<PathFinderLineGraphNodeI*>& GetConnections() = 0;

        ///
        virtual bool HasConnectionWithPoint(Vector2 *point) = 0;

        /// Calcultes the distance from a target point all they way
        /// through all the connecting points.
        /// Upon each loop as `DidStart` will be called with the initial distance.
        /// Each time a path if found a `DidFind` will be executed.
        virtual void DistanceToPoint(PathFinderBaseI *sender, Vector2 &startingPoint, Vector2 &targetPoint, std::vector<PathFinderLineGraphNodeI*> *pathStack) = 0;

    protected:
        Vector2 *m_point;
        Vector2 m_normal;
        std::vector<PathFinderLineGraphNodeI*> m_connectingNodes;
    };

    /// Path finder graph
    class PathFinderGraphI
    {
    public:
        PathFinderGraphI(std::vector<Polygon> polygons, std::vector<Line> lines)
        : m_polygons(polygons), m_connectingLines(lines) { };
        virtual ~PathFinderGraphI() { };

    public:
        virtual void DistanceToPoint(PathFinderBaseI *sender, std::vector<Polygon> &polygons, Vector2 &startingPoint, Vector2 &targetPoint, std::vector<PathFinderLineGraphNodeI*> *pathStack) = 0;
        std::vector<std::unique_ptr<PathFinderLineGraphNodeI>>& GetNodes() { return m_nodes; };

    protected:
        std::vector<Polygon> m_polygons;
        std::vector<Line> m_connectingLines;
        std::vector<std::unique_ptr<PathFinderLineGraphNodeI>> m_nodes;
    };
};

#endif /* path_finder_interface_h */
