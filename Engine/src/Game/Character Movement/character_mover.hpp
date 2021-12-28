//
//  character_mover.hpp
//  Engine
//
//  Created by krzysp on 26/12/2021.
//

#ifndef character_mover_hpp
#define character_mover_hpp

#include "character_mover_interface.h"
#include "common_engine_impl.h"
#include "function.hpp"

namespace engine
{

    typedef enum
    {
        MOVETYPE_NONE,
        MOVETYPE_ALONG_PATH,
        MOVETYPE_SIMPLE
    } CharacterMoveType;

    class CharacterMover: public CharacterMoverI
    {
    public:
        CharacterMover(CharacterI *character);
        ~CharacterMover();

    public:
        void Update();
        void PlaceCharacter(Vector2 target);
        void MoveCharacter(Vector2 target);
        void MoveCharacterAlongPath(PathI *path);

    private:
        void Draw();
        bool ShouldMove();
        void UpdateMoveSimple();
        void UpdateMovePath();
        void SetPathSegment(int index);

    private:
        Uint64 m_lastChecked;
        CharacterMoveType m_moveType;
        std::unique_ptr<PathI> m_path;
        std::vector<Line> m_pathSegments;
        size_t m_pathCurrentIndex;
        Line *m_pathCurrentSegment;
        std::unique_ptr<Function> m_pathCurrentFunction;
    };
};

#endif /* character_mover_hpp */
