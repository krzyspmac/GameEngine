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

#ifndef CharacterMoverI_h
#define CharacterMoverI_h

#include "character_interface.h"
#include "interfaces.h"
#include "path_finder_interface.h"

namespace engine
{

    class CharacterMoverI
    {
    public:
        /// Initializes the character mover. Uses a target character.
        /// Does not take ownershop of the object. Memory disposal
        /// moved to the caller. Must exist for the duration of this
        /// instance
        CharacterMoverI(CharacterI *character, float pixelsPerMillisecond)
        : m_character(character), m_pixelsPerSecond(pixelsPerMillisecond)
        { }

        virtual ~CharacterMoverI() { };

    public:
        /// Update method must be called from the main loop to
        /// deal with continous character movement.
        /// Draws the character.
        virtual void Update() = 0;

    public:
        /// Draws the character.
        virtual void Draw() = 0;

        /// Places the character at position. Does not animate.
        virtual void PlaceCharacter(Vector2 target) = 0;

        /// Gets the character posittion.
        virtual Vector2& GetCharacterPosition() { return m_origin; };

        /// Move the character to a location.
        virtual void MoveCharacter(Vector2 target) = 0;

        /// Move the character along a path. Calling this again will clear
        /// the move stack and start again.
        /// Copies `path` data.
        virtual void MoveCharacterAlongPath(PathI *path) = 0;

        /// Gets the current character's target position.
        virtual Vector2& GetCharacterTargetPosition() { return m_targetOrigin; };

    public:
        Vector2 &GetCurrentOrigin() { return m_origin; };
        Vector2 &GetTargetOrigin() { return m_targetOrigin; };
        void SetWalkingSpeed(float val) { m_pixelsPerSecond = val; };

    protected:
        CharacterI *m_character;
        Vector2 m_origin;
        Vector2 m_targetOrigin;
        float m_pixelsPerSecond; // walking speed
    };
};

#endif /* CharacterMoverI_h */
