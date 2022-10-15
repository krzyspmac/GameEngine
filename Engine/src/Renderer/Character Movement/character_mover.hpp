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

#ifndef character_mover_hpp
#define character_mover_hpp

#include "character_mover_interface.h"
#include "interfaces.h"
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
