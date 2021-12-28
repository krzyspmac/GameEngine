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

CharacterMover::CharacterMover(CharacterI *character)
: CharacterMoverI(character), m_moveType(MOVETYPE_NONE), m_pathCurrentIndex(0), m_pathCurrentFunction(nullptr)
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
    m_moveType = MOVETYPE_SIMPLE;
    m_targetOrigin = target;
}

void CharacterMover::MoveCharacterAlongPath(PathI *path)
{
    m_path = std::unique_ptr<PathI>(path);

    if (m_path != nullptr)
    {
        m_moveType = MOVETYPE_ALONG_PATH;
        m_pathSegments = m_path->ToLines();
        SetPathSegment(0);
    }
    else {
        m_moveType = MOVETYPE_NONE;
    }
//    if (path != nullptr && !path->GetPath().empty())
//    {
//        m_targetOrigin = path->GetPath().back();
//        m_origin = m_targetOrigin;
//    }
}

void CharacterMover::SetPathSegment(int index)
{
    if (m_pathSegments.size() > index)
    {
        m_pathCurrentIndex = index;
        Line &segmentLine = m_pathSegments.at(index);
        m_pathCurrentSegment = &segmentLine;
        Function *segmentFunction = new Function(segmentLine.GetP1(), segmentLine.GetP2());
        m_pathCurrentFunction = std::unique_ptr<Function>(segmentFunction);
        m_targetOrigin = segmentLine.GetP2();
    }
    else
    {
        m_pathCurrentIndex = -1;
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
        case MOVETYPE_SIMPLE:
            UpdateMoveSimple();
            return;
        case MOVETYPE_ALONG_PATH:
            UpdateMovePath();
            return;;
    }
}

void CharacterMover::UpdateMoveSimple()
{
//    if (!ShouldMove())
//    {
//        Draw();
//        return;
//    }
//
//    /*
//     UP and DOWN when diff(x) < 10
//     */
//
//    int animationDistancePerFrame = 5;
//    int m_frameAnimationDurationMs = 10;
//
//    Vector2 diff = OriginGetDiff(m_targetOrigin, m_origin);
//    CharacterWalkState state = m_character->GetWalkState();
//
//    if (diff.y != 0)
//    {
//        if (diff.y >= 0)
//        {
//            state = FORWARD;
//        }
//        else
//        {
//            state = BACKWARD;
//        }
//    }
//
//    if (diff.x != 0 && abs(diff.x) > 10)
//    {
//        if (diff.x >= 0)
//        {
//            state = RIGHT;
//        }
//        else
//        {
//            state = LEFT;
//        }
//    }
//
//    int xDelim = m_targetOrigin.x >= m_origin.x ? 1 : -1;
//    int yDelim = m_targetOrigin.y >= m_origin.y ? 1 : -1;
//
//    Uint64 ticks = GetMainEngine()->getProvider().GetTicks();
//    Uint64 seconds = ticks / m_frameAnimationDurationMs;
//
//    if (seconds == m_lastChecked)
//    {
//        Draw();
//        return;
//    }
//
//    m_lastChecked = seconds;
//
//    m_character->SetWalking(true);
//
//    if (xDelim == -1)
//    {
//        // Generally walks left
//        m_origin.x = MAX(m_targetOrigin.x, m_origin.x + (xDelim * animationDistancePerFrame));
//    }
//    else if (xDelim == 1)
//    {
//        // Generally walks right
//        m_origin.x = MIN(m_targetOrigin.x, m_origin.x + (xDelim * animationDistancePerFrame));
//    }
//
//    if (yDelim == -1)
//    {
//        // Generally walks left
//        m_origin.y = MAX(m_targetOrigin.y, m_origin.y + (yDelim * animationDistancePerFrame));
//    }
//    else if (yDelim == 1)
//    {
//        // Generally walks right
//        m_origin.y = MIN(m_targetOrigin.y, m_origin.y + (yDelim * animationDistancePerFrame));
//    }
//
//    m_character->SetWalkState(state);
//    Draw();
//
//    if (OriginEquals(m_targetOrigin, m_origin))
//    {
//        m_character->SetWalking(false);
//        m_character->SetWalkState(CharacterWalkStateGetStanding(m_character->GetWalkState()));
//    }
}

void CharacterMover::UpdateMovePath()
{
    // We move by n-px per frame for the current path patr.

    int animationDistancePerFrame = 5;
    int m_frameAnimationDurationMs = 10;

    int xDelim = m_targetOrigin.x >= m_origin.x ? 1 : -1;
    int yDelim = m_targetOrigin.y >= m_origin.y ? 1 : -1;

    Uint64 ticks = GetMainEngine()->getProvider().GetTicks();
    Uint64 seconds = ticks / m_frameAnimationDurationMs;

    Vector2 diff = Vector2GetDiff(m_targetOrigin, m_origin);
    CharacterWalkState state = m_character->GetWalkState();
    m_character->SetWalking(true);

    if (seconds == m_lastChecked)
    {
        Draw();
        return;
    }

    m_lastChecked = seconds;

    if (diff.y != 0)
    {
        if (diff.y >= 0)
        {
            state = FORWARD;
        }
        else
        {
            state = BACKWARD;
        }
    }

    if (diff.x != 0 && abs(diff.x) > 10)
    {
        if (diff.x >= 0)
        {
            state = RIGHT;
        }
        else
        {
            state = LEFT;
        }
    }

    if (xDelim == -1)
    {
        // Generally walks left
        m_origin.x = MAX(m_targetOrigin.x, m_origin.x + (xDelim * animationDistancePerFrame));

    }
    else if (xDelim == 1)
    {
        // Generally walks right
        m_origin.x = MIN(m_targetOrigin.x, m_origin.x + (xDelim * animationDistancePerFrame));
    }

    m_origin.y = (int)m_pathCurrentFunction->f(m_origin.x);
    m_character->SetWalkState(state);
    Draw();

    if (PathSegmentDidReachEnd())
    {
        if (!PathSegmentRunNext())
        {
            m_character->SetWalking(false);
            m_character->SetWalkState(CharacterWalkStateGetStanding(m_character->GetWalkState()));
        }
    }

//    if (Vector2Equals(m_targetOrigin, m_origin))
//    {
//        m_character->SetWalking(false);
//        m_character->SetWalkState(CharacterWalkStateGetStanding(m_character->GetWalkState()));
//    }
}

bool CharacterMover::PathSegmentDidReachEnd()
{
    if (m_pathCurrentSegment != nullptr)
    {
        Vector2 &last = m_pathCurrentSegment->GetP2();

        if (Vector2Equals(m_origin, last))
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
    if (m_pathCurrentIndex + 1 < m_pathSegments.size())
    {
        SetPathSegment(m_pathCurrentIndex + 1);
        return true;
    }
    else
    {
        return false;
    }
}

void CharacterMover::Draw()
{
    m_character->Draw(m_origin.x, m_origin.y);
}

