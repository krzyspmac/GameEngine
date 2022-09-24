//
//  time.cpp
//  Engine
//
//  Created by krzysp on 01/01/2022.
//

#include "time_base.hpp"
#include "engine.hpp"

#define MILLI2SEC(m) (double)m/1000.f

using namespace engine;

TimeBase::TimeBase(EngineProviderI &provider)
: m_engineProvider(provider)
{
}

void TimeBase::Prepare()
{
    m_beginning = m_engineProvider.GetTicks();
    m_engineStart = m_beginning;
    m_engineStatSec = MILLI2SEC(m_engineStart);
    m_frameStart = m_engineProvider.GetTicks();
    m_frameStartSec = MILLI2SEC(m_frameStart);
    m_previousFrameStart = m_frameStart;
    m_previousFrameStartSec = MILLI2SEC(m_previousFrameStart);
}

void TimeBase::PreUpdate()
{
    // Get the current frame moment. Assume TimeBase::Update
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

void TimeBase::PostUpdate()
{
    // Store the frame moment for future reference.
    m_previousFrameStart = m_frameStart;
    m_previousFrameStartSec = MILLI2SEC(m_previousFrameStart);
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(TimeBase);

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

std::vector<luaL_Reg> TimeBase::ScriptingInterfaceFunctions()
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
