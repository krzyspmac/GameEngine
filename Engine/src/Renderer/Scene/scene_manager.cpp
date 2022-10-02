// Copyright (c) 2022 Krzysztof Pawłowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

#include "scene_manager.hpp"
#include "scene.hpp"

using namespace engine;

SceneI* SceneManager::SceneCreateNew()
{
    m_scenes.emplace_back(std::unique_ptr<SceneI>(std::move(new Scene())));
    return m_scenes.at(m_scenes.size()-1).get();
}

void SceneManager::SceneUnload(SceneI *scene)
{
    auto existing = GetFor(scene);
    if (existing != m_scenes.end())
    {   m_scenes.erase(existing);
    }
    m_current = nullptr;
}

void SceneManager::SceneMakeActive(SceneI* scene)
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

std::vector<std::unique_ptr<SceneI>>::iterator SceneManager::GetFor(SceneI* scene)
{
    for (auto it = m_scenes.begin(); it != m_scenes.end(); it++)
    {   if (it->get() == scene)
        {   return it;
        }
    }

    return m_scenes.end();
}

SceneI* SceneManager::SceneGetCurrent()
{
    return m_current;
}

//#pragma mark - Scripting
//
//SCRIPTING_INTERFACE_IMPL_NAME(SceneManager);
//
//static int lua_SceneManager_CreateNew(lua_State *L)
//{
//    SceneManager **ptr = (SceneManager**)luaL_checkudata(
//        L, 1, SceneManager::ScriptingInterfaceName().c_str()
//    );
//    if (ptr == nullptr) { return 0; }
//    if (dynamic_cast<SceneManager*>(*ptr) == nullptr) { return 0; }
//    Scene *scene = (*ptr)->SceneCreateNew();
//    scene->ScriptingInterfaceRegisterFunctions(L, scene);
////    lua_pushlightuserdata(L, scene);
//    return 1;
//}
//
//static int lua_SceneManager_SceneGetCurrent(lua_State *L)
//{
//    SceneManager **ptr = (SceneManager**)luaL_checkudata(
//        L, 1, SceneManager::ScriptingInterfaceName().c_str()
//    );
//    if (ptr == nullptr) { return 0; }
//    if (dynamic_cast<SceneManager*>(*ptr) == nullptr) { return 0; }
//    Scene *scene = (*ptr)->SceneGetCurrent();
//    scene->ScriptingInterfaceRegisterFunctions(L, scene);
////    lua_pushlightuserdata(L, scene);
//    return 1;
//}
//
//static int lua_SceneManager_SceneUnload(lua_State *L)
//{
//    SceneManager **ptr = (SceneManager**)luaL_checkudata(
//        L, 1, SceneManager::ScriptingInterfaceName().c_str()
//    );
//    Scene **scene = (Scene**)luaL_checkudata(
//        L, 2, Scene::ScriptingInterfaceName().c_str()
//    );
//    if (ptr == nullptr) { return 0; }
//    if (dynamic_cast<SceneManager*>(*ptr) == nullptr) { return 0; }
//    (*ptr)->SceneUnload(*scene);
//    return 0;
//}
//
//static int lua_SceneManager_SceneMakeActive(lua_State *L)
//{
//    SceneManager **ptr = (SceneManager**)luaL_checkudata(
//        L, 1, SceneManager::ScriptingInterfaceName().c_str()
//    );
//    Scene **scene = (Scene**)luaL_checkudata(
//        L, 2, Scene::ScriptingInterfaceName().c_str()
//    );
//    if (ptr == nullptr) { return 0; }
//    if (dynamic_cast<SceneManager*>(*ptr) == nullptr) { return 0; }
//    (*ptr)->SceneMakeActive(*scene);
//    return 0;
//}
//
//std::vector<luaL_Reg> SceneManager::ScriptingInterfaceFunctions()
//{
//    std::vector<luaL_Reg> result({
//        { "SceneCreateNew", &lua_SceneManager_CreateNew },
//        { "SceneGetCurrent", &lua_SceneManager_SceneGetCurrent },
//        { "SceneUnload", &lua_SceneManager_SceneUnload },
//        { "SceneMakeActive", &lua_SceneManager_SceneMakeActive}
//    });
//    return result;
//}
//
