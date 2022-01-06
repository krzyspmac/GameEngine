//
//  animation_group_simulateneus.cpp
//  Engine
//
//  Created by x180611 on 05/01/2022.
//

#include "animation_group_simulateneus.hpp"

using namespace engine;

AnimationGroupSimultaneus::AnimationGroupSimultaneus(CallableScriptFunctionSciptableInstance scriptableFinishFn, std::vector<AnimatableI*> args)
    : AnimationGroupI()
    , MemoryI()
    , m_scriptableGroupFinishFn(scriptableFinishFn)
    , m_cAnimatablesRunning(0)
{
    m_animatables = args;
    Prepare();
}

void AnimationGroupSimultaneus::Start()
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

void AnimationGroupSimultaneus::Stop()
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

void AnimationGroupSimultaneus::Prepare()
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

void AnimationGroupSimultaneus::DidFinish()
{
    if (m_animatableFinishL != nullptr)
    {
        m_animatableFinishL(this);
    }
    if (m_scriptableGroupFinishFn.CanCall())
    {
        m_scriptableGroupFinishFn.PerformCall([&](lua_State *L){
            this->ScriptingInterfaceRegisterFunctions(L, this);
            return 1;
        });
    }
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(AnimationGroupSimultaneus);

static int lua_AnimationGroup_Start(lua_State *L)
{
    AnimationGroupSimultaneus *obj = ScriptingEngineI::GetScriptingObjectPtr<AnimationGroupSimultaneus>(L, 1);
    obj->Start();
    return 0;
}

static int lua_AnimationGroup_Stop(lua_State *L)
{
    AnimationGroupSimultaneus *obj = ScriptingEngineI::GetScriptingObjectPtr<AnimationGroupSimultaneus>(L, 1);
    obj->Stop();
    return 0;
}

static int lua_AnimationGroup_FreeMem(lua_State *L)
{
    AnimationGroupSimultaneus *obj = ScriptingEngineI::GetScriptingObjectPtr<AnimationGroupSimultaneus>(L, 1);
    obj->FreeMem();
    return 0;
}

std::vector<luaL_Reg>AnimationGroupSimultaneus::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
          {"Start",         &lua_AnimationGroup_Start}
        , {"Stop",          &lua_AnimationGroup_Stop}
        , {"FreeMem",       &lua_AnimationGroup_FreeMem}
    });
    return result;
}
