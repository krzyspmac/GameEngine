//
//  character.hpp
//  Engine
//
//  Created by krzysp on 25/12/2021.
//

#ifndef character_hpp
#define character_hpp

#include "character_interface.h"
#include "scripting_engine_provider_interface.h"

namespace engine
{

    /**
     Default game character.
     */
    class Character: public CharacterI, public ScriptingInterface
    {
    public:
        /** @private */
        Character(std::string jsonDefinition);

    private:
        void ProcessBodyParts(void*, SpriteAtlasI*, CharacterWalkState, bool reversed);
        void ProcessBodyFrame(void*, SpriteAtlasI *atlas, CharacterWalkState walkState, bool reversed);
        void ProcessHeadFrame(void*, SpriteAtlasI *atlas, CharacterWalkState walkState, bool reversed);

    public:
        /**
         Set the scale.
         */
        void SetScale(float scale);

        /**
         Draw the character at position.
         */
        void Draw(Vector2& position);

    /// ScriptingInterface
    public:
        /**
         @private
         */
        SCRIPTING_INTERFACE_HEADERS(Character);
    };
};

#endif /* character_hpp */
