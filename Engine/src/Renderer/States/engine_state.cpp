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

Size& EngineState::GetViewportSize()
{
    return GetMainEngine()->GetViewport();
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(EngineState);

static int lua_EngineState_GetViewport(lua_State *L)
{
    EngineState *spr = ScriptingEngineI::GetScriptingObjectPtr<EngineState>(L, 1);
    Size& size = spr->GetViewportSize();
    lua_pushnumber(L, size.width);
    lua_pushnumber(L, size.height);
    return 2;
}

std::vector<luaL_Reg> EngineState::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "GetViewportSize", &lua_EngineState_GetViewport}
    });
    return result;
}
