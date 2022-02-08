//
//  light_metal.cpp
//  Engine-Mac
//
//  Created by krzysp on 05/02/2022.
//

#include "light_metal.hpp"

using namespace engine;

void LightMetal::SetBuffer(AAPAmbientLLight *buffer)
{
    if (buffer == nullptr)
    {   return;
    }

    auto type = GetType();
    auto color = GetColor();
    auto ambientIntensity = GetAmbientIntensity();
    auto position = GetPosition();
    auto diffuseSize = GetDiffuseSize();
    auto diffuseIntensity = GetDiffuseIntensity();
    auto isEnabled = GetIsEnabled();

    buffer->lightType = (float)type;
    buffer->color = { color.r, color.g, color.b };
    buffer->ambientIntensity = ambientIntensity;
    buffer->position = { static_cast<float>(position.x), static_cast<float>(position.y) };
    buffer->diffuse_size = static_cast<float>(diffuseSize);
    buffer->diffuse_intensity = diffuseIntensity;
    buffer->enabled = isEnabled ? 1.f : 0.f;

    m_light = buffer;
}

void LightMetal::SetType(LightFalloutType type)
{
    Light::SetType(type);
    m_light->lightType = (float)type;
}

void LightMetal::SetIsEnabled(bool value)
{
    Light::SetIsEnabled(value);
    m_light->enabled = value ? 1.f : 0.f;
}

void LightMetal::SetColor(Color3 color)
{
    Light::SetColor(color);
    m_light->color = { color.r, color.g, color.b };
}

void LightMetal::SetAmbientIntensity(float value)
{
    Light::SetAmbientIntensity(value);
    m_light->ambientIntensity = value;
}

void LightMetal::SetDiffuseIntensity(float value)
{
    Light::SetDiffuseIntensity(value);
    m_light->diffuse_intensity = value;
}

void LightMetal::SetDiffuseSize(float value)
{
    Light::SetDiffuseSize(value);
    m_light->diffuse_size = value;
}

void LightMetal::SetPosition(Origin position)
{
    Light::SetPosition(position);
    m_light->position = { static_cast<float>(position.x), static_cast<float>(position.y) };
}
