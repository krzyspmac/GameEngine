//
//  scene.cpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#include "scene.hpp"
#include "scripting_engine.hpp"

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

#define SCRIPTING_GET_OBJECT_PTR (class)

SCRIPTING_INTERFACE_IMPL_NAME(Scene);

static int lua_Scene_AddSpriteDrawStatic(lua_State *L)
{
    Scene *scene = ScriptingEngineI::GetScriptingObjectPtr<Scene>(L, 1);
    SpriteDrawStatic *sprite = ScriptingEngineI::GetScriptingObjectPtr<SpriteDrawStatic>(L, 2);
    scene->AddSpriteDrawStatic(sprite);
    return 0;
}

std::vector<luaL_Reg> Scene::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        {"addSpriteDrawStatic", &lua_Scene_AddSpriteDrawStatic}
    });
    return result;
}
