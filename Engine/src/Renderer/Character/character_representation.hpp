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

#ifndef character_representation_hpp
#define character_representation_hpp

#include "character_interface.h"
#include "path_finder.hpp"
#include "character_mover_interface.h"

namespace engine
{
    /**
     The final character renderer. Uses CharacterI, CharacterMoverI and PathFinder to
     deal with rendering, path finder, placement and animation. This is the go-to
     class to render a character in a complete fashion.
     \see Scene
     */
    class CharacterRepresentation
    {
        CharacterI *m_character;
        bool m_hidden;
        std::unique_ptr<CharacterMoverI> m_mover;
        std::unique_ptr<PathFinder> m_pathFinder;

    public:
        /** @private */
        CharacterRepresentation(CharacterI *);

        /** @private */
        ~CharacterRepresentation();

        /** @private */
        CharacterI *GetCharacter() { return m_character; };

        /** @private */
        CharacterMoverI *GetMover() { return m_mover.get(); };

    public:

        /**
         Renders at position. Static. No anim.
         */
        void DrawAt(Vector2& position);

        /**
         Places at position. Static. No anim.
         */
        void PlaceAt(Vector2 target);

        /**
         Gets the current position.
         */
        Vector2& GetPosition();

        /**
         Sets the character scale.
         */
        void SetScale(float val);
        
        /**
         Set the z-position
         */
        void SetZPosition(float val);

        /**
         Walks to a specific place. Uses walkboxes if provided.
         */
        void WalkTo(Vector2& position);

        /**
         Sets the current inverse walk boxes, a list of plygons
         where the character can't go.
         */
        void SetInverseWalkbox(std::string polygonJsonFilename);

        /**
         Sets the character crossing speed. In pixels per millisecond.
         */
        void SetCharacterWalkingSpeed(float pixelsInMilliseconds);

        /**
         Sets the character's visibility.
         */
        void SetHidden(bool value);

        /**
         Renders the character as needed. This is the main method
         called by the engine.
         */
        void Render();
    };
};

#endif /* character_representation_hpp */
