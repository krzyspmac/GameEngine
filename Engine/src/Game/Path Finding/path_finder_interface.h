//
//  path_finding_interface.h
//  Engine
//
//  Created by krzysp on 27/12/2021.
//

#ifndef path_finder_interface_h
#define path_finder_interface_h

#include <iostream>
#include "common_engine_impl.h"
#include "path_finder_line.hpp"

namespace engine
{
    /// Path finder callbacks
    class PathFinderCallbackI
    {
    public:
        virtual void DidStart(float initialDistance) = 0;
        virtual void DidFind() = 0;
    };

    /// Path finder data accessors
    class PathFinderDataI
    {
    public:
        virtual std::vector<Vector2> &GetAllPoint() = 0;
        virtual std::vector<Line> &GetAllLines() = 0;
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
        PathFinderLineGraphNodeI(Vector2 *point): m_point(point) { };
        virtual ~PathFinderLineGraphNodeI() { };
        
    public:
        ///
        Vector2 *GetPoint() { return m_point; };

        ///
        virtual void AddConnection(PathFinderLineGraphNodeI *node) = 0;

        ///
        virtual std::vector<PathFinderLineGraphNodeI*>& GetConnections() = 0;

        ///
        virtual bool HasConnectionWithPoint(Vector2 *point) = 0;

        /// Calcultes the distance from a target point all they way
        /// through all the connecting points.
        virtual void DistanceToPoint(PathFinderBaseI *sender, Vector2 &targetPoint, std::vector<PathFinderLineGraphNodeI*> *pathStack) = 0;

    protected:
        Vector2 *m_point;
        std::vector<PathFinderLineGraphNodeI*> m_connectingNodes;
    };

    /// Path finder graph
    class PathFinderGraphI
    {
    public:
        PathFinderGraphI(std::vector<Line> lines): m_connectingLines(lines) { };
        virtual ~PathFinderGraphI() { };

    public:
        virtual void DistanceToPoint(PathFinderBaseI *sender, Vector2 &startingPoint, Vector2 &targetPoint, std::vector<PathFinderLineGraphNodeI*> *pathStack) = 0;
        std::vector<std::unique_ptr<PathFinderLineGraphNodeI>>& GetNodes() { return m_nodes; };

    protected:
        std::vector<Line> m_connectingLines;
        std::vector<std::unique_ptr<PathFinderLineGraphNodeI>> m_nodes;
    };
};

#endif /* path_finder_interface_h */
