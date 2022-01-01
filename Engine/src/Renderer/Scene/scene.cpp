//
//  scene.cpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#include "scene.hpp"
#include "scripting_engine.hpp"
#include "character.hpp"
#include "scripting_engine.hpp"

using namespace engine;

Scene::Scene()
: m_mainCharacter(nullptr), m_mouseDownFunctionName("")
{
    GetMainEngine()->getEventsManager().RegisterMouseClickedEvents(EventHolderMouseClicked([&](void *mouse){
        Origin *clicked = (Origin*)mouse;
        Vector2 pos;
        pos.x = (*clicked).x;
        pos.y = (*clicked).y;

        MouseClicked(pos);
//        Vector2 pos = ->GetCharacterPosition();
//        Vector2 from = Vector2Make(pos.x, pos.y);
//        PathI *path = m_walkingBoxes->CalculatePath(from, Vector2Make(m_mousePosition.x, m_mousePosition.y));
//        m_characterMover->MoveCharacterAlongPath(path);
    }));
}

Scene::~Scene()
{

}

void Scene::MouseClicked(Vector2 pos)
{
    if (m_mainCharacter != nullptr)
    {
        m_mainCharacter->WalkTo(pos);
    }

    if (!m_mouseDownFunctionName.empty())
    {
        lua_State *L = ((ScriptingEngine&)GetMainEngine()->getScripting()).GetL();
        lua_getglobal(L, m_mouseDownFunctionName.c_str());  /* function to be called */
        lua_pushnumber(L, pos.x);
        lua_pushnumber(L, pos.y);
        if (lua_pcall(L, 2, 0, 0) != 0)
        {
            std::cout << "Error:" << lua_tostring(L, -1) << "\n";
        }
    }
}

void Scene::SetMainCharacter(CharacterRepresentation *rep)
{
    m_mainCharacter = rep;
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

void Scene::SetMouseDownFunction(std::string functionName)
{
    m_mouseDownFunctionName = functionName;
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

static int lua_Scene_SetMainCharacter(lua_State *L)
{
    Scene *scene = ScriptingEngineI::GetScriptingObjectPtr<Scene>(L, 1);
    CharacterRepresentation *chr = ScriptingEngineI::GetScriptingObjectPtr<CharacterRepresentation>(L, 2);
    scene->SetMainCharacter(chr);
    return 0;
}

static int lua_Scene_SetMouseDownFunction(lua_State *L)
{
    Scene *scene = ScriptingEngineI::GetScriptingObjectPtr<Scene>(L, 1);
    const char *functionName = lua_tostring(L, 2);
    scene->SetMouseDownFunction(functionName);
    return 0;
}

std::vector<luaL_Reg> Scene::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        {"AddSpriteDrawStatic", &lua_Scene_AddSpriteDrawStatic},
        {"LoadSpriteStatic", &lua_Scene_LoadSpriteDrawStatic},
        {"LoadCharacter", &lua_Scene_LoadCharacter},
        {"SetMainCharacter", &lua_Scene_SetMainCharacter},
        {"SetMouseDownFunction", &lua_Scene_SetMouseDownFunction}
    });
    return result;
}
