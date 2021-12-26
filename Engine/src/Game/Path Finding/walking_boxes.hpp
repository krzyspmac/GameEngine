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
        void Draw();

    private:
        void DrawLine(Vector2 &p1, Vector2 &p2);

    private:
        std::vector<Polygon> m_polygons;
    };
};

#endif /* walking_boxes_hpp */
