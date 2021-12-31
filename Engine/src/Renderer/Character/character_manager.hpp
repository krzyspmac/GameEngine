//
//  character_manager.hpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#ifndef character_manager_hpp
#define character_manager_hpp

#include <iostream>
#include "scripting_engine_provider_interface.h"
#include "character_interface.h"
#include "character_representation.hpp"

namespace engine
{
    class CharacterManager: public ScriptingInterface
    {
    public:
        CharacterManager() { };

    public:
        /**
         Loads or gets the character previously loaded. `jsonFilename` must exist
         in the game files as well as any other files referenced by the json.
         Loaded characters are kept in memory by the manager. No need to take
         ownership of the intances.
         \ingroup API_EXPOSED
         */
        CharacterRepresentation* LoadCharacter(std::string jsonFilename);

        /**
         Unloads the character and its texture sheet.
         \ingroup API_EXPOSED
         */
        void UnloadCharacter(CharacterRepresentation*);

    private:
        CharacterRepresentation* LoadCharacterNew(std::string jsonFilename);
        CharacterRepresentation* GetCharacter(std::string jsonFilename);

    private:
        std::vector<std::unique_ptr<CharacterI>> m_characters;
        std::vector<std::unique_ptr<CharacterRepresentation>> m_representations;

    /// ScriptingInterface
    public:
        SCRIPTING_INTERFACE_HEADERS(CharacterManager);
    };
};

#endif /* character_manager_hpp */
