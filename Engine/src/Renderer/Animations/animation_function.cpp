//
//  animation_function.cpp
//  Engine
//
//  Created by krzysp on 01/01/2022.
//

#include "animation_function.hpp"
#include "scripting_engine.hpp"
#include "engine.hpp"
#include "time.hpp"

using namespace engine;

AnimationFunction::AnimationFunction(std::unique_ptr<AnimationCurveFunctionI> curve, double seconds, int functionUpdateRef, int functionEndRef)
    :   m_engineProvider(GetMainEngine()->getProvider()),
        m_time(GetMainEngine()->getTime()),
        m_secondsTotal(seconds),
        m_secondsStart(-1),
        m_val(curve->GetMin()),
        m_updateFuncRef(functionUpdateRef),
        m_endFuncRef(functionEndRef),
        m_isStopped(true)
{
    m_curve = std::move(curve);
}

AnimationFunction::~AnimationFunction()
{
    printf("AnimationFunction released\n");
}

void AnimationFunction::Start()
{
    m_secondsStart = m_time.GetFrameStartSec();
    m_isStopped = false;
    GetMainEngine()->getPeriodicUpdatesManager().Add(this);
}

void AnimationFunction::Stop()
{
    m_isStopped = true;
    GetMainEngine()->getPeriodicUpdatesManager().Remove(this);

    ScriptingEngine& se = (ScriptingEngine&)GetMainEngine()->getScripting();
    se.CallRegistryFunction(m_endFuncRef, [&](lua_State *L){
        return 0;
    });
}

float AnimationFunction::GetValue()
{
    return m_val;
}

void AnimationFunction::CallbackExecute()
{
    if (m_updateFuncRef < 0) { return; };

    ScriptingEngine& se = (ScriptingEngine&)GetMainEngine()->getScripting();
    se.CallRegistryFunction(m_updateFuncRef, [&](lua_State *L){
        lua_pushnumber(L, m_val);
        return 1;
    });
}

void AnimationFunction::ReleaseMem()
{
    if (!m_isStopped) { Stop(); };
    delete this;
}

void AnimationFunction::Update()
{
    double diffSeconds = m_time.GetFrameStartSec() - m_secondsStart;
    double progress = diffSeconds / m_secondsTotal;

    m_val = m_curve->f(progress);
    CallbackExecute();

    if (m_val >= m_curve->GetMax())
    {
        Stop();
    }
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(AnimationFunction);

static int lua_AnimationFactory_Start(lua_State *L)
{
    AnimationFunction *obj = ScriptingEngineI::GetScriptingObjectPtr<AnimationFunction>(L, 1);
    obj->Start();
    return 0;
}

static int lua_AnimationFactory_Stop(lua_State *L)
{
    AnimationFunction *obj = ScriptingEngineI::GetScriptingObjectPtr<AnimationFunction>(L, 1);
    obj->Stop();
    return 0;
}

static int lua_AnimationFactory_GetValue(lua_State *L)
{
    AnimationFunction *obj = ScriptingEngineI::GetScriptingObjectPtr<AnimationFunction>(L, 1);
    float f = obj->GetValue();
    lua_pushnumber(L, f);
    return 1;
}

static int lua_AnimationFactory_ReleaseMem(lua_State *L)
{
    AnimationFunction *obj = ScriptingEngineI::GetScriptingObjectPtr<AnimationFunction>(L, 1);
    obj->ReleaseMem();
    return 0;
}

std::vector<luaL_Reg> AnimationFunction::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        {"Start", &lua_AnimationFactory_Start},
        {"Stop", &lua_AnimationFactory_Stop},
        {"GetValue", &lua_AnimationFactory_GetValue},
        {"ReleaseMem", &lua_AnimationFactory_ReleaseMem},

    });
    return result;
}

