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
#include "light.hpp"
#include "font_bitmap.hpp"

using namespace engine;

Scene::Scene()
    : m_mainCharacter(nullptr)
    , m_mouseDownFunctionRef(-1)
    , m_engineProvider(ENGINE().getProvider())
    , m_isActive(false)
{
    ENGINE().getEventsManager().RegisterMouseClickedEvents([&](void *mouse){
        Origin *clicked = (Origin*)mouse;
        Vector2 pos;
        pos.x = (*clicked).x;
        pos.y = (*clicked).y;

        MouseClicked(pos);
    });
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

    if (m_mouseDownFunctionRef > -1)
    {
        ScriptingEngine& se = (ScriptingEngine&)ENGINE().getScripting();
        se.CallRegistryFunction(m_mouseDownFunctionRef, [&](lua_State *L){
            lua_pushnumber(L, pos.x);
            lua_pushnumber(L, pos.y);
            return 2;
        });
    }
}

void Scene::SetMainCharacter(CharacterRepresentation *rep)
{
    m_mainCharacter = rep;
}

SpriteRepresentationStatic *Scene::SpriteStaticLoad(SpriteAtlasI *atlas, std::string name)
{
    SpriteAtlasItemI *item = atlas->GetItemForName(name);
    if (item != nullptr)
    {
        SpriteRepresentationStatic *renderer = (SpriteRepresentationStatic*)ENGINE().getSpriteRendererManager().SpriteRepresentationStaticLoad(item);
        if (renderer != nullptr)
        {
            SpriteStaticAdd(renderer);
            return renderer;
        }
    }
    return nullptr;
}

SpriteRepresentationAnimated *Scene::SpriteAnimatedLoad(float keyframeAnimationDelay, SpriteAtlasI *atlas)
{
    if (atlas != nullptr)
    {
        SpriteRepresentationAnimated *renderer = (SpriteRepresentationAnimated*)ENGINE().getSpriteRendererManager().SpriteRepresentationAnimatedLoad(keyframeAnimationDelay, atlas);
        if (renderer != nullptr)
        {
            SpriteAnimatedAdd(renderer);
            return renderer;
        }
    }
    return nullptr;
}

SpriteRepresentationText *Scene::SpriteTextLoad(FontI *font)
{
    if (font != nullptr)
    {   auto *rep = (SpriteRepresentationText*)ENGINE().getSpriteRendererManager().SpriteRepresentationTextLoad(font);
        if (rep != nullptr)
        {   SpriteTextAdd(rep);
            return rep;
        }
    }

    return nullptr;
}

void Scene::SpriteStaticAdd(SpriteRepresentationStatic *renderer)
{
    m_staticSprites.push_back(renderer);
}

void Scene::SpriteAnimatedAdd(SpriteRepresentationAnimated *renderer)
{
    m_animatedSprites.push_back(renderer);
}

void Scene::SpriteTextAdd(SpriteRepresentationText *renderer)
{
    m_textSprites.push_back(renderer);
}

CharacterRepresentation *Scene::LoadCharacter(std::string jsonFilename)
{
    CharacterRepresentation *rep = ENGINE().getCharacterManager().LoadCharacter(jsonFilename);
    m_characterRepresentations.emplace_back(rep);
    return rep;
}

void Scene::SetMouseDownFunction(int mouseFunctionRef)
{
    m_mouseDownFunctionRef = mouseFunctionRef;
}

void Scene::RenderSceneBackground()
{
    for (auto it = m_staticSprites.begin(); it != m_staticSprites.end(); ++it)
    {
        SpriteRepresentationI *sprite = (*it);
        if (sprite->GetType() != SPRITE_DRAW_TYPE_BACKGROUND)
        {
            continue;
        }

        Vector2& pos = sprite->GetPosition();
        (*it)->DrawAt(pos.x, pos.y);
    };
}

void Scene::RenderSceneForeground()
{
    for (auto it = m_staticSprites.begin(); it != m_staticSprites.end(); ++it)
    {
        SpriteRepresentationI *sprite = (*it);
        if (sprite->GetType() != SPRITE_DRAW_TYPE_FOREGROUND)
        {
            continue;
        }

        Vector2& pos = sprite->GetPosition();
        (*it)->DrawAt(pos.x, pos.y);
    };

    for (auto* item : m_animatedSprites)
    {
        if (item->GetType() != SPRITE_DRAW_TYPE_FOREGROUND)
        {
            continue;
        }
        Vector2& pos = item->GetPosition();
        item->DrawAt(pos.x, pos.y);
    }

    for (auto it = m_characterRepresentations.begin(); it != m_characterRepresentations.end(); ++it)
    {
        (*it)->Render();
    };

    for (auto *textRep : m_textSprites)
    {
        textRep->Draw();
    }
}

LightI* Scene::CreateLight(std::string type, Color3 color, float ambientIntensity, Origin position, float diffuseSize, float diffuseIntensity)
{
    auto* light = ENGINE().getLightMnaager().CreateLight(type, color, ambientIntensity, position, diffuseSize, diffuseIntensity);
    if (light != nullptr)
    {
        m_lights.emplace_back(light);
        return light;
    }
    else
    {
        return nullptr;
    }
}

#pragma mark - Scripting Interface

#define SCRIPTING_GET_OBJECT_PTR (class)

SCRIPTING_INTERFACE_IMPL_NAME(Scene);

static int lua_Scene_AddSpriteDrawStatic(lua_State *L)
{
    Scene *scene = ScriptingEngineI::GetScriptingObjectPtr<Scene>(L, 1);
    SpriteRepresentationStatic *sprite = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationStatic>(L, 2);
    scene->SpriteStaticAdd(sprite);
    return 0;
}

static int lua_Scene_LoadSpriteDrawStatic(lua_State *L)
{
    Scene *scene = ScriptingEngineI::GetScriptingObjectPtr<Scene>(L, 1);
    SpriteAtlas *atlas = ScriptingEngineI::GetScriptingObjectPtr<SpriteAtlas>(L, 2);
    std::string itemName = lua_tostring(L, 3);
    SpriteRepresentationStatic *sprite = scene->SpriteStaticLoad(atlas, itemName);
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

static int lua_Scene_SpriteAnimatedLoad(lua_State *L)
{
    Scene *scene = ScriptingEngineI::GetScriptingObjectPtr<Scene>(L, 1);
    float keyframeDelayMs = lua_tonumber(L, 2);
    SpriteAtlas *atlas = ScriptingEngineI::GetScriptingObjectPtr<SpriteAtlas>(L, 3);

    SpriteRepresentationAnimated *representation = scene->SpriteAnimatedLoad(keyframeDelayMs, atlas);
    if (representation != nullptr)
    {   representation->ScriptingInterfaceRegisterFunctions(L, representation);
        return 1;
    }
    else
    {   return 0;
    }
}

static int lua_Scene_SpriteTextLoad(lua_State *L)
{
    Scene *scene = ScriptingEngineI::GetScriptingObjectPtr<Scene>(L, 1);
    FontBitmapRepresentation *font = ScriptingEngineI::GetScriptingObjectPtr<FontBitmapRepresentation>(L, 2);
    auto *sprite = scene->SpriteTextLoad(font);
    if (sprite != nullptr)
    {   sprite->ScriptingInterfaceRegisterFunctions(L, sprite);
        return 1;
    }
    else
    {   return 0;
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
    int functionRef = luaL_ref( L, LUA_REGISTRYINDEX );
    scene->SetMouseDownFunction(functionRef);
    return 0;
}

static int lua_Scene_CreateLight(lua_State *L)
{
    Scene *scene = ScriptingEngineI::GetScriptingObjectPtr<Scene>(L, 1);

    std::string lightType = lua_tostring(L, 2);
    float r = lua_tonumber(L, 3);
    float g = lua_tonumber(L, 4);
    float b = lua_tonumber(L, 5);
    float ambientIntensity = lua_tonumber(L, 6);
    int posX = lua_tonumber(L, 7);
    int posY = lua_tonumber(L, 8);
    float diffuseSize = lua_tonumber(L, 9);
    float diffuseIntensity = lua_tonumber(L, 10);

    auto *light = (Light*)scene->CreateLight(lightType, {r, g, b}, ambientIntensity, {posX, posY}, diffuseSize, diffuseIntensity);
    light->ScriptingInterfaceRegisterFunctions(L, light);
    return 1;
}

static int lua_Scene_GetIsActivated(lua_State *L)
{
    Scene *scene = ScriptingEngineI::GetScriptingObjectPtr<Scene>(L, 1);
    lua_pushboolean(L, scene->GetIsActivated());
    return 1;
}

std::vector<luaL_Reg> Scene::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        {"SpriteStaticLoad", &lua_Scene_LoadSpriteDrawStatic}
      , {"SpriteStaticAdd", &lua_Scene_AddSpriteDrawStatic}
      , {"SpriteAnimatedLoad", &lua_Scene_SpriteAnimatedLoad}
      , {"SpriteTextLoad", &lua_Scene_SpriteTextLoad}
      , {"LoadCharacter", &lua_Scene_LoadCharacter}
      , {"SetMainCharacter", &lua_Scene_SetMainCharacter}
      , {"SetMouseDownFunction", &lua_Scene_SetMouseDownFunction}
      , {"CreateLight", &lua_Scene_CreateLight}
      , {"GetIsActivated", &lua_Scene_GetIsActivated}
    });
    return result;
}
