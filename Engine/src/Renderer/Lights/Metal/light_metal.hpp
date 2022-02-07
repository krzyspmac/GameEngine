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
        LightMetal(LightFalloutType type, Color3 color, float ambientIntensity, Origin position, float diffuseSize, float diffuseIntensity);

        AAPAmbientLLight& GetLightMetal() { return m_light; };

        void SetType(LightFalloutType);
        void SetIsEnabled(bool);
        void SetColor(Color3);
        void SetAmbientIntensity(float);
        void SetDiffuseIntensity(float);
        void SetDiffuseSize(float);
        void SetPosition(Origin);
    };
};

#endif /* light_metal_hpp */
