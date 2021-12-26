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

    private:
        void ProcessBodyParts(void*, SpriteAtlasI*, CharacterWalkDirection, bool reversed);
        void ProcessBodyFrame(void*, SpriteAtlasI *atlas, CharacterWalkDirection walkState, bool reversed);
        void ProcessHeadFrame(void*, SpriteAtlasI *atlas, CharacterWalkDirection walkState, bool reversed);

    public:
        void Draw(int x, int y);

        void Change();
    };
};

#endif /* character_hpp */
