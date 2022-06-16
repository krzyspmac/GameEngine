//
//  property_animator.cpp
//  Engine
//
//  Created by krzysp on 04/01/2022.
//

#include "property_animator.hpp"

using namespace engine;

PropertyAnimator::PropertyAnimator(SpritePropertyManipulatorsI *sprite, ValueAnimator *valueAnimator)
    : AnimatableI()
    , m_sprite(nullptr)
    , m_valueAnimator(std::move(valueAnimator))
{
    m_valueAnimator.get()->AnimatableSetFinishLambda([&](AnimatableI *sender){
        auto lambda = this->AnimatableGetFinishLambda();
        if (lambda != nullptr)
        {
            lambda(this);
        }
    });
}

PropertyAnimator::~PropertyAnimator()
{
    printf("PropertyAnimator released\n");
}

void PropertyAnimator::Start()
{
    m_valueAnimator->Start();
}

void PropertyAnimator::Stop()
{
    m_valueAnimator->Stop();
}

void PropertyAnimator::FreeMem()
{
    MemoryI::FreeMem();
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(PropertyAnimator);

static int lua_PropertyAnimator_Start(lua_State *L)
{
    PropertyAnimator *obj = ScriptingEngineI::GetScriptingObjectPtr<PropertyAnimator>(L, 1);
    obj->Start();
    return 0;
}

static int lua_PropertyAnimator_Stop(lua_State *L)
{
    PropertyAnimator *obj = ScriptingEngineI::GetScriptingObjectPtr<PropertyAnimator>(L, 1);
    obj->Stop();
    return 1;
}

static int lua_PropertyAnimator_FreeMem(lua_State *L)
{
    PropertyAnimator *obj = ScriptingEngineI::GetScriptingObjectPtr<PropertyAnimator>(L, 1);
    obj->FreeMem();
    return 1;
}

std::vector<luaL_Reg>PropertyAnimator::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
          {"Start",         &lua_PropertyAnimator_Start}
        , {"Stop",          &lua_PropertyAnimator_Stop}
        , {"FreeMem",       &lua_PropertyAnimator_FreeMem}
    });
    return result;
}
