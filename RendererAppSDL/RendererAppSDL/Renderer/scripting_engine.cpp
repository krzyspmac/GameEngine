//
//  scriptint_engine.cpp
//  RendererApp
//
//  Created by krzysp on 19/12/2021.
//

#include "common.h"
#include "scripting_engine.hpp"

static engine::EngineProviderI *m_curProvider = NULL;

namespace engine
{

ScriptingEngine::ScriptingEngine(EngineProviderI *engineProvider)
{
    this->m_engineProvider = engineProvider;
    m_curProvider = engineProvider;
}

void ScriptingEngine::newState()
{
    this->L = luaL_newstate();
    luaL_openlibs(L);
    luaopen_base(L);
}

void ScriptingEngine::closeState()
{
    lua_close(L);
}

void ScriptingEngine::loadFile(const char *fname)
{
    if(luaL_loadfile(this->L, fname) == 0)
    {
        // Call priming lua_pcall
        int iErr = lua_pcall(L, 0, 0, 0);
        if (iErr != 0)
        {
            std::cout << "Error:" << lua_tostring(L, -1) << "\n";
        }
    }
    else
    {
        std::cout << "Final:" << lua_tostring(L, -1) << "\n";
    }
}

void ScriptingEngine::registerFunctions()
{
    lua_pushcclosure(L, &ScriptingEngine::lua_drawDebugString, 0);
    lua_setglobal (L, "drawDebugText");
};


void ScriptingEngine::callUpdate()
{
    /* push functions and arguments */
    lua_getglobal(L, "update");  /* function to be called */
//    lua_pushnumber(L, 1);   /* push 1st argument */
//    lua_pushnumber(L, 2);   /* push 2nd argument */

    /* do the call (2 arguments, 1 result) */
    if (lua_pcall(L, 0, 0, 0) != 0) {
        std::cout << "Error:" << lua_tostring(L, -1) << "\n";
    }

    /* retrieve result */
//    if (!lua_isnumber(L, -1)) {
//        std::cout << "function `f' must return a number" << "\n";
//    }

//    int z = lua_tonumber(L, -1);
//    lua_pop(L, 1);  /* pop returned value */
}

int ScriptingEngine::lua_drawDebugString(lua_State *lua)
{
    int argc = lua_gettop(lua);

    const char *msgX = (char *) lua_tostring (lua, argc);
    int val = lua_tonumberx(lua, argc-1, NULL);
    int y = lua_tonumberx(lua, argc-2, NULL);
    int x = lua_tonumberx(lua, argc-3, NULL);

//    m_curProvider->DrawDebugText(x, y, val, msgX);
    return 0;
}

};
