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
    m_light.enabled = m_isEnabled ? 1.f : 0.f;
}

void LightMetal::SetIsEnabled(bool value)
{
    Light::SetIsEnabled(value);
    m_light.enabled = value ? 1.f : 0.f;
}

void LightMetal::SetColor(Color3 color)
{
    Light::SetColor(color);
    m_light.color = { color.r, color.g, color.b };
}

void LightMetal::SetAmbientIntensity(float value)
{
    Light::SetAmbientIntensity(value);
    m_light.ambientIntensity = value;
}

void LightMetal::SetDiffuseIntensity(float value)
{
    Light::SetDiffuseIntensity(value);
    m_light.diffuse_intensity = value;
}

void LightMetal::SetDiffuseSize(float value)
{
    Light::SetDiffuseSize(value);
    m_light.diffuse_size = value;
}

void LightMetal::SetPosition(Origin position)
{
    Light::SetPosition(position);
    m_light.position = { static_cast<float>(position.x), static_cast<float>(position.y) };
}
