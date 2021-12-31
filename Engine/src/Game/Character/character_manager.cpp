//
//  character_manager.cpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#include "character_manager.hpp"
#include "scripting_engine.hpp"
#include "character.hpp"

using namespace engine;

CharacterI* CharacterManager::LoadCharacter(std::string jsonFilename)
{
    CharacterI *character = GetCharacter(jsonFilename);
    if (!character)
    {
        character = LoadCharacterNew(jsonFilename);
    }
    return character;
}

CharacterI* CharacterManager::LoadCharacterNew(std::string jsonFilename)
{
    Character *character = new Character(jsonFilename);
    if (character != nullptr)
    {
        m_characters.emplace_back(std::move(character));
    }
    return character;
}

void UnloadCharacter(CharacterI*);

CharacterI* CharacterManager::GetCharacter(std::string jsonFilename)
{
    for (auto it = m_characters.begin(); it != m_characters.end(); it++)
    {
        if (it->get()->GetJsonFilename().compare(jsonFilename) == 0)
        {
            return it->get();
        }
    }
    return nullptr;
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(CharacterManager);

static int lua_CharacterManager_loadCharacter(lua_State *L)
{
    // TODO: should check if proper params are in proper places!
    CharacterManager **ptr = (CharacterManager**)luaL_checkudata(
        L, 1, CharacterManager::ScriptingInterfaceName().c_str()
     );
    std::string jsonName = luaL_checkstring(L, 2);

    Character *character = (Character*)(*ptr)->LoadCharacter(jsonName);
    if (character != nullptr)
    {
        character->ScriptingInterfaceRegisterFunctions(L, character);
    }
    else
    {
        lua_pushnil(L);
    }

    return 1;
}

std::vector<luaL_Reg> CharacterManager::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "LoadCharacter", &lua_CharacterManager_loadCharacter },
    });
    return result;
}
