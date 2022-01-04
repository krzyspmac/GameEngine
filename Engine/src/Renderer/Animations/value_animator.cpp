//
//  animation_function.cpp
//  Engine
//
//  Created by krzysp on 01/01/2022.
//

#include "value_animator.hpp"
#include "scripting_engine.hpp"
#include "engine.hpp"
#include "time.hpp"

using namespace engine;

ValueAnimator::ValueAnimator(std::unique_ptr<CallableCurveLamba> curve, double seconds, int delay, CallableScriptFunctionNumber functionUpdateRef, CallableScriptFunctionSciptableInstance functionEndRef)
    : m_engineProvider(GetMainEngine()->getProvider())
    , m_time(GetMainEngine()->getTime())
    , m_secondsDelay(delay)
    , m_secondsTotal(seconds)
    , m_secondsStart(-1)
    , m_val(curve->GetMin())
    , m_updateFuncRef(functionUpdateRef)
    , m_functionUpdate(nullptr)
    , m_endFuncRef(functionEndRef)
    , m_endFunc(nullptr)
    , m_isStopped(true)
{
    m_curve = std::move(curve);
}

ValueAnimator::ValueAnimator(std::unique_ptr<CallableCurveLamba> curve, double seconds, int delay, std::function<void(float)> functionUpdate, std::function<void(ValueAnimator*)> functionEnd)
    : m_engineProvider(GetMainEngine()->getProvider())
    , m_time(GetMainEngine()->getTime())
    , m_secondsDelay(delay)
    , m_secondsTotal(seconds)
    , m_secondsStart(-1)
    , m_val(curve->GetMin())
    , m_updateFuncRef(CallableScriptFunctionNumber(-1))
    , m_functionUpdate(functionUpdate)
    , m_endFuncRef(CallableScriptFunctionSciptableInstance(-1))
    , m_endFunc(functionEnd)
    , m_isStopped(true)
{
    m_curve = std::move(curve);
}

ValueAnimator::~ValueAnimator()
{
    printf("AnimationFunction released\n");
}

void ValueAnimator::Start()
{
    m_secondsStart = m_time.GetFrameStartSec();
    m_isStopped = false;
    GetMainEngine()->getPeriodicUpdatesManager().Add(this);
}

void ValueAnimator::Stop()
{
    m_isStopped = true;
    GetMainEngine()->getPeriodicUpdatesManager().Remove(this);

    if (m_endFuncRef.CanCall())
    {
        m_endFuncRef.PerformCall([&](lua_State *L){
            this->ScriptingInterfaceRegisterFunctions(L, this);
            return 1;
        });
    }

    if (m_endFunc != nullptr)
    {
        m_endFunc(this);
    }
}

float ValueAnimator::GetValue()
{
    return m_val;
}

void ValueAnimator::CallbackExecute()
{
    if (m_updateFuncRef.CanCall())
    {
        m_updateFuncRef.PerformCall(m_val);
    }

    if (m_functionUpdate != nullptr)
    {
        m_functionUpdate(m_val);
    }
}

void ValueAnimator::ReleaseMem()
{
    if (!m_isStopped) { Stop(); };
    MemoryI::ReleaseMem();
}

void ValueAnimator::Update()
{
    double diffSeconds = MAX(m_time.GetFrameStartSec() - m_secondsStart - m_secondsDelay, 0);
    double progress = diffSeconds / m_secondsTotal;

    m_val = m_curve->f(progress);
    CallbackExecute();

    if (diffSeconds >= m_secondsTotal)
    {
        Stop();
    }
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(ValueAnimator);

static int lua_AnimationFactory_Start(lua_State *L)
{
    ValueAnimator *obj = ScriptingEngineI::GetScriptingObjectPtr<ValueAnimator>(L, 1);
    obj->Start();
    return 0;
}

static int lua_AnimationFactory_Stop(lua_State *L)
{
    ValueAnimator *obj = ScriptingEngineI::GetScriptingObjectPtr<ValueAnimator>(L, 1);
    obj->Stop();
    return 0;
}

static int lua_AnimationFactory_GetValue(lua_State *L)
{
    ValueAnimator *obj = ScriptingEngineI::GetScriptingObjectPtr<ValueAnimator>(L, 1);
    float f = obj->GetValue();
    lua_pushnumber(L, f);
    return 1;
}

static int lua_AnimationFactory_ReleaseMem(lua_State *L)
{
    ValueAnimator *obj = ScriptingEngineI::GetScriptingObjectPtr<ValueAnimator>(L, 1);
    obj->ReleaseMem();
    return 0;
}

std::vector<luaL_Reg> ValueAnimator::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        {"Start", &lua_AnimationFactory_Start},
        {"Stop", &lua_AnimationFactory_Stop},
        {"GetValue", &lua_AnimationFactory_GetValue},
        {"ReleaseMem", &lua_AnimationFactory_ReleaseMem},

    });
    return result;
}

