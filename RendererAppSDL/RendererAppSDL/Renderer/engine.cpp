//
//  engine.cpp
//  RendererApp
//
//  Created by krzysp on 19/12/2021.
//

#include "engine.hpp"

#ifdef __cplusplus
extern "C" {
    #include "../../../Lua/code/src/lua.h"
    #include "../../../Lua/code/src/lualib.h"
    #include "../../../Lua/code/src/lauxlib.h"
}
#endif //__cplusplus

namespace engine
{

Engine::Engine(EngineProviderI &engine, FileAccessI &fileAccess, ScriptingEngineI &scriptingEngine) :
    m_engineProvider(engine), m_fileAccess(fileAccess), m_scriptingEngine(scriptingEngine)
{
    m_scriptingEngine.newState();
    m_scriptingEngine.loadFile("/Users/Shared/Shared Documents/NoBackup/xcode_temporary/Build/Products/Debug/RendererApp.app/Contents/Resources/main.lua");
    m_scriptingEngine.registerFunctions();
}

void Engine::update()
{
    m_scriptingEngine.callUpdate();
}

}

/*
 lua_State* L;
 L = luaL_newstate();
 lua_pushstring(L, "Anna");
 lua_setglobal(L, "name");
 luaL_openlibs(L);
 if(luaL_dofile(L, "hello.lua")) {
 std::cout << "Final:" << lua_tostring(L, -1) << "\n";
 }
 lua_close(L);
 */

/*
 // delete some dangerous functions
 lua_pushnil(L); lua_setglobal(L, "dofile");
 lua_pushnil(L); lua_setglobal(L, "loadfile");
 lua_pushnil(L); lua_setglobal(L, "loadlib");
 lua_pushnil(L); lua_setglobal(L, "loadstring"); // replaced
 lua_pushnil(L); lua_setglobal(L, "require");
 lua_pushnil(L); lua_setglobal(L, "rawequal");
 lua_pushnil(L); lua_setglobal(L, "rawget");
 lua_pushnil(L); lua_setglobal(L, "rawset");
 //    lua_pushnil(L); lua_setglobal(L, "getfenv");
 //    lua_pushnil(L); lua_setglobal(L, "setfenv");
 lua_pushnil(L); lua_setglobal(L, "newproxy");
 lua_pushnil(L); lua_setglobal(L, "gcinfo");
 lua_pushnil(L); lua_setglobal(L, "collectgarbage");

 see https://cpp.hotexamples.com/examples/-/-/lua_setglobal/cpp-lua_setglobal-function-examples.html
 */
