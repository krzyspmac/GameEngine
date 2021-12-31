//
//  scene_manager.cpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#include "scene_manager.hpp"

using namespace engine;

Scene* SceneManager::SceneCreateNew()
{
    if (m_currentScene != nullptr)
    {
        SceneUnloadCurrent();
    }
    m_currentScene = std::unique_ptr<Scene>(std::move(new Scene()));
    return m_currentScene.get();
}

void SceneManager::SceneUnloadCurrent()
{
    if (m_currentScene != nullptr)
    {
        m_currentScene.reset();
    }
}

#pragma mark - Scripting

SCRIPTING_INTERFACE_IMPL_NAME(SceneManager);

static int lua_SceneManager_CreateNew(lua_State *L)
{
    SceneManager **ptr = (SceneManager**)luaL_checkudata(
        L, 1, SceneManager::ScriptingInterfaceName().c_str()
    );
    if (ptr == nullptr) { return 0; }
    if (dynamic_cast<SceneManager*>(*ptr) == nullptr) { return 0; }
    Scene *scene = (*ptr)->SceneCreateNew();
    scene->ScriptingInterfaceRegisterFunctions(L, scene);
//    lua_pushlightuserdata(L, scene);
    return 1;
}

static int lua_SceneManager_SceneGetCurrent(lua_State *L)
{
    SceneManager **ptr = (SceneManager**)luaL_checkudata(
        L, 1, SceneManager::ScriptingInterfaceName().c_str()
    );
    if (ptr == nullptr) { return 0; }
    if (dynamic_cast<SceneManager*>(*ptr) == nullptr) { return 0; }
    Scene *scene = (*ptr)->SceneGetCurrent();
    scene->ScriptingInterfaceRegisterFunctions(L, scene);
//    lua_pushlightuserdata(L, scene);
    return 1;
}

static int lua_SceneManager_SceneUnloadCurrent(lua_State *L)
{
    SceneManager **ptr = (SceneManager**)luaL_checkudata(
        L, 1, SceneManager::ScriptingInterfaceName().c_str()
    );
    if (ptr == nullptr) { return 0; }
    if (dynamic_cast<SceneManager*>(*ptr) == nullptr) { return 0; }
    (*ptr)->SceneUnloadCurrent();
    return 0;
}

std::vector<luaL_Reg> SceneManager::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "SceneCreateNew", &lua_SceneManager_CreateNew },
        { "SceneGetCurrent", &lua_SceneManager_SceneGetCurrent },
        { "SceneUnloadCurrent", &lua_SceneManager_SceneUnloadCurrent }
    });
    return result;
}

