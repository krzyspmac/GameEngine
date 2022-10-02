//
//  light.cpp
//  Engine-Mac
//
//  Created by krzysp on 05/02/2022.
//

#include "light.hpp"
#include "engine.hpp"

using namespace engine;

LightFalloffType Light::GetType()
{
    return m_type;;
}

void Light::SetType(LightFalloffType value)
{
    m_type = value;
}

Color3& Light::GetColor()
{
    return m_color;
}

void Light::SetColor(Color3 value)
{
    m_color = value;
}

float& Light::GetAmbientIntensity()
{
    return m_ambientIntensity;
}

void Light::SetAmbientIntensity(float value)
{
    m_ambientIntensity = value;
}

float& Light::GetDiffuseIntensity()
{
    return m_diffuseIntensity;
}

void Light::SetDiffuseIntensity(float value)
{
    m_diffuseIntensity = value;
}

float& Light::GetDiffuseSize()
{
    return m_diffuseSize;
}

void Light::SetDiffuseSize(float value)
{
    m_diffuseSize = value;
}

Origin& Light::GetPosition()
{
    return m_position;
}

void Light::SetPosition(Origin value)
{
    m_position = value;
}

bool Light::GetIsEnabled()
{
    return m_isEnabled;
}

void Light::SetIsEnabled(bool value)
{
    m_isEnabled = value;
}

std::string& Light::GetName()
{
    return m_name;
}

void Light::SetName(std::string value)
{
    m_name = value;
}
