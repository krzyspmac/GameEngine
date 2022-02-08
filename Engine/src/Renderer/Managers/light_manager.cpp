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

LightI *LightManager::CreateLight(LightFalloutType type, Color3 color, float ambientIntensity, Origin position, float diffuseSize, float diffuseIntensity)
{
#if TARGET_OSX || TARGET_IOS
    LightMetal *light = new LightMetal(type, color, ambientIntensity, position, diffuseSize, diffuseIntensity);
    m_lights.emplace_back(std::unique_ptr<LightI>(std::move(light)));
    UpdateCache();
    return light;
#else
    return nullptr;
#endif
}

LightI *LightManager::CreateLight(std::string type, Color3 color, float ambientIntensity, Origin position, float diffuseSize, float diffuseIntensity)
{
    return CreateLight(LightI::GetFalloutTypeForName(type), color, ambientIntensity, position, diffuseSize, diffuseIntensity);
}

void LightManager::DeleteLight(LightI *light)
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

#pragma mark - Scripting Interface
/** Scripting interface */

SCRIPTING_INTERFACE_IMPL_NAME(LightManager);

static int lua_LightManager_CreateLight(lua_State *L)
{
    LightManager *mgr = ScriptingEngineI::GetScriptingObjectPtr<LightManager>(L, 1);

    std::string type = lua_tostring(L, 2);
    float r = lua_tonumber(L, 3);
    float g = lua_tonumber(L, 4);
    float b = lua_tonumber(L, 5);
    float ambientIntensity = lua_tonumber(L, 6);
    int posX = lua_tonumber(L, 7);
    int posY = lua_tonumber(L, 8);
    float diffuseSize = lua_tonumber(L, 9);
    float diffuseIntensity = lua_tonumber(L, 10);

    auto *light = (Light*)mgr->CreateLight(type, {r, g, b}, ambientIntensity, {posX, posY}, diffuseSize, diffuseIntensity);
    light->ScriptingInterfaceRegisterFunctions(L, light);
    return 1;
}

static int lua_LightManager_DeleteLight(lua_State *L)
{
    LightManager *mgr = ScriptingEngineI::GetScriptingObjectPtr<LightManager>(L, 1);
    Light *light = ScriptingEngineI::GetScriptingObjectPtr<Light>(L, 2);
    mgr->DeleteLight(light);
    return 0;
}

static int lua_LightManager_DeleteAllLight(lua_State *L)
{
    LightManager *mgr = ScriptingEngineI::GetScriptingObjectPtr<LightManager>(L, 1);
    mgr->DeleteAllLights();
    return 0;
}

std::vector<luaL_Reg> LightManager::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        {"CreateLight", &lua_LightManager_CreateLight}
      , {"DeleteLight", &lua_LightManager_DeleteLight}
      , {"DeleteAllLights", &lua_LightManager_DeleteAllLight},
    });
    return result;
}
