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

    private:
        bool IntersectsAnyline(Line &line);
        void DrawLine(Line&);

    private:
        std::vector<Polygon> m_polygons;
        std::vector<Line> m_connectionLines;
    };
};

#endif /* walking_boxes_hpp */
