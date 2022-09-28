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

// default include of Pictel-engine namespace
using namespace engine;

// constants
double MAX_SPEED = 20;      // maximum speed (px/s)
double INC_SPEED = 10;      // speed increase when force applied (in px/s)
double DMP_SPEED = 0.05;    // speed fall when force not applied (in px/s)

IntertiaProcessor::IntertiaProcessor()
    : m_position(Vector2::shared())
    , m_movementVector(Vector2::shared())
    , m_forceVector(Vector2::shared())
    , m_time(*engine::Globals::time())
    , m_frameDeltaSec(0.0)
{
    
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
    double speedIncrease = MIN(INC_SPEED, m_frameDeltaSec * INC_SPEED);
    Vector2 incVector = m_forceVector * speedIncrease;
    m_movementVector += incVector;

    /*
    local speedIncrease = math.min(INC_SPEED, self.frameDeltaSec * INC_SPEED)
    local incVector = self.forceVector * speedIncrease
    self.movementVector = self.movementVector + incVector
     */
}

void IntertiaProcessor::Damper()
{
    double dmpFactor = MAX(DMP_SPEED, m_frameDeltaSec * DMP_SPEED);
    Vector2 damperVector = m_movementVector.normalized().inversed() * dmpFactor;
    m_movementVector += damperVector;
    /*
     local dmpFactor = math.max(DMP_SPEED, self.frameDeltaSec * DMP_SPEED)
     local damperVector = self.movementVector:normalized():inversed() * dmpFactor
     self.movementVector = self.movementVector + damperVector
     */
}

void IntertiaProcessor::Limit()
{
    double length = MIN(MAX_SPEED, m_movementVector.length());
    m_movementVector = m_movementVector.normalized() * length;
    /*
    local length = math.min(MAX_SPEED, self.movementVector:length())
    self.movementVector = self.movementVector:normalized() * length
    */
}

void IntertiaProcessor::UpdatePosition()
{
    m_position += m_movementVector;
}
