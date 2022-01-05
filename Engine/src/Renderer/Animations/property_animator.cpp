//
//  property_animator.cpp
//  Engine
//
//  Created by krzysp on 04/01/2022.
//

#include "property_animator.hpp"

using namespace engine;

PropertyAnimator::PropertyAnimator(SpriteDrawI *sprite, ValueAnimator *valueAnimator)
    : m_sprite(sprite)
    , m_valueAnimator(valueAnimator)
{
}

void PropertyAnimator::Start()
{
    m_valueAnimator->Start();
}

void PropertyAnimator::Stop()
{
    m_valueAnimator->Stop();
}

void PropertyAnimator::ReleaseMem()
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

static int lua_PropertyAnimator_ReleaseMem(lua_State *L)
{
    PropertyAnimator *obj = ScriptingEngineI::GetScriptingObjectPtr<PropertyAnimator>(L, 1);
    obj->ReleaseMem();
    return 1;
}

std::vector<luaL_Reg>PropertyAnimator::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
          {"Start",         &lua_PropertyAnimator_Start}
        , {"Stop",          &lua_PropertyAnimator_Stop}
        , {"ReleaseMem",    &lua_PropertyAnimator_ReleaseMem}
    });
    return result;
}
