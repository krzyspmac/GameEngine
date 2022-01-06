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
        MOVETYPE_ALONG_PATH
    } CharacterMoveType;

    class CharacterMover: public CharacterMoverI
    {
    public:
        CharacterMover(CharacterI *character, float pixelsPerMillisecond);
        ~CharacterMover();

    public:
        void Update();
        void PlaceCharacter(Vector2 target);
        void MoveCharacter(Vector2 target);
        void MoveCharacterAlongPath(PathI *path);

    private:
        void Draw();
        bool ShouldMove();
        void UpdateMovePath();
        void PathSegmentSet(size_t index);
        bool PathSegmentDidReachEnd();
        bool PathSegmentRunNext();

    private:
        CharacterMoveType m_moveType;
        std::unique_ptr<PathI> m_path;
        std::vector<Line> m_pathSegments;
        
        Line    *m_pathCurrentSegment;
        size_t  m_pathCurrentSegmentIndex;

        Vector2 m_segmentInitialOrigin;
        Uint64  m_segmentStartTicks;
        float   m_segmentDistance;
        float   m_segmentSeconds;
        double  m_segmentLastSeconds;
    };
};

#endif /* character_mover_hpp */
