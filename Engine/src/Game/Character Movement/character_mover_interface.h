//
//  CharacterMoverI.h
//  Engine
//
//  Created by krzysp on 26/12/2021.
//

#ifndef CharacterMoverI_h
#define CharacterMoverI_h

#include "character_interface.h"
#include "common_engine_impl.h"
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
        CharacterMoverI(CharacterI *character)
        : m_character(character)
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
        virtual void PlaceCharacter(Origin target) = 0;

        /// Gets the character posittion.
        virtual Origin& GetCharacterPosition() { return m_origin; };

        /// Move the character to a location.
        virtual void MoveCharacter(Origin target) = 0;

        /// Move the character along a path. Calling this again will clear
        /// the move stack and start again.
        /// Takes ownership of `path`.
        virtual void MoveCharacterAlongPath(PathI *path) = 0;

        /// Gets the current character's target position.
        virtual Origin& GetCharacterTargetPosition() { return m_targetOrigin; };

    public:
        Origin &GetCurrentOrigin() { return m_origin; };
        Origin &GetTargetOrigin() { return m_targetOrigin; };

    protected:
        CharacterI *m_character;
        Origin m_origin;
        Origin m_targetOrigin;
    };
};

#endif /* CharacterMoverI_h */
