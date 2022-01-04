//
//  callable.cpp
//  Engine
//
//  Created by krzysp on 04/01/2022.
//

#include <math.h>
#include "callable.hpp"
#include "scripting_engine.hpp"
#include "common.h"

using namespace engine;

CallableCurveLamba::CallableCurveLamba(float min, float max, std::function<float(float, float, float)> lambda)
    : CallableCurveI<float, float>()
    , m_lambda(lambda)
    , m_min(min)
    , m_max(max)
    , m_diff(fabsf(max - min))
{
}

float CallableCurveLamba::f(float progress)
{
    return m_lambda(m_min, m_max, progress);
}

/**
 */
CallableScriptFunctionParamless::CallableScriptFunctionParamless(CallableScriptFunctionRef ref)
    : CallableScriptFunctionI(ref)
    , m_ref(ref)
{
}

void CallableScriptFunctionParamless::PerformCall()
{
    ScriptingEngine& se = (ScriptingEngine&)GetMainEngine()->getScripting();
    se.CallRegistryFunction(GetFunctionRef(), [&](lua_State *L){
        return 0;
    });
}

/**
 */
CallableScriptFunctionNumber::CallableScriptFunctionNumber(CallableScriptFunctionRef ref)
   : CallableScriptFunctionI(ref)
   , m_ref(ref)
{
}

void CallableScriptFunctionNumber::PerformCall(float val)
{
    if (m_ref < -1) { return; };

    ScriptingEngine& se = (ScriptingEngine&)GetMainEngine()->getScripting();
    se.CallRegistryFunction((int)GetFunctionRef(), [&](lua_State *L){
        lua_pushnumber(L, val);
        return 1;
    });
}

/**
 */
CallableScriptFunctionSciptableInstance::CallableScriptFunctionSciptableInstance(CallableScriptFunctionRef ref)
   : CallableScriptFunctionI(ref)
   , m_ref(ref)
{
}

void CallableScriptFunctionSciptableInstance::PerformCall(std::function<int(lua_State*)> block)
{
    if (m_ref < -1) { return; };

    ScriptingEngine& se = (ScriptingEngine&)GetMainEngine()->getScripting();
    se.CallRegistryFunction((int)GetFunctionRef(), [&](lua_State *L){
        return block(L);
    });
}
