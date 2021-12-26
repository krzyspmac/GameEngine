//
//  character_mover.hpp
//  Engine
//
//  Created by krzysp on 26/12/2021.
//

#ifndef character_mover_hpp
#define character_mover_hpp

#include "character_mover_interface.h"

namespace engine
{

    class CharacterMover: public CharacterMoverI
    {
    public:
        CharacterMover(CharacterI *character);

    public:
        void Update();
        void PlaceCharacter(Origin target);
        void MoveCharacter(Origin target);

    private:
        bool ShouldMove();
    };
};

#endif /* character_mover_hpp */
