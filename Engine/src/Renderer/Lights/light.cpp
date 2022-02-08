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

SCRIPTING_INTERFACE_IMPL_NAME(Light);

static int lua_Light_GetEnabled(lua_State *L)
{
    Light *obj = ScriptingEngineI::GetScriptingObjectPtr<Light>(L, 1);
    lua_pushnumber(L, obj->GetIsEnabled());
    return 1;
}

static int lua_Light_SetEnabled(lua_State *L)
{
    Light *obj = ScriptingEngineI::GetScriptingObjectPtr<Light>(L, 1);
    bool value = lua_toboolean(L, 2);
    obj->SetIsEnabled(value);
    return 0;
}

static int lua_Light_GetName(lua_State *L)
{
    Light *obj = ScriptingEngineI::GetScriptingObjectPtr<Light>(L, 1);
    lua_pushstring(L, obj->GetName().c_str());
    return 1;
}

static int lua_Light_SetName(lua_State *L)
{
    Light *obj = ScriptingEngineI::GetScriptingObjectPtr<Light>(L, 1);
    std::string value = lua_tostring(L, 2);
    obj->SetName(value);
    return 0;
}

static int lua_Light_GetColor(lua_State *L)
{
    Light *obj = ScriptingEngineI::GetScriptingObjectPtr<Light>(L, 1);
    auto& ambientColor = obj->GetColor();
    lua_pushnumber(L, ambientColor.r);
    lua_pushnumber(L, ambientColor.g);
    lua_pushnumber(L, ambientColor.b);
    return 3;
}

static int lua_Light_SetColor(lua_State *L)
{
    Light *obj = ScriptingEngineI::GetScriptingObjectPtr<Light>(L, 1);
    float r = lua_tonumber(L, 2);
    float g = lua_tonumber(L, 3);
    float b = lua_tonumber(L, 4);
    obj->SetColor( {r, g, b});
    return 0;
}

static int lua_Light_GetAmbientIntensity(lua_State *L)
{
    Light *obj = ScriptingEngineI::GetScriptingObjectPtr<Light>(L, 1);
    lua_pushnumber(L, obj->GetAmbientIntensity());
    return 1;
}

static int lua_Light_SetAmbientIntensity(lua_State *L)
{
    Light *obj = ScriptingEngineI::GetScriptingObjectPtr<Light>(L, 1);
    float value = lua_tonumber(L, 2);
    obj->SetAmbientIntensity(value);
    return 0;
}

static int lua_Light_GetDiffuseIntensity(lua_State *L)
{
    Light *obj = ScriptingEngineI::GetScriptingObjectPtr<Light>(L, 1);
    lua_pushnumber(L, obj->GetDiffuseIntensity());
    return 1;
}

static int lua_Light_SetDiffuseIntensity(lua_State *L)
{
    Light *obj = ScriptingEngineI::GetScriptingObjectPtr<Light>(L, 1);
    float value = lua_tonumber(L, 2);
    obj->SetDiffuseIntensity(value);
    return 0;
}

static int lua_Light_GetDiffuseSize(lua_State *L)
{
    Light *obj = ScriptingEngineI::GetScriptingObjectPtr<Light>(L, 1);
    lua_pushnumber(L, obj->GetDiffuseSize());
    return 1;
}

static int lua_Light_SetDiffuseSize(lua_State *L)
{
    Light *obj = ScriptingEngineI::GetScriptingObjectPtr<Light>(L, 1);
    float value = lua_tonumber(L, 2);
    obj->SetDiffuseSize(value);
    return 0;
}

static int lua_Light_GetPosition(lua_State *L)
{
    Light *obj = ScriptingEngineI::GetScriptingObjectPtr<Light>(L, 1);
    auto& position = obj->GetPosition();
    lua_pushnumber(L, position.x);
    lua_pushnumber(L, position.y);
    return 2;
}

static int lua_Light_SetPosition(lua_State *L)
{
    Light *obj = ScriptingEngineI::GetScriptingObjectPtr<Light>(L, 1);
    float x = lua_tonumber(L, 2);
    float y = lua_tonumber(L, 3);
    obj->SetPosition({(int)x, (int)y});
    return 0;
}

std::vector<luaL_Reg> Light::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "GetEnabled",             &lua_Light_GetEnabled }
      , { "SetEnabled",             &lua_Light_SetEnabled }
      , { "GetName",                &lua_Light_GetName }
      , { "SetName",                &lua_Light_SetName }
      , { "GetColor",               &lua_Light_GetColor }
      , { "SetColor",               &lua_Light_SetColor }
      , { "GetAmbientIntensity",    &lua_Light_GetAmbientIntensity }
      , { "SetAmbientIntensity",    &lua_Light_SetAmbientIntensity }
      , { "GetDiffuseIntensity",    &lua_Light_GetDiffuseIntensity }
      , { "SetDiffuseIntensity",    &lua_Light_SetDiffuseIntensity }
      , { "GetDiffuseIntensity",    &lua_Light_GetDiffuseIntensity }
      , { "SetDiffuseIntensity",    &lua_Light_SetDiffuseIntensity }
      , { "GetDiffuseSize",         &lua_Light_GetDiffuseSize }
      , { "SetDiffuseSize",         &lua_Light_SetDiffuseSize }
      , { "GetDiffuseSize",         &lua_Light_GetDiffuseSize }
      , { "SetDiffuseSize",         &lua_Light_SetDiffuseSize }
      , { "GetPosition",            &lua_Light_GetPosition }
      , { "SetPosition",            &lua_Light_SetPosition }
    });
    return result;
}
