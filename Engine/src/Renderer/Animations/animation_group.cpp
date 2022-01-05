//
//  animation_group.cpp
//  Engine
//
//  Created by x180611 on 05/01/2022.
//

#include "animation_group.hpp"

using namespace engine;

AnimationGroup::AnimationGroup(AnimationGroupMode mode, CallableScriptFunctionSciptableInstance scriptableFinishFn, std::vector<AnimatableI*> args)
    : AnimationGroupI()
    , MemoryI()
    , m_scriptableFinishFn(scriptableFinishFn)
    , m_cAnimatablesRunning(0)
{
    m_animatables = args;
}

AnimationGroup::AnimationGroup(std::string mode,
    CallableScriptFunctionSciptableInstance scriptableFinishFn,
    std::vector<AnimatableI*> args)
    : AnimationGroupI()
    , MemoryI()
    , m_scriptableFinishFn(scriptableFinishFn)
    , m_cAnimatablesRunning(0)
{
    m_animatables = args;
    Prepare();
}

void AnimationGroup::Start()
{
    for (auto it = m_animatables.begin(); it != m_animatables.end(); ++it)
    {
        AnimatableI *anim = (*it);
        if (!anim->IsRunning())
        {
            anim->Start();
            m_cAnimatablesRunning++;
        }
    }
}

void AnimationGroup::Stop()
{
    for (auto it = m_animatables.begin(); it != m_animatables.end(); ++it)
    {
        AnimatableI *anim = (*it);
        if (anim->IsRunning())
        {
            anim->Stop();
            m_cAnimatablesRunning--;
        }
    }
}

void AnimationGroup::Prepare()
{
    for (auto it = m_animatables.begin(); it != m_animatables.end(); ++it)
    {
        AnimatableI *anim = (*it);
        anim->AnimatableSetFinishLambda([&](AnimatableI *a){
            m_cAnimatablesRunning--;
            if (m_cAnimatablesRunning <= 0)
            {
                this->DidFinish();
            }
        });
    }
}

void AnimationGroup::DidFinish()
{
    if (m_animatableFinishL != nullptr)
    {
        m_animatableFinishL(this);
    }
    if (m_scriptableFinishFn.CanCall())
    {
        m_scriptableFinishFn.PerformCall([&](lua_State *L){
            this->ScriptingInterfaceRegisterFunctions(L, this);
            return 1;
        });
    }
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(AnimationGroup);

static int lua_AnimationGroup_Start(lua_State *L)
{
    AnimationGroup *obj = ScriptingEngineI::GetScriptingObjectPtr<AnimationGroup>(L, 1);
    obj->Start();
    return 0;
}

static int lua_AnimationGroup_Stop(lua_State *L)
{
    AnimationGroup *obj = ScriptingEngineI::GetScriptingObjectPtr<AnimationGroup>(L, 1);
    obj->Stop();
    return 0;
}

static int lua_AnimationGroup_FreeMem(lua_State *L)
{
    AnimationGroup *obj = ScriptingEngineI::GetScriptingObjectPtr<AnimationGroup>(L, 1);
    obj->FreeMem();
    return 0;
}

std::vector<luaL_Reg>AnimationGroup::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
          {"Start",         &lua_AnimationGroup_Start}
        , {"Stop",          &lua_AnimationGroup_Stop}
        , {"FreeMem",       &lua_AnimationGroup_FreeMem}
    });
    return result;
}
