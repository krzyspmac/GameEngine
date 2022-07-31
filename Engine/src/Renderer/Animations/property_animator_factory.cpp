//
//  property_animator_factory.cpp
//  Engine
//
//  Created by krzysp on 04/01/2022.
//

#include "property_animator_factory.hpp"
#include "sprite_representation_static.hpp"
#include "animation_curve_factory.hpp"
#include "engine.hpp"

using namespace engine;

PropertyAnimator *PropertyAnimatorFactory
    ::FadeIn( SpritePropertyManipulatorsI *sprite
            , std::string curveType
            , float delay
            , float duration
            , CallableScriptFunctionParametersEmpty fFinishRef)
{
    SpritePropertyManipulatorsI &spr = *sprite;
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
    ::FadeIn(  SpritePropertyManipulatorsI *sprite
             , AnimationCurveType curveType
             , float delay
             , float duration
             , std::function<void(void)> fFinishRef)
{
    SpritePropertyManipulatorsI &spr = *sprite;
    CallableCurveLamba *curve = new CallableCurveLamba(0, 1, AnimationCurveFactory::Create(curveType));
    ValueAnimator *linearAnimator = ENGINE().getValueAnimatorFactory()
        .Create(
                  curve
                , delay
                , duration
                , [&](float val) { spr.SetAlpha(val); }
                , nullptr);

    PropertyAnimator *result = new PropertyAnimator(sprite, linearAnimator);
    return result;
}

PropertyAnimator *PropertyAnimatorFactory
    ::FadeOut(  SpritePropertyManipulatorsI *sprite
              , std::string curveType
              , float delay
              , float duration
              , CallableScriptFunctionParametersEmpty fFinishRef)
{
    SpritePropertyManipulatorsI &spr = *sprite;
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

PropertyAnimator *PropertyAnimatorFactory
    ::FadeOut(SpritePropertyManipulatorsI *sprite
              , AnimationCurveType curveType
              , float delay
              , float duration
              , std::function<void(void)> fFinishRef)
{
    SpritePropertyManipulatorsI &spr = *sprite;
    CallableCurveLamba *curve = new CallableCurveLamba(1, 0, AnimationCurveFactory::Create(curveType));
    ValueAnimator *linearAnimator = ENGINE().getValueAnimatorFactory()
        .Create(
                  curve
                , delay
                , duration
                , [&](float val) { spr.SetAlpha(val); }
                , nullptr);

    PropertyAnimator *result = new PropertyAnimator(sprite, linearAnimator);
    return result;
}

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
        {"FadeIn", &lua_PropertyAnimatorFactory_FadeIn}
    ,   {"FadeOut", &lua_PropertyAnimatorFactory_FadeOut}
    ,   {"Wait", &lua_PropertyAnimatorFactory_Wait},
    });
    return result;
}
