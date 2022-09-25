//
//  animation_factory.cpp
//  Engine
//
//  Created by krzysp on 01/01/2022.
//

#include "value_animator_factory.hpp"
#include "common_engine.h"
#include "callable.hpp"
#include "animation_curve_factory.hpp"

using namespace engine;

ValueAnimatorI *ValueAnimatorFactory::Create(
      CallableCurveLamba *curve
    , float delay
    , float duration
    , std::function<void(ValueAnimatorI*)> functionStartRef
    , std::function<void(ValueAnimatorI*, float)> functionUpdateRef
    , std::function<void(ValueAnimatorI*)> functionEndRef)
{
    ValueAnimator *function = new ValueAnimator(
        std::unique_ptr<CallableCurveLamba>(curve)
      , delay
      , duration
      , functionStartRef
      , functionUpdateRef
      , functionEndRef);
    return function;
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(ValueAnimatorFactory);

static int lua_ValueAnimatorFactory_CreateLinear(lua_State *L)
{
//    ValueAnimatorFactory *obj = ScriptingEngineI::GetScriptingObjectPtr<ValueAnimatorFactory>(L, 1);
//    float min = lua_tonumberx(L, 2, nullptr);
//    float max = lua_tonumberx(L, 3, nullptr);
//    double seconds = lua_tonumberx(L, 4, nullptr);
//    double delay = lua_tonumberx(L, 5, nullptr);
//    int functionEndRef = luaL_ref( L, LUA_REGISTRYINDEX );
//    int functionUpdateRef = luaL_ref( L, LUA_REGISTRYINDEX );
//    ValueAnimator *function = obj->Create(
//        new CallableCurveLamba(min, max, AnimationCurveFactory::Create(LINEAR))
//      , delay
//      , seconds
//      , -1
//      , functionUpdateRef
//      , functionEndRef);
//
//    if (function != nullptr)
//    {
//        ENGINE().getReleasePool().Sink(function);
////        function->ScriptingInterfaceRegisterFunctions(L, function);
//        return 1;
//    }
//    else
//    {
        return 0;
//    }
}

std::vector<luaL_Reg> ValueAnimatorFactory::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        {"CreateLinear", &lua_ValueAnimatorFactory_CreateLinear},
    });
    return result;
}
