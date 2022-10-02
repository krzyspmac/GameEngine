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

#include "time.hpp"
#include "engine.hpp"

#define MILLI2SEC(m) (double)m/1000.f

using namespace engine;

Time::Time(EngineProviderI &provider)
: m_engineProvider(provider)
{
}

void Time::Prepare()
{
    m_beginning = m_engineProvider.GetTicks();
    m_engineStart = m_beginning;
    m_engineStatSec = MILLI2SEC(m_engineStart);
    m_frameStart = m_engineProvider.GetTicks();
    m_frameStartSec = MILLI2SEC(m_frameStart);
    m_previousFrameStart = m_frameStart;
    m_previousFrameStartSec = MILLI2SEC(m_previousFrameStart);
}

Uint64 Time::GetEngineStart()
{
    return m_engineStart;
}

double Time::GetEngineStartSec()
{
    return m_engineStatSec;
}

Uint64 Time::GetFrameStart()
{
    return m_frameStart;
}

double Time::GetFrameStartSec()
{
    return m_frameStartSec;
}

Uint64 Time::GetFrameDelta() {
    return m_frameDelta;
};

double Time::GetFrameDeltaSec()
{
    return m_frameDeltaSec;
}

void Time::PreUpdate()
{
    // Get the current frame moment. Assume Time::Update
    // is the first thing to be updated in the udpate
    // queue.
    m_frameStart = m_engineProvider.GetTicks();
    m_frameStartSec = MILLI2SEC(m_frameStart);

    // Get the difference between frames
    m_frameDelta = m_frameStart - m_previousFrameStart;
    m_frameDeltaSec = MILLI2SEC(m_frameDelta);

    // Get the time betwen the engine start and the current frame
    m_engineStart = m_frameStart - m_beginning;
    m_engineStatSec = MILLI2SEC(m_engineStart);
}

void Time::PostUpdate()
{
    // Store the frame moment for future reference.
    m_previousFrameStart = m_frameStart;
    m_previousFrameStartSec = MILLI2SEC(m_previousFrameStart);
}
