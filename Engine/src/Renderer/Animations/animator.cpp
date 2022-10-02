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
    m_progress = MIN(1.f, m_secondsCurrent / m_secondsDuration);
    UpdateBlocks();

    if (m_progress >= 1.f) {
        m_endHndlr(this);
        ENGINE().getPeriodicUpdatesManager().Remove(this);
    }
}
