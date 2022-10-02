//
//  light_manager.cpp
//  Engine-Mac
//
//  Created by krzysp on 05/02/2022.
//

#include "light_manager.hpp"
#include "defs.h"

#if TARGET_IOS || TARGET_OSX
#include "light_metal.hpp"
#endif

#define MAX_LIGHTS  100

using namespace engine;

LightManager::LightManager()
    : m_lightCache(nullptr)
    , m_lightsActive(true)
{
    m_lightCache = (AAPAmbientLLight*)malloc(sizeof(AAPAmbientLLight) * MAX_LIGHTS);
    m_lightCacheCount = 0;
    UpdateCache();
}

LightManager::~LightManager()
{
    free(m_lightCache);
}

AAPAmbientLLight *LightManager::GetFirstFreeEntry()
{
    size_t nextIndex = std::max(m_lightCacheCount -1 + 1, 0);
    if (nextIndex < MAX_LIGHTS)
    {   return &m_lightCache[nextIndex];
    }
    else
    {   return nullptr;
    }
}

Light *LightManager::CreateLight(LightFalloffType type, Color3 color, float ambientIntensity, Origin position, float diffuseSize, float diffuseIntensity)
{
#if TARGET_OSX || TARGET_IOS
    LightMetal *light = new LightMetal(type, color, ambientIntensity, position, diffuseSize, diffuseIntensity);
    m_lights.emplace_back(std::unique_ptr<Light>(std::move(light)));
    UpdateCache();
    return light;
#else
    return nullptr;
#endif
}

Light *LightManager::CreateLight(std::string type, Color3 color, float ambientIntensity, Origin position, float diffuseSize, float diffuseIntensity)
{
    return CreateLight(LightI::GetFalloutTypeForName(type), color, ambientIntensity, position, diffuseSize, diffuseIntensity);
}

void LightManager::DeleteLight(Light *light)
{
    for (auto it = m_lights.begin(); it != m_lights.end(); ++it)
    {
        if (it->get() == light)
        {
            m_lights.erase(it);
            break;
        }
    }
    UpdateCache();
}

void LightManager::DeleteAllLights()
{
    m_lights.clear();
    UpdateCache();
}

void LightManager::UpdateCache()
{
#if TARGET_IOS || TARGET_OSX
    m_lightCacheCount = 0;
    for (int i = 0; i < m_lights.size(); i++)
    {
        auto* light = m_lights.at(i).get();
        auto* lightMetal = static_cast<LightMetal*>(light);
        auto* buffer = GetFirstFreeEntry();
        lightMetal->SetBuffer(buffer);
        m_lightCacheCount = i + 1;
    }

    m_lightCacheBufferSize = MAX(1, (int)m_lights.size()) * sizeof(AAPAmbientLLight);
#endif
}

void LightManager::SetLightsActive(bool value)
{
    m_lightsActive = value;
}
