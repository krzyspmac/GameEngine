//
//  property_animator_factory.cpp
//  Engine
//
//  Created by krzysp on 04/01/2022.
//

#include "property_animator_factory.hpp"
#include "sprite_representation_static.hpp"
#include "animation_curve_factory.hpp"
#include "animation_interface.h"
#include "engine.hpp"

using namespace engine;

PropertyAnimator *PropertyAnimatorFactory
    ::FadeIn( AnimatablePropertiesI *sprite
            , std::string curveType
            , float delay
            , float duration
            , CallableScriptFunctionParametersEmpty fFinishRef)
{
    AnimatablePropertiesI &spr = *sprite;
    CallableCurveLamba *curve = new CallableCurveLamba(0, 1, AnimationCurveFactory::Create(curveType));
    ValueAnimator *linearAnimator = ENGINE().getValueAnimatorFactory()
        .Create(
                  curve
                , delay
                , duration
                , [&](float val) { spr.SetAlpha(val); }
                , nullptr);
    linearAnimator->SetFunctionFinish(fFinishRef);

    PropertyAnimator *result = new PropertyAnimator(sprite, linearAnimator);
    return result;
}

PropertyAnimator *PropertyAnimatorFactory
    ::FadeOut(  AnimatablePropertiesI *sprite
              , std::string curveType
              , float delay
              , float duration
              , CallableScriptFunctionParametersEmpty fFinishRef)
{
    AnimatablePropertiesI &spr = *sprite;
    CallableCurveLamba *curve = new CallableCurveLamba(1, 0, AnimationCurveFactory::Create(curveType));
    ValueAnimator *linearAnimator = ENGINE().getValueAnimatorFactory()
        .Create(
                  curve
                , delay
                , duration
                , [&](float val) { spr.SetAlpha(val); }
                , nullptr);
    linearAnimator->SetFunctionFinish(fFinishRef);

    PropertyAnimator *result = new PropertyAnimator(sprite, linearAnimator);
    return result;
}

PropertyMultipleAnimator *PropertyAnimatorFactory
    ::SetPosition(  AnimatablePropertiesI *sprite
                  , std::string curveType
                  , Vector2 offset
                  , float delay
                  , float duration
                  , CallableScriptFunctionParametersEmpty fFinishRef)
{
    AnimatablePropertiesI &spr = *sprite;

    auto startingOffset = sprite->GetPosition();

    CallableCurveLamba *curveX = new CallableCurveLamba(startingOffset.x, offset.x, AnimationCurveFactory::Create(curveType));
    ValueAnimator *linearAnimatorX = ENGINE().getValueAnimatorFactory()
        .Create(
                  curveX
                , delay
                , duration
                , [&](float val) {
                    spr.SetPosition({val, spr.GetPosition().y});
                }
                , nullptr);
    linearAnimatorX->SetFunctionFinish(fFinishRef);

    CallableCurveLamba *curveY = new CallableCurveLamba(startingOffset.y, offset.y, AnimationCurveFactory::Create(curveType));
    ValueAnimator *linearAnimatorY = ENGINE().getValueAnimatorFactory()
        .Create(
                  curveY
                , delay
                , duration
                , [&](float val) {
                    spr.SetPosition({spr.GetPosition().x, val});
                }
                , nullptr);
    linearAnimatorY->SetFunctionFinish(fFinishRef);

    std::vector<ValueAnimator*> list;
    list.emplace_back(linearAnimatorX);
    list.emplace_back(linearAnimatorY);

    PropertyMultipleAnimator *result = new PropertyMultipleAnimator(
         sprite
       , list
    );

    return result;
}

PropertyAnimator *SetPosition(AnimatablePropertiesI *object,
                              std::string curveType,
                              Vector2 offset,
                              float delay,
                              float duration,
                              CallableScriptFunctionParametersEmpty fFinishRef
                              );


PropertyAnimator *PropertyAnimatorFactory
    ::Wait(float delay, float duration, CallableScriptFunctionParametersEmpty fFinishRef)
{
    CallableCurveLamba *curve = new CallableCurveLamba(1, 0, AnimationCurveFactory::Create(LINEAR));
    ValueAnimator *linearAnimator = ENGINE().getValueAnimatorFactory()
        .Create(
                  curve
                , delay
                , duration
                , [&](float val) { }
                , nullptr);
    linearAnimator->SetFunctionFinish(fFinishRef);

    PropertyAnimator *result = new PropertyAnimator(nullptr, linearAnimator);
    return result;
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(PropertyAnimatorFactory);

static int lua_PropertyAnimatorFactory_FadeIn(lua_State *L)
{
    int argc = lua_gettop(L);
    PropertyAnimatorFactory *obj = ScriptingEngineI::GetScriptingObjectPtr<PropertyAnimatorFactory>(L, 1);
    SpritePropertyManipulatorsI **spriteDrawPtr = (SpritePropertyManipulatorsI**)lua_touserdata(L, 2);
    SpritePropertyManipulatorsI *spriteDraw = *spriteDrawPtr;

    std::string curveType = lua_tostring(L, 3); // linear
    float delay = lua_tonumberx(L, 4, NULL);
    float duration = lua_tonumberx(L, 5, NULL);

    CallableScriptFunctionParametersEmpty function = CallableScriptFunctionParametersEmpty::empty();
    int functionEndRef = luaL_ref( L, LUA_REGISTRYINDEX );
    if (argc > 4)
    {
        function = CallableScriptFunctionParametersEmpty(functionEndRef);
    }

    PropertyAnimator *result = obj->FadeIn(spriteDraw, curveType, delay, duration, function);
    if (result != nullptr)
    {
        ENGINE().getReleasePool().Sink(result);
        result->ScriptingInterfaceRegisterFunctions(L, result);
        return 1;
    }
    else
    {
        return 0;
    }
}

static int lua_PropertyAnimatorFactory_FadeOut(lua_State *L)
{
    int argc = lua_gettop(L);
    PropertyAnimatorFactory *obj = ScriptingEngineI::GetScriptingObjectPtr<PropertyAnimatorFactory>(L, 1);
    SpritePropertyManipulatorsI **spriteDrawPtr = (SpritePropertyManipulatorsI**)lua_touserdata(L, 2);
    SpritePropertyManipulatorsI *spriteDraw = *spriteDrawPtr;

    std::string curveType = lua_tostring(L, 3); // linear
    float delay = lua_tonumberx(L, 4, NULL);
    float duration = lua_tonumberx(L, 5, NULL);

    CallableScriptFunctionParametersEmpty function = CallableScriptFunctionParametersEmpty::empty();
    int functionEndRef = luaL_ref( L, LUA_REGISTRYINDEX );
    if (argc > 4)
    {
        function = CallableScriptFunctionParametersEmpty(functionEndRef);
    }

    PropertyAnimator *result = obj->FadeOut(spriteDraw, "linear", delay, duration, function);
    if (result)
    {
        ENGINE().getReleasePool().Sink(result);
        result->ScriptingInterfaceRegisterFunctions(L, result);
        return 1;
    }
    else
    {
        return 0;
    }
}

static int lua_PropertyAnimatorFactory_SetPosition(lua_State *L)
{
    int argc = lua_gettop(L);
    PropertyAnimatorFactory *obj = ScriptingEngineI::GetScriptingObjectPtr<PropertyAnimatorFactory>(L, 1);
    AnimatablePropertiesI **spriteDrawPtr = (AnimatablePropertiesI**)lua_touserdata(L, 2);
    AnimatablePropertiesI *spriteDraw = *spriteDrawPtr;

    std::string curveType = lua_tostring(L, 3); // linear
    float x = lua_tonumber(L, 4);
    float y = lua_tonumber(L, 5);
    float delay = lua_tonumber(L, 6);
    float duration = lua_tonumber(L, 7);

    CallableScriptFunctionParametersEmpty function = CallableScriptFunctionParametersEmpty::empty();
    int functionEndRef = luaL_ref( L, LUA_REGISTRYINDEX );
    if (argc > 4)
    {
        function = CallableScriptFunctionParametersEmpty(functionEndRef);
    }

    PropertyMultipleAnimator *result = obj->SetPosition(spriteDraw, curveType, {x, y}, delay, duration, function);
    if (result)
    {
        ENGINE().getReleasePool().Sink(result);
        result->ScriptingInterfaceRegisterFunctions(L, result);
        return 1;
    }
    else
    {
        return 0;
    }
}

static int lua_PropertyAnimatorFactory_Wait(lua_State *L)
{
    int argc = lua_gettop(L);
    PropertyAnimatorFactory *obj = ScriptingEngineI::GetScriptingObjectPtr<PropertyAnimatorFactory>(L, 1);
    float delay = lua_tonumberx(L, 2, NULL);
    float duration = lua_tonumberx(L, 3, NULL);

    CallableScriptFunctionParametersEmpty function = CallableScriptFunctionParametersEmpty::empty();
    int functionEndRef = luaL_ref( L, LUA_REGISTRYINDEX );
    if (argc > 3)
    {
        function = CallableScriptFunctionParametersEmpty(functionEndRef);
    }

    PropertyAnimator *result = obj->Wait(delay, duration, function);
    if (result)
    {
        ENGINE().getReleasePool().Sink(result);
        result->ScriptingInterfaceRegisterFunctions(L, result);
        return 1;
    }
    else
    {
        return 0;
    }
}

std::vector<luaL_Reg> PropertyAnimatorFactory::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        {"FadeIn",      &lua_PropertyAnimatorFactory_FadeIn}
    ,   {"FadeOut",     &lua_PropertyAnimatorFactory_FadeOut}
    ,   {"SetPosition", &lua_PropertyAnimatorFactory_SetPosition}
    ,   {"Wait",        &lua_PropertyAnimatorFactory_Wait},
    });
    return result;
}
