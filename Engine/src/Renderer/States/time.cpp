//
//  time_export.cpp
//  Engine
//
//  Created by krzysp on 24/09/2022.
//

#include "time.hpp"

using namespace engine;

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
