//
//  light_metal.hpp
//  Engine-Mac
//
//  Created by krzysp on 05/02/2022.
//

#ifndef light_metal_hpp
#define light_metal_hpp

#include "light.hpp"
#include "common_engine_impl.h"
#include "AAPLShaderTypes.h"

namespace engine
{
    class LightMetal: public Light
    {
        AAPAmbientLLight m_light;
    public:
        LightMetal(Color3 color, float ambientIntensity, Origin position, float diffuseSize, float diffuseIntensity);

        AAPAmbientLLight& GetLightMetal() { return m_light; };
    };
};

#endif /* light_metal_hpp */
