// Copyright (c) 2022 Krzysztof Pawłowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

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
