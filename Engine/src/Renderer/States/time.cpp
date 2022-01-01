//
//  time.cpp
//  Engine
//
//  Created by krzysp on 01/01/2022.
//

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

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(Time);

static int lua_Time_GetEngineStart(lua_State *L)
{
    Time *time = ScriptingEngineI::GetScriptingObjectPtr<Time>(L, 1);
    lua_pushnumber(L, time->GetEngineStart());
    return 1;
}

static int lua_Time_GetEngineStartSec(lua_State *L)
{
    Time *time = ScriptingEngineI::GetScriptingObjectPtr<Time>(L, 1);
    lua_pushnumber(L, time->GetEngineStartSec());
    return 1;
}

static int lua_Time_GetFrameStart(lua_State *L)
{
    Time *time = ScriptingEngineI::GetScriptingObjectPtr<Time>(L, 1);
    lua_pushnumber(L, time->GetFrameStart());
    return 1;
}

static int lua_Time_GetFrameStartSec(lua_State *L)
{
    Time *time = ScriptingEngineI::GetScriptingObjectPtr<Time>(L, 1);
    lua_pushnumber(L, time->GetFrameStartSec());
    return 1;
}

static int lua_Time_GetFrameDelta(lua_State *L)
{
    Time *time = ScriptingEngineI::GetScriptingObjectPtr<Time>(L, 1);
    lua_pushnumber(L, time->GetFrameDelta());
    return 1;
}

static int lua_Time_GetFrameDeltaSec(lua_State *L)
{
    Time *time = ScriptingEngineI::GetScriptingObjectPtr<Time>(L, 1);
    lua_pushnumber(L, time->GetFrameDeltaSec());
    return 1;
}

std::vector<luaL_Reg> Time::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "GetEngineStart",     &lua_Time_GetEngineStart },
        { "GetEngineStartSec",  &lua_Time_GetEngineStartSec },
        { "GetFrameStart",      &lua_Time_GetFrameStart },
        { "GetFrameStartSec",   &lua_Time_GetFrameStartSec },
        { "GetFrameDelta",      &lua_Time_GetFrameDelta },
        { "GetFrameDeltaSec",   &lua_Time_GetFrameDeltaSec }
    });
    return result;
}
