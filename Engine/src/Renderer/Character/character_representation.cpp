//
//  character_representation.cpp
//  Engine
//
//  Created by krzysp on 31/12/2021.
//

#include "character_representation.hpp"
#include "character_mover.hpp"

using namespace engine;

CharacterRepresentation::CharacterRepresentation(CharacterI *character)
: m_character(character)
{
    m_mover = std::unique_ptr<CharacterMoverI>(new CharacterMover(m_character, 100));
}

CharacterRepresentation::~CharacterRepresentation()
{
    m_mover.reset();
}

void CharacterRepresentation::DrawAt(Vector2& position)
{
    m_character->Draw(position);
}

void CharacterRepresentation::PlaceAt(Vector2 target)
{
    m_mover->PlaceCharacter(target);
}

void CharacterRepresentation::SetScale(float val)
{
    m_character->SetScale(val);
}

Vector2& CharacterRepresentation::GetPosition()
{
    return m_mover->GetCharacterPosition();
}

void CharacterRepresentation::WalkTo(Vector2& position)
{
    PathFinder *pf = m_pathFinder.get();
    if (pf != nullptr)
    {

    }
    else
    {
        m_mover->MoveCharacter(position);
    }
}

void CharacterRepresentation::Render()
{
    m_mover->Update();
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(CharacterRepresentation);

static int lua_CharacterRepresentation_DrawAt(lua_State *L)
{
    CharacterRepresentation *sender = ScriptingEngineI::GetScriptingObjectPtr<CharacterRepresentation>(L, 1);
    float x = lua_tonumberx(L, 2, nullptr);
    float y = lua_tonumberx(L, 3, nullptr);
    Vector2 pos = {x, y};
    sender->DrawAt(pos);
    return 0;
}

static int lua_CharacterRepresentation_PlaceAt(lua_State *L)
{
    CharacterRepresentation *sender = ScriptingEngineI::GetScriptingObjectPtr<CharacterRepresentation>(L, 1);
    float x = lua_tonumberx(L, 2, nullptr);
    float y = lua_tonumberx(L, 3, nullptr);
    Vector2 pos = {x, y};
    sender->PlaceAt(pos);
    return 0;
}

static int lua_CharacterRepresentation_GetPosition(lua_State *L)
{
    CharacterRepresentation *sender = ScriptingEngineI::GetScriptingObjectPtr<CharacterRepresentation>(L, 1);
    Vector2& position = sender->GetPosition();
    lua_pushnumber(L, position.x);
    lua_pushnumber(L, position.y);
    return 2;
}

static int lua_CharacterRepresentation_SetScale(lua_State *L)
{
    CharacterRepresentation *sender = ScriptingEngineI::GetScriptingObjectPtr<CharacterRepresentation>(L, 1);
    float x = lua_tonumberx(L, 2, nullptr);
    sender->SetScale(x);
    return 0;
}

static int lua_CharacterRepresentation_WalkTo(lua_State *L)
{
    CharacterRepresentation *sender = ScriptingEngineI::GetScriptingObjectPtr<CharacterRepresentation>(L, 1);
    float x = lua_tonumberx(L, 2, nullptr);
    float y = lua_tonumberx(L, 3, nullptr);
    Vector2 pos = {x, y};
    sender->WalkTo(pos);
    return 0;
}

std::vector<luaL_Reg> CharacterRepresentation::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        {"DrawAt", &lua_CharacterRepresentation_DrawAt},
        {"PlaceAt", &lua_CharacterRepresentation_PlaceAt},
        {"GetPosition", &lua_CharacterRepresentation_GetPosition},
        {"SetScale", &lua_CharacterRepresentation_SetScale},
        {"WalkTo", &lua_CharacterRepresentation_WalkTo}
    });
    return result;
}
