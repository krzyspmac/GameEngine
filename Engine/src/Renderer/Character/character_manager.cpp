//
//  character_manager.cpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#include "character_manager.hpp"
#include "scripting_engine.hpp"
#include "character.hpp"
#include "character_mover.hpp"

using namespace engine;

CharacterRepresentation* CharacterManager::LoadCharacter(std::string jsonFilename)
{
    CharacterRepresentation *character = GetCharacter(jsonFilename);
    if (!character)
    {
        character = LoadCharacterNew(jsonFilename);
    }
    return character;
}

CharacterRepresentation* CharacterManager::LoadCharacterNew(std::string jsonFilename)
{
    Character *character = new Character(jsonFilename);
    if (character != nullptr)
    {
        CharacterRepresentation *rep = new CharacterRepresentation(character);
        m_representations.emplace_back(std::unique_ptr<CharacterRepresentation>(std::move(rep)));
        return rep;
    }
    else
    {
        return nullptr;
    }
}

void UnloadCharacter(CharacterI*);

CharacterRepresentation* CharacterManager::GetCharacter(std::string jsonFilename)
{
    for (auto it = m_representations.begin(); it != m_representations.end(); ++it)
    {
        CharacterRepresentation *rep = it->get();
        CharacterI *chr = rep->GetCharacter();
        if (chr && chr->GetJsonFilename().compare(jsonFilename) == 0)
        {
            return rep;
        }
    }
    return nullptr;
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(CharacterManager);

static int lua_CharacterManager_loadCharacter(lua_State *L)
{
//    // TODO: should check if proper params are in proper places!
//    CharacterManager **ptr = (CharacterManager**)luaL_checkudata(
//        L, 1, CharacterManager::ScriptingInterfaceName().c_str()
//     );
//    std::string jsonName = luaL_checkstring(L, 2);
//
//    Character *character = (Character*)(*ptr)->LoadCharacter(jsonName);
//    if (character != nullptr)
//    {
//        character->ScriptingInterfaceRegisterFunctions(L, character);
//    }
//    else
//    {
//        lua_pushnil(L);
//    }
//
    return 1;
}

std::vector<luaL_Reg> CharacterManager::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "LoadCharacter", &lua_CharacterManager_loadCharacter },
    });
    return result;
}
