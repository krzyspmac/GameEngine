//
//  character_mover.cpp
//  Engine
//
//  Created by krzysp on 26/12/2021.
//

#include "character_mover.hpp"
#include "engine_interface.h"
#include "path.hpp"
#include <stdio.h>

using namespace engine;

CharacterMover::CharacterMover(CharacterI *character, float pixelsPerMillisecond)
: CharacterMoverI(character, pixelsPerMillisecond), m_moveType(MOVETYPE_NONE), m_pathCurrentSegmentIndex(0)
{
    m_targetOrigin = m_origin;
}

CharacterMover::~CharacterMover()
{
}

void CharacterMover::PlaceCharacter(Vector2 target)
{
    m_origin = target;
    m_targetOrigin = m_origin;
}

void CharacterMover::MoveCharacter(Vector2 target)
{
    std::cout << "Not implemented" << std::endl;
    exit(0);
}

void CharacterMover::MoveCharacterAlongPath(PathI *path)
{
    m_path = std::unique_ptr<PathI>(path);

    if (m_path != nullptr)
    {
        m_moveType = MOVETYPE_ALONG_PATH;
        m_pathSegments = m_path->ToLines();
        PathSegmentSet(0);
    }
    else {
        m_moveType = MOVETYPE_NONE;
    }
}

void CharacterMover::PathSegmentSet(size_t index)
{
    if (m_pathSegments.size() > index)
    {
        m_pathCurrentSegmentIndex = index;
        Line &segmentLine = m_pathSegments.at(index);
        m_pathCurrentSegment = &segmentLine;
        m_targetOrigin = segmentLine.GetP2();

        Vector2 &segmentStart = m_pathCurrentSegment->GetP1();
        Vector2 &segmentEnd = m_pathCurrentSegment->GetP2();

        m_segmentDistance = Vector2Distance(segmentStart, segmentEnd);
        m_segmentSeconds = m_segmentDistance / m_pixelsPerSecond;

        m_segmentInitialOrigin = segmentLine.GetP1();
        m_segmentLastSeconds = 0;
        m_segmentStartTicks = GetMainEngine()->getProvider().GetTicks();
        m_character->SetWalking(true);
    }
    else
    {
        m_pathCurrentSegmentIndex = -1;
    }
}

bool CharacterMover::ShouldMove()
{
    return (m_targetOrigin.x != m_origin.x) || (m_targetOrigin.y != m_origin.y);
}

void CharacterMover::Update()
{
    switch (m_moveType)
    {
        case MOVETYPE_NONE:
            Draw();
            return;
        case MOVETYPE_ALONG_PATH:
            UpdateMovePath();
            return;;
    }
}

void CharacterMover::UpdateMovePath()
{
    Uint64 ticks = GetMainEngine()->getProvider().GetTicks();
    Uint64 ticksDelta = ticks - m_segmentStartTicks;
    double seconds = ticksDelta / 1000.0;

    int xDelim = m_targetOrigin.x >= m_origin.x ? 1 : -1;
    int yDelim = m_targetOrigin.y >= m_origin.y ? -1 : 1;

    Vector2 &segmentStart = m_pathCurrentSegment->GetP1();
    Vector2 &segmentEnd = m_pathCurrentSegment->GetP2();
    float lesserX = MIN(segmentStart.x, segmentEnd.x);
    float greaterX = MAX(segmentStart.x, segmentEnd.x);
    float lesserY = MIN(segmentStart.y, segmentEnd.y);
    float greaterY = MAX(segmentStart.y, segmentEnd.y);

    Vector2 segmentDiff = Vector2GetDiff(segmentStart, segmentEnd);

    double dxPerSecond = fabs(segmentDiff.x) / m_segmentSeconds;
    m_origin.x = MAX(lesserX, MIN(greaterX, m_segmentInitialOrigin.x + (dxPerSecond * seconds * xDelim)));

    double dyPerSecond = fabs(segmentDiff.y) / m_segmentSeconds;
    m_origin.y = MAX(lesserY, MIN(greaterY, m_segmentInitialOrigin.y - (dyPerSecond * seconds * yDelim)));

    CharacterWalkState state = m_character->GetWalkState();

    if (segmentDiff.y != 0)
    {
        if (segmentDiff.y >= 0)
        {
            state = BACKWARD;
        }
        else
        {
            state = FORWARD;
        }
    }

    if (segmentDiff.x != 0 && abs(segmentDiff.x) > 10)
    {
        if (segmentDiff.x >= 0)
        {
            state = LEFT;
        }
        else
        {
            state = RIGHT;
        }
    }

    m_character->SetWalkState(state);
    Draw();
    m_segmentLastSeconds = seconds;

    if (PathSegmentDidReachEnd())
    {
        if (!PathSegmentRunNext())
        {
            m_character->SetWalking(false);
            m_character->SetWalkState(CharacterWalkStateGetStanding(m_character->GetWalkState()));
            m_origin = m_pathSegments.back().GetP2();
            m_moveType = MOVETYPE_NONE;
        }
    }
}

bool CharacterMover::PathSegmentDidReachEnd()
{
    if (m_pathCurrentSegment != nullptr)
    {
        Vector2 &last = m_pathCurrentSegment->GetP2();

        if (m_segmentLastSeconds > m_segmentSeconds || Vector2Equals(m_origin, last))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool CharacterMover::PathSegmentRunNext()
{
    if (m_pathCurrentSegmentIndex + 1 < m_pathSegments.size())
    {
        PathSegmentSet(m_pathCurrentSegmentIndex + 1);
        return true;
    }
    else
    {
        return false;
    }
}

void CharacterMover::Draw()
{
    m_character->Draw(m_origin);
}
