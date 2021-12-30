//
//  scene.cpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#include "scene.hpp"

using namespace engine;

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::AddSpriteDrawStatic(SpriteDrawStatic *renderer)
{
    m_staticSprites.push_back(renderer);
}

void Scene::AddSpriteDrawAnimated(SpriteDrawAnimated *renderer)
{

}

void Scene::RenderScene()
{
    for (auto it = m_staticSprites.begin(); it != m_staticSprites.end(); ++it)
    {
        (*it)->Draw(0, 0);
    };
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(Scene);

static int lua_Scene_AddSpriteDrawStatic(lua_State *L)
{
    Scene **ptr = (Scene**)luaL_checkudata(
        L, 1, Scene::ScriptingInterfaceName().c_str()
    );
    if (ptr != nullptr && dynamic_cast<Scene*>(*ptr) == nullptr) { return 0; }

    SpriteDrawStatic *sprite = (SpriteDrawStatic*)lua_topointer(L, 2);
    if (sprite != nullptr && dynamic_cast<SpriteDrawStatic*>(sprite) == nullptr) { return 0; }

    (*ptr)->AddSpriteDrawStatic(sprite);

    return 0;
}

std::vector<luaL_Reg> Scene::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        {"addSpriteDrawStatic", &lua_Scene_AddSpriteDrawStatic}
    });
    return result;
}
