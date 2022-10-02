//
//  character_manager.cpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#include "character_manager.hpp"
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
