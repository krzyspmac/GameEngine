//
//  polygon.hpp
//  Engine
//
//  Created by krzysp on 26/12/2021.
//

#ifndef polygon_hpp
#define polygon_hpp

#include <common.h>
#include "common_engine_impl.h"
#include <iostream>

namespace engine
{

    class Polygon
    {
    public:
        Polygon(std::vector<Vector2> list) : m_points(list) { };

        std::vector<Vector2> &GetPoints() { return m_points; };
    private:
        std::vector<Vector2> m_points;
    };
};

#endif /* polygon_hpp */
