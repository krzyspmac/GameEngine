//
//  scene.cpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#include "scene.hpp"
#include "scripting_engine.hpp"
#include "character.hpp"

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
        SpriteDrawStatic *renderer = (SpriteDrawStatic*)GetMainEngine()->getSpriteRendererManager().SpriteDrawLoadStatic(item);
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

CharacterRepresentation *Scene::LoadCharacter(std::string jsonFilename)
{
    CharacterRepresentation *rep = GetMainEngine()->getCharacterManager().LoadCharacter(jsonFilename);
    m_characterRepresentations.emplace_back(rep);
    return rep;
}

void Scene::RenderScene()
{
    for (auto it = m_staticSprites.begin(); it != m_staticSprites.end(); ++it)
    {
        (*it)->DrawAt(0, 0);
    };

    for (auto it = m_characterRepresentations.begin(); it != m_characterRepresentations.end(); ++it)
    {
        (*it)->Render();
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

static int lua_Scene_LoadCharacter(lua_State *L)
{
    Scene *scene = ScriptingEngineI::GetScriptingObjectPtr<Scene>(L, 1);
    std::string jsonFilename = lua_tostring(L, 2);
    CharacterRepresentation *character = (CharacterRepresentation*)scene->LoadCharacter(jsonFilename);
    if (character == nullptr) { return 0; }
    character->ScriptingInterfaceRegisterFunctions(L, character);
    return 1;
}

std::vector<luaL_Reg> Scene::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        {"AddSpriteDrawStatic", &lua_Scene_AddSpriteDrawStatic},
        {"LoadSpriteStatic", &lua_Scene_LoadSpriteDrawStatic},
        {"LoadCharacter", &lua_Scene_LoadCharacter}
    });
    return result;
}
