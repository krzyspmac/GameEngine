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

using namespace engine;

WalkingBoxes::WalkingBoxes(std::vector<Polygon> polygonList)
: m_polygons(polygonList)
{

}

void WalkingBoxes::Draw()
{
    for (auto it = std::begin(m_polygons); it != std::end(m_polygons); ++it)
    {
        Polygon &polygon = *it;
        std::vector<Vector2> &points = polygon.GetPoints();
        size_t size = points.size();
        if (size < 1)
        {
            continue;
        }

        for (int i = 0; i < size; i++)
        {
            if (i+1 >= size)
            {
                break;
            }

            Vector2 &p1 = points.at(i);
            Vector2 &p2 = points.at(i+1);
            DrawLine(p1, p2);
        }

        Vector2 &first = points.at(0);
        Vector2 &last = points.at(size-1);
        if (!Vector2Equals(first, last))
        {
            DrawLine(last, first);
        }
    }
}

void WalkingBoxes::DrawLine(Vector2 &p1, Vector2 &p2)
{
    EngineProviderI &provider = GetMainEngine()->getProvider();
    provider.RenderDrawLine(p1.x, p1.y, p2.x, p2.y);
}
