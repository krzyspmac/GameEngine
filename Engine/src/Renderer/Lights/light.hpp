//
//  light.hpp
//  Engine-Mac
//
//  Created by krzysp on 05/02/2022.
//

#ifndef light_hpp
#define light_hpp

#include "light_interface.hpp"
#include "scripting_engine_provider_interface.h"

namespace engine
{
    class Light: public LightI
    {
        Color3  m_color;
        float   m_ambientIntensity;
        Origin  m_position;
        float   m_diffuseSize;
        float   m_diffuseIntensity;
    public:
        Light(Color3 color, float ambientIntensity, Origin position, float diffuseSize, float diffuseIntensity)
            : LightI(color, diffuseIntensity, position, diffuseSize, diffuseIntensity)
            , m_color(color)
            , m_ambientIntensity(ambientIntensity)
            , m_position(position)
            , m_diffuseSize(diffuseSize)
            , m_diffuseIntensity(diffuseIntensity)
        { };

    private: /** scripting */
        /** @private */
        SCRIPTING_INTERFACE_HEADERS(Light);
    };
};

#endif /* light_hpp */
