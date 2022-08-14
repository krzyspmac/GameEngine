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
    m_scenes.emplace_back(std::unique_ptr<Scene>(std::move(new Scene())));
    return m_scenes.at(m_scenes.size()-1).get();
}

void SceneManager::SceneUnload(Scene *scene)
{
    auto existing = GetFor(scene);
    if (existing != m_scenes.end())
    {   m_scenes.erase(existing);
    }
    m_current = nullptr;
}

void SceneManager::SceneMakeActive(Scene* scene)
{
    auto existing = GetFor(scene);
    if (existing != m_scenes.end())
    {   m_current = existing->get();
        if (m_current != nullptr)
        {   for (auto it = std::begin(m_scenes); it != std::end(m_scenes); it++)
            {   it->get()->SetIsActivated(false);
            }
            m_current->SetIsActivated(true);
        }
    }
}

std::vector<std::unique_ptr<Scene>>::iterator SceneManager::GetFor(Scene* scene)
{
    for (auto it = m_scenes.begin(); it != m_scenes.end(); it++)
    {   if (it->get() == scene)
        {   return it;
        }
    }

    return m_scenes.end();
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

static int lua_SceneManager_SceneUnload(lua_State *L)
{
    SceneManager **ptr = (SceneManager**)luaL_checkudata(
        L, 1, SceneManager::ScriptingInterfaceName().c_str()
    );
    Scene **scene = (Scene**)luaL_checkudata(
        L, 2, Scene::ScriptingInterfaceName().c_str()
    );
    if (ptr == nullptr) { return 0; }
    if (dynamic_cast<SceneManager*>(*ptr) == nullptr) { return 0; }
    (*ptr)->SceneUnload(*scene);
    return 0;
}

static int lua_SceneManager_SceneMakeActive(lua_State *L)
{
    SceneManager **ptr = (SceneManager**)luaL_checkudata(
        L, 1, SceneManager::ScriptingInterfaceName().c_str()
    );
    Scene **scene = (Scene**)luaL_checkudata(
        L, 2, Scene::ScriptingInterfaceName().c_str()
    );
    if (ptr == nullptr) { return 0; }
    if (dynamic_cast<SceneManager*>(*ptr) == nullptr) { return 0; }
    (*ptr)->SceneMakeActive(*scene);
    return 0;
}

std::vector<luaL_Reg> SceneManager::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "SceneCreateNew", &lua_SceneManager_CreateNew },
        { "SceneGetCurrent", &lua_SceneManager_SceneGetCurrent },
        { "SceneUnload", &lua_SceneManager_SceneUnload },
        { "SceneMakeActive", &lua_SceneManager_SceneMakeActive}
    });
    return result;
}

