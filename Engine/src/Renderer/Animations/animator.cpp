//
//  animator.cpp
//  Engine
//
//  Created by krzysp on 27/09/2022.
//

#include "animator.hpp"
#include "easy.h"

using namespace engine;

Animator::Animator(double delay, double duration, Time& time, AnimationCurveLambda curve)
    : m_secondsDelay(delay)
    , m_secondsDuration(duration)
    , m_secondsCurrent(0.f)
    , m_progress(0.f)
    , m_time(time)
    , m_curve(curve)
    , m_beginHndlr(nullptr)
    , m_endHndlr(nullptr)
{
    m_secondsStart = time.GetEngineStartSec();
    ENGINE().getPeriodicUpdatesManager().Add(this);
};

void Animator::Register(std::function<void(AnimatorI*)> lamda) {
    blocks.push_back(lamda);
}

void Animator::Prepare(std::function<void(AnimatorI*)> beginHndlr, std::function<void(AnimatorI*)> endHndlr) {
    m_beginHndlr = beginHndlr;
    m_endHndlr = endHndlr;

    m_beginHndlr(this);
}

void Animator::UpdateBlocks()
{
    for(auto it = blocks.begin(); it != blocks.end(); ++it) {
        (*it)(this);
    }
}

void Animator::Update() {
    m_secondsCurrent = m_time.GetEngineStartSec() - m_secondsStart;
    printf("udpate %1.2f seconds\n", m_secondsCurrent);

    m_progress = MIN(1.f, m_secondsCurrent / m_secondsDuration);

    UpdateBlocks();

    if (m_progress >= 1.f) {
        m_endHndlr(this);
        ENGINE().getPeriodicUpdatesManager().Remove(this);
    }
}
