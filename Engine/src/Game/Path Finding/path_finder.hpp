//
//  walking_boxes.hpp
//  Engine
//
//  Created by krzysp on 26/12/2021.
//

#ifndef walking_boxes_hpp
#define walking_boxes_hpp

#include "polygon.hpp"
#include "path_finder_interface.h"
#include "path_finder_graph.hpp"

namespace engine
{

    class PathFinder: public PathFinderBaseI
    {
    public:
        PathFinder(std::vector<Polygon> polygonList);
        ~PathFinder();
        
    public:
        void Prepare();
        void Draw();

    public:
        void CalculatePathTo(Vector2 fromPoint, Vector2 toPoint);

    private:
        bool IntersectsAnyline(Line &line);
        bool PointInsidePolygons(Vector2 &point, Polygon **outPolygon);
        void DrawLine(Line&);
        void DrawPoint(Vector2&);

    /// PathFinderCallbackI
    public:
        void DidStart(float initialDistance);
        void DidFind();

    /// PathFinderDataI
    public:
        std::vector<Vector2> &GetAllPoint() { return m_allPoint; };
        std::vector<Line> &GetAllLines() { return m_allLines; };

    private:
        std::vector<Polygon> m_polygons;
        std::vector<Line> m_connectionLines;

        std::vector<Vector2> m_allPoint;
        std::vector<Line> m_allLines;

        // path claculation
        PathFinderGraphI *m_lineGraph;
        Vector2 m_startPosition;
        Vector2 m_targetPosition;
        std::vector<Vector2> m_calculatedPath;
        float m_startingDistance;
        float m_maxDistance;
        std::vector<PathFinderLineGraphNodeI*> m_tempPathStack;
    };
};

#endif /* walking_boxes_hpp */
