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
CallableScriptFunctionSciptableInstance scriptableFinishFn
    , std::vector<AnimatableI*> args)
{
    AnimationGroupSimultaneus *group = new AnimationGroupSimultaneus(scriptableFinishFn, args);
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

    AnimationGroupSimultaneus *group = new AnimationGroupSimultaneus(finishFuncEndRef, list);
    if (group != nullptr)
    {
        group->ScriptingInterfaceRegisterFunctions(L, group);
        GetMainEngine()->getReleasePool().Sink(group);
        return 1;
    }
    else
    {
        return 0;
    }
}

static int lua_AnimationGroup_Stop(lua_State *L)
{
//    AnimationGroup *obj = ScriptingEngineI::GetScriptingObjectPtr<AnimationGroup>(L, 1);
//    obj->Stop();
    return 0;
}

static int lua_AnimationGroup_FreeMem(lua_State *L)
{
//    AnimationGroup *obj = ScriptingEngineI::GetScriptingObjectPtr<AnimationGroup>(L, 1);
//    obj->FreeMem();
    return 0;
}

std::vector<luaL_Reg>AnimationGroupFactory::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        {"GroupAnimations",   &lua_AnimationGroup_GroupAnimations}
    });
    return result;
}
