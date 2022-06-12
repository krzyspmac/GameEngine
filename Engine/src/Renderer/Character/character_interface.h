//
//  character.hpp
//  Engine
//
//  Created by krzysp on 25/12/2021.
//

#ifndef character_interface_hpp
#define character_interface_hpp

#include "character_renderer_interface.h"
#include "scripting_engine_provider_interface.h"
#include "vector2.hpp"

namespace engine
{

    /**
     Renders the character. Uses CharacteMoverI and WalkingBoxes to deal with
     proper walking animations.
     */
    class CharacterI {
    public:
        CharacterI(std::string jsonFilename): m_jsonFilename(jsonFilename), m_characterRenderer(nullptr), m_talking(false), m_isWalking(false), m_walkState(STAND_RIGHT) { };

        virtual ~CharacterI() { }

    /// Character rendering
    public:
        std::string GetJsonFilename() { return m_jsonFilename; };

        ///
        CharacterRendererI *GetCharacterRenderer() { return m_characterRenderer.get(); };

        /// Draw the character. The origin aligned to the bottom center part of the character.
        virtual void Draw(Vector2& position) = 0;

        /// Set the character scale
        virtual void SetScale(float scale) = 0;
        
        /// Set the z-position
        virtual void SetZPosition(float) = 0;

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

    /// Helper methods use additional classes to facilitate rendering, animation
    /// and path finding.
    public:

    protected:
        std::string m_jsonFilename;
        std::unique_ptr<CharacterRendererI> m_characterRenderer;
        bool m_talking;
        bool m_isWalking;
        CharacterWalkState m_walkState;
    };
};

#endif /* character_interface_hpp */
