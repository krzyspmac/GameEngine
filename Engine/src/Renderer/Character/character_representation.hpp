//
//  character_representation.hpp
//  Engine
//
//  Created by krzysp on 31/12/2021.
//

#ifndef character_representation_hpp
#define character_representation_hpp

#include "character_interface.h"
#include "path_finder.hpp"
#include "character_mover_interface.h"
#include "scripting_engine_provider_interface.h"

namespace engine
{
    /**
     The final character renderer. Uses CharacterI, CharacterMoverI and PathFinder to
     deal with rendering, path finder, placement and animation. This is the go-to
     class to render a character in a complete fashion.
     \see Scene
     \ingroup API_EXPOSED
     */
    class CharacterRepresentation
    {
        CharacterI *m_character;
        std::unique_ptr<CharacterMoverI> m_mover;
        std::unique_ptr<PathFinder> m_pathFinder;

    public:
        CharacterRepresentation(CharacterI *);
        ~CharacterRepresentation();
        
        CharacterI *GetCharacter() { return m_character; };
        CharacterMoverI *GetMover() { return m_mover.get(); };

    public:

        /**
         Renders at position. Static. No anim.
         \ingroup API_EXPOSED
         */
        void DrawAt(Vector2& position);

        /**
         Places at position. Static. No anim.
         \ingroup API_EXPOSED
         */
        void PlaceAt(Vector2 target);

        /**
         Gets the current position.
         \ingroup API_EXPOSED
         */
        Vector2& GetPosition();

        /**
         Sets the character scale.
         \ingroup API_EXPOSED
         */
        void SetScale(float val);

        /**
         Walks to a specific place. Uses walkboxes if provided.
         \ingroup API_EXPOSED
         */
        void WalkTo(Vector2& position);

        /**
         Sets the current inverse walk boxes, a list of plygons
         where the character can't go.
         */

        /**
         Renders the character as needed. This is the main method
         called by the engine.
         */
        void Render();

    /// ScriptingInterface
    public:
        /// @private
        SCRIPTING_INTERFACE_HEADERS(CharacterRepresentation);
    };
};

#endif /* character_representation_hpp */
