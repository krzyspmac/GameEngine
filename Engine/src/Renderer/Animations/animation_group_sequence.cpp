//
//  animation_group_sequence.cpp
//  Engine
//
//  Created by krzysp on 06/01/2022.
//

#include "animation_group_sequence.hpp"

using namespace engine;

AnimationGroupSequence::AnimationGroupSequence(CallableScriptFunctionSciptableInstance scriptableFinishFn, std::vector<AnimatableI*> args)
    : AnimationGroupI()
    , MemoryI()
    , m_scriptableGroupFinishFn(scriptableFinishFn)
    , m_iCurrentAnimatable(0)
{
    m_animatables = args;
    Prepare();
}

void AnimationGroupSequence::Start()
{
    m_iCurrentAnimatable = 0;
    PlayCurrent();
}

void AnimationGroupSequence::PlayCurrent()
{
    if (m_iCurrentAnimatable < m_animatables.size())
    {
        AnimatableI *anim = m_animatables.at(m_iCurrentAnimatable);
        if (anim != nullptr) {
            printf("Starting animation indexed %zu\n", this->m_iCurrentAnimatable);
            anim->Start();
        };
    }
    else
    {
        DidFinish();
    }
}

void AnimationGroupSequence::PlayNext()
{
    if (++m_iCurrentAnimatable < m_animatables.size())
    {
        PlayCurrent();
    }
    else
    {
        DidFinish();
    }
}

void AnimationGroupSequence::Stop()
{
    if (m_iCurrentAnimatable < m_animatables.size())
    {
        AnimatableI *anim = m_animatables.at(m_iCurrentAnimatable);
        if (anim != nullptr) { anim->Stop(); };
    }
}

void AnimationGroupSequence::Prepare()
{
    for (auto it = m_animatables.begin(); it != m_animatables.end(); ++it)
    {
        AnimatableI *anim = (*it);
        anim->AnimatableSetFinishLambda([&](AnimatableI *a){
            printf("Finished animation indexed %zu\n", this->m_iCurrentAnimatable);
            this->PlayNext();
        });
    }
}

void AnimationGroupSequence::DidFinish()
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

SCRIPTING_INTERFACE_IMPL_NAME(AnimationGroupSequence);

static int lua_AnimationGroup_Start(lua_State *L)
{
    AnimationGroupSequence *obj = ScriptingEngineI::GetScriptingObjectPtr<AnimationGroupSequence>(L, 1);
    obj->Start();
    return 0;
}

static int lua_AnimationGroup_Stop(lua_State *L)
{
    AnimationGroupSequence *obj = ScriptingEngineI::GetScriptingObjectPtr<AnimationGroupSequence>(L, 1);
    obj->Stop();
    return 0;
}

static int lua_AnimationGroup_FreeMem(lua_State *L)
{
    AnimationGroupSequence *obj = ScriptingEngineI::GetScriptingObjectPtr<AnimationGroupSequence>(L, 1);
    obj->FreeMem();
    return 0;
}

std::vector<luaL_Reg>AnimationGroupSequence::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
          {"Start",         &lua_AnimationGroup_Start}
        , {"Stop",          &lua_AnimationGroup_Stop}
        , {"FreeMem",       &lua_AnimationGroup_FreeMem}
    });
    return result;
}

