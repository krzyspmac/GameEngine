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

SpriteDrawStatic *Scene::LoadSpriteStatic(SpriteAtlas *atlas, std::string name)
{
    SpriteAtlasItemI *item = atlas->GetItemForName(name);
    if (item != nullptr)
    {
        SpriteDrawStatic *renderer = (SpriteDrawStatic*)GetMainEngine()->getSpriteRendererManager().SpriteDrawLoadStatic(item, 1);
        if (renderer != nullptr)
        {
            AddSpriteDrawStatic(renderer);
            return renderer;
        }
    }
    return nullptr;
}

void Scene::AddSpriteDrawStatic(SpriteDrawStatic *renderer)
{
    m_staticSprites.push_back(renderer);
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

static int lua_Scene_LoadSpriteDrawStatic(lua_State *L)
{
    Scene *scene = ScriptingEngineI::GetScriptingObjectPtr<Scene>(L, 1);
    SpriteAtlas *atlas = ScriptingEngineI::GetScriptingObjectPtr<SpriteAtlas>(L, 2);
    std::string itemName = lua_tostring(L, 3);
    SpriteDrawStatic *sprite = scene->LoadSpriteStatic(atlas, itemName);
    if (sprite != nullptr)
    {
        sprite->ScriptingInterfaceRegisterFunctions(L, sprite);
        return 1;
    }
    else
    {
        return 0;
    }
}

std::vector<luaL_Reg> Scene::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        {"addSpriteDrawStatic", &lua_Scene_AddSpriteDrawStatic},
        {"LoadSpriteStatic", &lua_Scene_LoadSpriteDrawStatic}
    });
    return result;
}
