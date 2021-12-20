//
//  scriptint_engine.cpp
//  RendererApp
//
//  Created by krzysp on 19/12/2021.
//

#include "common.h"
#include "scripting_engine.hpp"

static engine::EngineI *m_curEngine = NULL;

namespace engine
{

ScriptingEngine::ScriptingEngine()
{
}

void ScriptingEngine::setEngine(EngineI *engine)
{
    m_engine = engine;
    m_curEngine = m_engine;
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

void ScriptingEngine::loadFile(std::string fname)
{
    if(luaL_loadfile(this->L, fname.c_str()) == 0)
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

    lua_pushcclosure(L, &ScriptingEngine::lua_loadTexture, 0);
    lua_setglobal (L, "loadTexture");

    lua_pushcclosure(L, &ScriptingEngine::lua_drawTexture, 0);
    lua_setglobal (L, "drawTexture");
};

void ScriptingEngine::callInit()
{
    lua_getglobal(L, "init");  /* function to be called */
    if (lua_pcall(L, 0, 0, 0) != 0)
    {
        std::cout << "Error:" << lua_tostring(L, -1) << "\n";
    }
}

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

int ScriptingEngine::lua_drawDebugString(lua_State *L)
{
    int argc = lua_gettop(L);

    const char *msgX = (char *) lua_tostring (L, argc);
    int val = lua_tonumberx(L, argc-1, NULL);
    int y = lua_tonumberx(L, argc-2, NULL);
    int x = lua_tonumberx(L, argc-3, NULL);

//    m_curProvider->DrawDebugText(x, y, val, msgX);
    return 0;
}

/// loadTexture(name)
int ScriptingEngine::lua_loadTexture(lua_State *L)
{
    int argc = lua_gettop(L);
    const char *msgX = (char *) lua_tostring (L, argc);

    std::string path = m_curEngine->getFileAccess().getBundledFilepath(msgX);
    TextureI *texture = m_curEngine->LoadTexture(path);
    lua_pushlightuserdata(L, texture);

    return 1;
}

/// drawTexture(texture_handle, x, y)
int ScriptingEngine::lua_drawTexture(lua_State *L)
{
    int argc = lua_gettop(L);
    int y = lua_tonumberx(L, argc-0, NULL);
    int x = lua_tonumberx(L, argc-1, NULL);
    TextureI *texturePointer = (TextureI*)lua_topointer(L, argc-2);

    if (texturePointer != NULL)
    {
        m_curEngine->getProvider().DrawTexture(texturePointer, x, y);
    }

    return 0;
}

};
