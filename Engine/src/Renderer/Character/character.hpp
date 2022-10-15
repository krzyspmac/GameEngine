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

#ifndef character_hpp
#define character_hpp

#include "character_interface.h"

namespace engine
{

    /**
     Default game character.
     */
    class Character: public CharacterI
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

        /**
         Set Z-position
         */
        void SetZPosition(float);
    };
};

#endif /* character_hpp */
