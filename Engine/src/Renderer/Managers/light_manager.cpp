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

using namespace engine;

LightManager::LightManager()
    : m_lightCache(nullptr)
    , m_lightsActive(true)
{
    UpdateCache();
}

LightI *LightManager::CreateLight(Color3 color, float ambientIntensity, Origin position, float diffuseSize, float diffuseIntensity)
{
#if TARGET_OSX || TARGET_IOS
    LightMetal *light = new LightMetal(color, ambientIntensity, position, diffuseSize, diffuseIntensity);
    m_lights.emplace_back(std::unique_ptr<LightI>(std::move(light)));
    UpdateCache();
    return light;
#else
    return nullptr;
#endif
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
    if (m_lightCache != nullptr)
    {
        delete m_lightCache;
        m_lightCache = nullptr;
    }

    m_lightCacheBufferSize = MAX(1, (int)m_lights.size()) * sizeof(AAPAmbientLLight);
    m_lightCache = (AAPAmbientLLight*)malloc(m_lightCacheBufferSize);

    int counter = 0;
    for (auto& baseLight : m_lights)
    {
        auto& metalLight = static_cast<LightMetal&>(*baseLight);
        auto& lightDescriptor = metalLight.GetLightMetal();
        memcpy(&m_lightCache[counter++], &lightDescriptor, sizeof(lightDescriptor));
    }

    m_lightCacheCount = (int)m_lights.size();

#endif
}

#pragma mark - Scripting Interface
/** Scripting interface */

SCRIPTING_INTERFACE_IMPL_NAME(LightManager);

static int lua_LightManager_CreateLight(lua_State *L)
{
    LightManager *mgr = ScriptingEngineI::GetScriptingObjectPtr<LightManager>(L, 1);
    float r = lua_tonumber(L, 2);
    float g = lua_tonumber(L, 3);
    float b = lua_tonumber(L, 4);
    float ambientIntensity = lua_tonumber(L, 5);
    int posX = lua_tonumber(L, 6);
    int posY = lua_tonumber(L, 7);
    float diffuseSize = lua_tonumber(L, 8);
    float diffuseIntensity = lua_tonumber(L, 9);

    auto *light = (Light*)mgr->CreateLight({r, g, b}, ambientIntensity, {posX, posY}, diffuseSize, diffuseIntensity);
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
