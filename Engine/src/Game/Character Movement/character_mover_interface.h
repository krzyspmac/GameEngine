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

    public:
        /// Update method must be called from the main loop to
        /// deal with continous character movement.
        /// Draws the character.
        virtual void Update() = 0;

    public:
        /// Places the character at position. Does not animate.
        virtual void PlaceCharacter(Origin target) = 0;

        /// Move the character to a location.
        virtual void MoveCharacter(Origin target) = 0;

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
