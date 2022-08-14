//
//  property_animator_multiple.cpp
//  Engine-Mac
//
//  Created by krzysp on 12/08/2022.
//

#include "property_animator_multiple.hpp"

using namespace engine;

PropertyMultipleAnimator::PropertyMultipleAnimator(
    AnimatablePropertiesI* animatable,
    std::vector<ValueAnimator*> animators
)   : m_animatorsFinished(0)
{
    for (auto it = std::begin(animators); it != std::end(animators); it++)
    {
        m_animators.emplace_back(std::move(*it));
    }

    for (auto it = std::begin(m_animators); it != std::end(m_animators); it++)
    {
        auto animator = it->get();

        animator->AnimatableSetFinishLambda([&](AnimatableI *sender){
            auto lambda = this->AnimatableGetFinishLambda();
            if (lambda != nullptr)
            {
                m_animatorsFinished++;
                if (m_animatorsFinished >= m_animators.size())
                {   lambda(this);
                }
            }
        });
    }
}

PropertyMultipleAnimator::~PropertyMultipleAnimator()
{
    printf("PropertyAnimator released\n");
}

void PropertyMultipleAnimator::Start()
{
    for (auto it = std::begin(m_animators); it != std::end(m_animators); it++)
    {   it->get()->Start();
    }
}

void PropertyMultipleAnimator::Stop()
{
    for (auto it = std::begin(m_animators); it != std::end(m_animators); it++)
    {   it->get()->Stop();
    }
}

void PropertyMultipleAnimator::FreeMem()
{
    MemoryI::FreeMem();
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(PropertyMultipleAnimator);

static int lua_PropertyAnimator_Start(lua_State *L)
{
    PropertyMultipleAnimator *obj = ScriptingEngineI::GetScriptingObjectPtr<PropertyMultipleAnimator>(L, 1);
    obj->Start();
    return 0;
}

static int lua_PropertyAnimator_Stop(lua_State *L)
{
    PropertyMultipleAnimator *obj = ScriptingEngineI::GetScriptingObjectPtr<PropertyMultipleAnimator>(L, 1);
    obj->Stop();
    return 1;
}

static int lua_PropertyAnimator_FreeMem(lua_State *L)
{
    PropertyMultipleAnimator *obj = ScriptingEngineI::GetScriptingObjectPtr<PropertyMultipleAnimator>(L, 1);
    obj->FreeMem();
    return 1;
}

std::vector<luaL_Reg>PropertyMultipleAnimator::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
          {"Start",         &lua_PropertyAnimator_Start}
        , {"Stop",          &lua_PropertyAnimator_Stop}
        , {"FreeMem",       &lua_PropertyAnimator_FreeMem}
    });
    return result;
}
