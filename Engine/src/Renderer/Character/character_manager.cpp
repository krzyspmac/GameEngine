// Copyright (c) 2022 Krzysztof Pawłowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

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
