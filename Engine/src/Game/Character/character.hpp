//
//  character.hpp
//  Engine
//
//  Created by krzysp on 25/12/2021.
//

#ifndef character_hpp
#define character_hpp

#include "character_interface.h"

namespace engine
{

    class Character: public CharacterI
    {
    public:
        Character(std::string jsonDefinition);

    public:
        void Draw(int x, int y);
    };
};

#endif /* character_hpp */
