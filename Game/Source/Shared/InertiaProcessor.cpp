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

#include "InertiaProcessor.hpp"

using namespace engine;

IntertiaProcessor::IntertiaProcessor(IntertiaProcessorDescriptor descriptor)
    : m_descriptor(descriptor)
    , m_position(Vector2::zero())
    , m_movementVector(Vector2::zero())
    , m_forceVector(Vector2::zero())
    , m_time(*engine::Globals::time())
    , m_frameDeltaSec(0.0)
{
}

void IntertiaProcessor::SetPosition(engine::Vector2 vector)
{
    m_position = vector;
}

void IntertiaProcessor::UpdateForceVector(engine::Vector2 vector)
{
    m_forceVector = vector;
}

void IntertiaProcessor::Tick()
{
    m_frameDeltaSec = m_time.GetFrameDeltaSec();
    Advance();
    Damper();
    Limit();
    UpdatePosition();
}

void IntertiaProcessor::Advance()
{
    double inc_speed = m_descriptor.inc_speed;
    double speedIncrease = MIN(inc_speed, m_frameDeltaSec * inc_speed);
    Vector2 incVector = m_forceVector * speedIncrease;
    m_movementVector += incVector;
}

void IntertiaProcessor::Damper()
{
    double dmp_speed = m_descriptor.dmp_speed;
    double dmpFactor = MAX(dmp_speed, m_frameDeltaSec * dmp_speed);
    Vector2 damperVector = m_movementVector.normalized().inversed() * dmpFactor;
    m_movementVector += damperVector;
}

void IntertiaProcessor::Limit()
{
    double max_speed = m_descriptor.max_speed;
    double length = MIN(max_speed, m_movementVector.length());
    m_movementVector = m_movementVector.normalized() * length;
}

void IntertiaProcessor::UpdatePosition()
{
    m_position += m_movementVector;
}
