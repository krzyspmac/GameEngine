//
//  animation_factory.cpp
//  Engine
//
//  Created by krzysp on 01/01/2022.
//

#include "value_animator_factory.hpp"
#include "common_engine.h"
#include "callable.hpp"

using namespace engine;

ValueAnimator *ValueAnimatorFactory::CreateLinear(float min, float max, double seconds, int delay, CallableScriptFunctionNumber functionUpdateRef, CallableScriptFunctionSciptableInstance functionEndRef)
{
    CallableCurveLamba *s = new CallableCurveLamba(min, max, [&](float min, float max, float progress){
        float m_diff = fabsf(max - min);
        if (min > max)
        {
            float result = min - progress * m_diff;
            return result;
        }
        else
        {
            return min + MAX(0, MIN(max, progress * m_diff));
        }
    });
    ValueAnimator *function = new ValueAnimator(std::unique_ptr<CallableCurveLamba>(s), seconds, delay, functionUpdateRef, functionEndRef);
    GetMainEngine()->getReleasePool().Sink(function);
    return function;
}

ValueAnimator *ValueAnimatorFactory::CreateLinear(float min, float max, double seconds, int delay, std::function<void(float)> functionUpdateRef, std::function<void(ValueAnimator*)> functionEndRef)
{
    CallableCurveLamba *s = new CallableCurveLamba(min, max, [&](float min, float max, float progress){
        float m_diff = fabsf(max - min);
        if (min > max)
        {
            float result = min - progress * m_diff;
            return result;
        }
        else
        {
            return min + MAX(0, MIN(max, progress * m_diff));
        }
    });

    ValueAnimator *function = new ValueAnimator(std::unique_ptr<CallableCurveLamba>(s), seconds, delay, functionUpdateRef, functionEndRef);
    GetMainEngine()->getReleasePool().Sink(function);
    return function;
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(ValueAnimatorFactory);

static int lua_AnimationFactory_CreateLinear(lua_State *L)
{
    ValueAnimatorFactory *obj = ScriptingEngineI::GetScriptingObjectPtr<ValueAnimatorFactory>(L, 1);
    float min = lua_tonumberx(L, 2, nullptr);
    float max = lua_tonumberx(L, 3, nullptr);
    double seconds = lua_tonumberx(L, 4, nullptr);
    double delay = lua_tonumberx(L, 5, nullptr);
    int functionEndRef = luaL_ref( L, LUA_REGISTRYINDEX );
    int functionUpdateRef = luaL_ref( L, LUA_REGISTRYINDEX );
    ValueAnimator *function = obj->CreateLinear(min, max, seconds, delay, functionUpdateRef, functionEndRef);
    function->ScriptingInterfaceRegisterFunctions(L, function);
    return 1;
}

std::vector<luaL_Reg> ValueAnimatorFactory::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        {"CreateLinear", &lua_AnimationFactory_CreateLinear},
    });
    return result;
}
