//
//  light_interface.hpp
//  Engine
//
//  Created by krzysp on 05/02/2022.
//

#ifndef light_interface_h
#define light_interface_h

#include "common_engine_impl.h"

namespace engine
{
    class LightI
    {
    public:
        LightI(Color3 color, float ambientIntensity, Origin position, float diffuseSize, float diffuseIntensity) { };

    };
};

#endif /* light_interface_h */
