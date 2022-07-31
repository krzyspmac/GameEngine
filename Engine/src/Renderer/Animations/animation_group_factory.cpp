//
//  animation_group_factory.cpp
//  Engine
//
//  Created by x180611 on 05/01/2022.
//

#include "animation_group_factory.hpp"
#include "animation_group_simulateneus.hpp"
#include "engine.hpp"

using namespace engine;

AnimationGroupSimultaneus* AnimationGroupFactory::GroupAnimationsSimulataneus(
      CallableScriptFunctionSciptableInstance finishFn
    , std::vector<AnimatableI*> args)
{
    AnimationGroupSimultaneus *group = new AnimationGroupSimultaneus(finishFn, args);
    return group;
}

AnimationGroupSequence* AnimationGroupFactory::GroupAnimationsSequence(
      CallableScriptFunctionSciptableInstance finishFn
    , std::vector<AnimatableI*> args)
{
    AnimationGroupSequence *group = new AnimationGroupSequence(finishFn, args);
    return group;
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(AnimationGroupFactory);

static int lua_AnimationGroup_GroupAnimations(lua_State *L)
{
    int argc = lua_gettop(L);
    AnimationGroupFactory *obj = ScriptingEngineI::GetScriptingObjectPtr<AnimationGroupFactory>(L, 1);
    const char *mode = lua_tostring(L, 2);
    
    std::vector<AnimatableI*> list;
    for (int i = 3; i < argc; i++)
    {
        PropertyAnimator *anim = ScriptingEngineI::GetScriptingObjectPtr<PropertyAnimator>(L, i);
        list.emplace_back(anim);
    }
    
    int finishFuncEndRef = luaL_ref( L, LUA_REGISTRYINDEX );

    AnimationGroupI::AnimationGroupMode groupMode = AnimationGroupI::GetGroupTypeFromString(mode);
    switch (groupMode)
    {
        case AnimationGroupI::ANIMATION_SIMULTANEUS:
        {
            AnimationGroupSimultaneus *group = obj->GroupAnimationsSimulataneus(finishFuncEndRef, list);
            if (group != nullptr)
            {
                group->ScriptingInterfaceRegisterFunctions(L, group);
                ENGINE().getReleasePool().Sink(group);
                return 1;
            }
            break;
        }
        case AnimationGroupI::ANIMATION_SEQUENCE:
        {
            AnimationGroupSequence *group = obj->GroupAnimationsSequence(finishFuncEndRef, list);
            if (group != nullptr)
            {
                group->ScriptingInterfaceRegisterFunctions(L, group);
                ENGINE().getReleasePool().Sink(group);
                return 1;
            }
            break;
        }
    }

    return 0;
}

std::vector<luaL_Reg>AnimationGroupFactory::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        {"GroupAnimations",   &lua_AnimationGroup_GroupAnimations}
    });
    return result;
}
