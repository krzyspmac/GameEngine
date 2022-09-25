//
//  engine.cpp
//  Engine
//
//  Created by krzysp on 01/01/2022.
//

#include "engine_state.hpp"
#include "engine.hpp"
#include "common.h"

using namespace engine;

EngineState::EngineState()
    : m_screenSizeChangeCallback(nullptr)
//    : m_screenSizeChangeHandler(nullptr)
//    , m_screenSizeChangeScriptHandler(CallableScriptFunctionParameters3<float, float, float>::empty())
{

}

Size EngineState::GetViewportSize()
{
    return ENGINE().getProvider().GetDesiredViewport();
}

void EngineState::SetOnScreenSizeChange(void (*callback)(Size, float))
{
    m_screenSizeChangeCallback = callback;
}

//void EngineState::SetOnScreenSizeChange(CallableScriptFunctionParameters3<float, float, float> handler)
//{
//    m_screenSizeChangeScriptHandler = handler;
//}

void EngineState::SendScreenSizeChangeEvent(Size size, float density)
{
//    if (m_screenSizeChangeHandler != nullptr)
//    {
//        m_screenSizeChangeHandler(size, density);
//    }
//
//    if (m_screenSizeChangeScriptHandler.CanCall())
//    {
//        m_screenSizeChangeScriptHandler.CallWithParameters(size.width, size.height, density);
//    }
    if (m_screenSizeChangeCallback != nullptr)
    {
        m_screenSizeChangeCallback(size, density);
    }
}

void EngineState::SetViewportSize(Size size, float scale)
{
    auto& engineSetup = ENGINE().GetEngineSetup();
    engineSetup.resolution.width = size.width;
    engineSetup.resolution.height = size.height;
    engineSetup.affineScale = scale;
    engineSetup.isDirty = true;
}


#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(EngineState);

static int lua_EngineState_GetViewportSize(lua_State *L)
{
    EngineState *spr = ScriptingEngineI::GetScriptingObjectPtr<EngineState>(L, 1);
    Size size = spr->GetViewportSize();
    lua_pushnumber(L, size.width);
    lua_pushnumber(L, size.height);
    return 2;
}

static int lua_EngineState_SetViewportSize(lua_State *L)
{
    EngineState *spr = ScriptingEngineI::GetScriptingObjectPtr<EngineState>(L, 1);
    float width = lua_tonumber(L, 2);
    float height = lua_tonumber(L, 3);
    float scale = lua_tonumber(L, 4);
    spr->SetViewportSize({static_cast<int>(width), static_cast<int>(height)}, scale);
    return 0;
}

static int lua_EngineState_SetOnScreenSizeChange(lua_State *L)
{
    EngineState *obj = ScriptingEngineI::GetScriptingObjectPtr<EngineState>(L, 1);
    int fnRef = luaL_ref( L, LUA_REGISTRYINDEX );
//    obj->SetOnScreenSizeChange(CallableScriptFunctionParameters3<float, float, float>(fnRef));
    return 0;
}

std::vector<luaL_Reg> EngineState::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "GetViewportSize", &lua_EngineState_GetViewportSize}
      , { "SetViewportSize", &lua_EngineState_SetViewportSize}
      , { "SetOnScreenSizeChange", &lua_EngineState_SetOnScreenSizeChange}
    });
    return result;
}
