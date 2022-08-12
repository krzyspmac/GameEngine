//
//  engine_screen.cpp
//  Engine-Mac
//
//  Created by krzysp on 12/08/2022.
//

#include "engine_screen.hpp"

using namespace engine;

EngineScreen::EngineScreen()
    : m_offset({0.0f, 0.0f})
{
}

void EngineScreen::SetScreenOffset(Vector2 position)
{
    m_offset = position;
}

SCRIPTING_INTERFACE_IMPL_NAME(EngineScreen);

static int lua_SetOffset(lua_State *L)
{
    EngineScreen *obj = ScriptingEngineI::GetScriptingObjectPtr<EngineScreen>(L, 1);
    float x = lua_tonumber(L, 2);
    float y = lua_tonumber(L, 2);
    obj->SetScreenOffset({x, y});
    return 0;
}

std::vector<luaL_Reg> EngineScreen::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "SetOffset",      &lua_SetOffset}
    });
    return result;
}
