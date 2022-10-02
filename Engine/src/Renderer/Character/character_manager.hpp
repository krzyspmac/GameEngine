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

#ifndef character_manager_hpp
#define character_manager_hpp

#include <iostream>
#include "character_interface.h"
#include "character_representation.hpp"

namespace engine
{
    /**
     CharacterManager
     \addtogroup API_GLOBALS
     */
    /**
     Manages a list of character representations. Allows loading of the characters
     from specific json files. Keeps a list of character representations
     available for future use.
     */
    class CharacterManager
    {
    public:
        CharacterManager() { };

    public:
        /**
         Loads or gets the character previously loaded. `jsonFilename` must exist
         in the game files as well as any other files referenced by the json.
         Loaded characters are kept in memory by the manager. No need to take
         ownership of the intances.
         */
        CharacterRepresentation* LoadCharacter(std::string jsonFilename);

        /**
         Unloads the character and its texture sheet.
         */
        void UnloadCharacter(CharacterRepresentation*);

    private:
        CharacterRepresentation* LoadCharacterNew(std::string jsonFilename);
        CharacterRepresentation* GetCharacter(std::string jsonFilename);

    private:
        std::vector<std::unique_ptr<CharacterI>> m_characters;
        std::vector<std::unique_ptr<CharacterRepresentation>> m_representations;
    };
};

#endif /* character_manager_hpp */
