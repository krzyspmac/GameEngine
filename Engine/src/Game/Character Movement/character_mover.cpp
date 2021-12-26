//
//  character_mover.cpp
//  Engine
//
//  Created by krzysp on 26/12/2021.
//

#include "character_mover.hpp"
#include "engine_interface.h"
#include <stdio.h>

using namespace engine;

CharacterMover::CharacterMover(CharacterI *character)
: CharacterMoverI(character)
{
    m_targetOrigin = m_origin;
}

void CharacterMover::PlaceCharacter(Origin target)
{
    m_origin = target;
    m_targetOrigin = m_origin;
}

void CharacterMover::MoveCharacter(Origin target)
{
    m_targetOrigin = target;
}

bool CharacterMover::ShouldMove()
{
    return (m_targetOrigin.x != m_origin.x) || (m_targetOrigin.y != m_origin.y);
}

int lastSecond = -1;

void CharacterMover::Update()
{
    if (!ShouldMove())
    {
        m_character->Draw(m_origin.x, m_origin.y);
        return;
    }

    int animationDistancePerFrame = 5;
    int m_frameAnimationDurationMs = 10;

    int xDelim = m_targetOrigin.x >= m_origin.x ? 1 : -1;
    int yDelim = m_targetOrigin.y >= m_origin.y ? 1 : -1;

    Uint64 ticks = GetMainEngine()->getProvider().GetTicks();
    Uint32 seconds = ticks / m_frameAnimationDurationMs;

    if (seconds == lastSecond)
    {
        m_character->Draw(m_origin.x, m_origin.y);
        return;
    }

    lastSecond = seconds;

    m_character->SetWalking(true);
    m_character->SetWalkState(RIGHT);

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

    m_character->Draw(m_origin.x, m_origin.y);
}
