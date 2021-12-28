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

void CharacterMover::PlaceCharacter(Origin target)
{
    m_origin = target;
    m_targetOrigin = m_origin;
}

void CharacterMover::MoveCharacter(Origin target)
{
    m_moveType = MOVETYPE_SIMPLE;
    m_targetOrigin = target;
}

void CharacterMover::MoveCharacterAlongPath(PathI *path)
{
    m_moveType = MOVETYPE_ALONG_PATH;
    m_path = std::unique_ptr<PathI>(path);
    m_pathSegments = m_path->ToLines();
    SetPathSegment(0);
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
//        m_targetOrigin = segmentLine.GetP2();
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
    if (!ShouldMove())
    {
        Draw();
        return;
    }

    /*
     UP and DOWN when diff(x) < 10
     */

    int animationDistancePerFrame = 5;
    int m_frameAnimationDurationMs = 10;

    Origin diff = OriginGetDiff(m_targetOrigin, m_origin);
    CharacterWalkState state = m_character->GetWalkState();

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

    int xDelim = m_targetOrigin.x >= m_origin.x ? 1 : -1;
    int yDelim = m_targetOrigin.y >= m_origin.y ? 1 : -1;

    Uint64 ticks = GetMainEngine()->getProvider().GetTicks();
    Uint64 seconds = ticks / m_frameAnimationDurationMs;

    if (seconds == m_lastChecked)
    {
        Draw();
        return;
    }

    m_lastChecked = seconds;

    m_character->SetWalking(true);

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

    if (yDelim == -1)
    {
        // Generally walks left
        m_origin.y = MAX(m_targetOrigin.y, m_origin.y + (yDelim * animationDistancePerFrame));
    }
    else if (yDelim == 1)
    {
        // Generally walks right
        m_origin.y = MIN(m_targetOrigin.y, m_origin.y + (yDelim * animationDistancePerFrame));
    }

    m_character->SetWalkState(state);
    Draw();

    if (OriginEquals(m_targetOrigin, m_origin))
    {
        m_character->SetWalking(false);
        m_character->SetWalkState(CharacterWalkStateGetStanding(m_character->GetWalkState()));
    }
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

    if (xDelim == -1)
    {
        // Generally walks left
//        m_origin.x = MAX(m_targetOrigin.x, m_origin.x + (xDelim * animationDistancePerFrame));
    }
    else if (xDelim == 1)
    {
        // Generally walks right
//        m_origin.x = MIN(m_targetOrigin.x, m_origin.x + (xDelim * animationDistancePerFrame));
    }


    m_origin.x = MIN(m_targetOrigin.x, m_origin.x + (xDelim * animationDistancePerFrame));
    Draw();
}

void CharacterMover::Draw()
{
    m_character->Draw(m_origin.x, m_origin.y);
}

