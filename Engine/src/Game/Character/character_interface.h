//
//  character.hpp
//  Engine
//
//  Created by krzysp on 25/12/2021.
//

#ifndef character_interface_hpp
#define character_interface_hpp

#include "character_renderer_interface.h"
#include "vector2.hpp"

namespace engine
{

    /// Should render the character, do animations for the walking stances.
    class CharacterI {
    public:
        CharacterI(): m_characterRenderer(nullptr), m_talking(false), m_isWalking(false), m_walkState(STAND_RIGHT) { };

        virtual ~CharacterI() { }

    /// Character rendering
    public:
        CharacterRendererI *GetCharacterRenderer() { return m_characterRenderer.get(); };

        /// Draw the character. The origin aligned to the bottom center part of the character.
        virtual void Draw(Vector2& position) = 0;

        /// Set the character scale
        virtual void SetScale(float scale) = 0;

        virtual void Change() = 0;

    /// Character actions
    public:
        /// Set the character to `talk`. This turns on the walking animation
        /// for the current renderer.
        void SetTalking(bool value) { m_talking = value; };

        ///
        bool IsTalking() { return m_talking; };

        /// Set tha character to `walk`. This turns on the walking animation
        /// for the current renderer.
        void SetWalking(bool value) { m_isWalking = value; };

        ///
        bool IsWalking() { return m_isWalking; };

        /// Set the state of the character animation.
        void SetWalkState(CharacterWalkState state) { m_walkState = state; };

        ///
        CharacterWalkState GetWalkState() { return m_walkState; };

    protected:
        std::unique_ptr<CharacterRendererI> m_characterRenderer;
        bool m_talking;
        bool m_isWalking;
        CharacterWalkState m_walkState;
    };
};

#endif /* character_interface_hpp */
