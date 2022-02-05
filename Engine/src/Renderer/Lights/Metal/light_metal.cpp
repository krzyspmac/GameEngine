//
//  light_metal.cpp
//  Engine-Mac
//
//  Created by krzysp on 05/02/2022.
//

#include "light_metal.hpp"

using namespace engine;

LightMetal::LightMetal(Color3 color, float ambientIntensity, Origin position, float diffuseSize, float diffuseIntensity)
    : Light(color, ambientIntensity, position, diffuseSize, diffuseIntensity)
{
    m_light.color = { color.r, color.g, color.b };
    m_light.ambientIntensity = ambientIntensity;
    m_light.position = { static_cast<float>(position.x), static_cast<float>(position.y) };
    m_light.diffuse_size = static_cast<float>(diffuseSize);
    m_light.diffuse_intensity = diffuseIntensity;
}
