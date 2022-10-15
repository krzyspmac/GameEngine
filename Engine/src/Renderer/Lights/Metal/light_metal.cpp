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

void LightMetal::SetType(LightFalloffType type)
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
