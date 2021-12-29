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
        PathI *CalculatePath(Vector2 fromPoint, Vector2 toPoint);
        Vector2 NudgedPosition(Vector2 position);

    private:
        bool IntersectsAnyline(Line &line);
        bool PointInsidePolygons(Vector2 &point, Polygon **outPolygon);
        void DrawLine(Line&);
        void DrawPoint(Vector2&);

    /// PathFinderCallbackI
    public:
        void DidFindPath(std::unique_ptr<PathI>&);

    /// PathFinderDataI
    public:
        std::vector<Vector2> &GetAllPoint() { return m_allPoints; };
        std::vector<Line> &GetAllLines() { return m_allLines; };

    private:
        std::vector<Polygon> m_polygons;
        std::vector<Line> m_connectionLines;

        std::vector<Vector2> m_allPoints;
        std::vector<Line> m_allLines;

        // path claculation
        std::unique_ptr<PathFinderGraphI> m_lineGraph;
        Vector2 m_startPosition;
        Vector2 m_targetPosition;
        std::vector<PathFinderLineGraphNodeI*> m_tempPathStack;
        float m_maxDistance;
        std::unique_ptr<PathI> m_calculatedPath;

        // tmp
        Line *m_nudgedLine;
        Vector2 m_nudgedPosition;
    };
};

#endif /* walking_boxes_hpp */
