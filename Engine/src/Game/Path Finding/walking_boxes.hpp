//
//  walking_boxes.hpp
//  Engine
//
//  Created by krzysp on 26/12/2021.
//

#ifndef walking_boxes_hpp
#define walking_boxes_hpp

#include "polygon.hpp"

namespace engine
{

    class WalkingBoxes
    {
    public:
        WalkingBoxes(std::vector<Polygon> polygonList);

    public:
        void Prepare();
        void Draw();

    public:
        void CalculatePathTo(Vector2 fromPoint, Vector2 toPoint);
        void DidStart(float initialDistance);
        void DidFind();

    private:
        bool IntersectsAnyline(Line &line);
        void DrawLine(Line&);
        void DrawPoint(Vector2&);

    public:
        std::vector<Polygon> m_polygons;
        std::vector<Line> m_connectionLines;
        std::vector<Vector2> m_points;
        std::vector<Line> m_path;

        std::vector<Vector2> m_allPoint;
        std::vector<Line> m_allLines;

        void *m_lineGraph;
        void *m_pathStack;

        std::vector<std::vector<void*>> m_arrayOfNodesArray;
    };
};

#endif /* walking_boxes_hpp */
