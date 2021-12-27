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

    class WalkingBoxes: public PathFinderBaseI
    {
    public:
        WalkingBoxes(std::vector<Polygon> polygonList);

    public:
        void Prepare();
        void Draw();

    public:
        void CalculatePathTo(Vector2 fromPoint, Vector2 toPoint);

    private:
        bool IntersectsAnyline(Line &line);
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
        std::vector<Vector2> m_points;
        std::vector<Line> m_path;

        std::vector<Vector2> m_allPoint;
        std::vector<Line> m_allLines;

        PathFinderGraphI *m_lineGraph;

        std::vector<std::vector<void*>> m_arrayOfNodesArray;
    };
};

#endif /* walking_boxes_hpp */
