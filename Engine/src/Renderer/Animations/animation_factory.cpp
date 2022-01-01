//
//  animation_factory.cpp
//  Engine
//
//  Created by krzysp on 01/01/2022.
//

#include "animation_factory.hpp"
#include "animation_curve_function_linear.hpp"

using namespace engine;

AnimationFunction *AnimationFactory::CreateLinear(float min, float max, double seconds, int functionUpdateRef, int functionEndRef)
{
    AnimationCurveFunctionI *linear = new AnimationCurveFunctionLinear(min, max);
    AnimationFunction *function = new AnimationFunction(std::unique_ptr<AnimationCurveFunctionI>(linear), seconds, functionUpdateRef, functionEndRef);
    return function;
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(AnimationFactory);

static int lua_AnimationFactory_CreateLinear(lua_State *L)
{
    AnimationFactory *obj = ScriptingEngineI::GetScriptingObjectPtr<AnimationFactory>(L, 1);
    float min = lua_tonumberx(L, 2, nullptr);
    float max = lua_tonumberx(L, 3, nullptr);
    double seconds = lua_tonumberx(L, 4, nullptr);
    int functionEndRef = luaL_ref( L, LUA_REGISTRYINDEX );
    int functionUpdateRef = luaL_ref( L, LUA_REGISTRYINDEX );
    AnimationFunction *function = obj->CreateLinear(min, max, seconds, functionUpdateRef, functionEndRef);
    function->ScriptingInterfaceRegisterFunctions(L, function);
    return 1;
}

std::vector<luaL_Reg> AnimationFactory::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        {"CreateLinear", &lua_AnimationFactory_CreateLinear},
    });
    return result;
}
