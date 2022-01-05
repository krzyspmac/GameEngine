//
//  property_animator_factory.cpp
//  Engine
//
//  Created by krzysp on 04/01/2022.
//

#include "property_animator_factory.hpp"
#include "sprite_draw_static.hpp"
#include "animation_curve_factory.hpp"
#include "engine.hpp"

using namespace engine;

PropertyAnimator *PropertyAnimatorFactory
    ::FadeIn( SpriteDrawI *sprite
            , std::string curveType
            , float delay
            , float duration
            , CallableScriptFunctionSciptableInstance fFinishRef)
{
    SpriteDrawI &spr = *sprite;
    CallableCurveLamba *curve = new CallableCurveLamba(0, 255, AnimationCurveFactory::Create(curveType));
    ValueAnimator *linearAnimator = GetMainEngine()->getValueAnimatorFactory()
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
    ::FadeIn(  SpriteDrawI *sprite
             , AnimationCurveType curveType
             , float delay
             , float duration
             , std::function<void(void)> fFinishRef)
{
    SpriteDrawI &spr = *sprite;
    CallableCurveLamba *curve = new CallableCurveLamba(0, 255, AnimationCurveFactory::Create(curveType));
    ValueAnimator *linearAnimator = GetMainEngine()->getValueAnimatorFactory()
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
    ::FadeOut(  SpriteDrawI *sprite
              , std::string curveType
              , float delay
              , float duration
              , CallableScriptFunctionSciptableInstance fFinishRef)
{
    SpriteDrawI &spr = *sprite;
    CallableCurveLamba *curve = new CallableCurveLamba(255, 0, AnimationCurveFactory::Create(curveType));
    ValueAnimator *linearAnimator = GetMainEngine()->getValueAnimatorFactory()
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
    ::FadeOut(SpriteDrawI *sprite
              , AnimationCurveType curveType
              , float delay
              , float duration
              , std::function<void(void)> fFinishRef)
{
    SpriteDrawI &spr = *sprite;
    CallableCurveLamba *curve = new CallableCurveLamba(255, 0, AnimationCurveFactory::Create(curveType));
    ValueAnimator *linearAnimator = GetMainEngine()->getValueAnimatorFactory()
        .Create(
                  curve
                , delay
                , duration
                , [&](float val) { spr.SetAlpha(val); }
                , nullptr);

    PropertyAnimator *result = new PropertyAnimator(sprite, linearAnimator);
    return result;
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(PropertyAnimatorFactory);

static int lua_PropertyAnimatorFactory_FadeIn(lua_State *L)
{
    int argc = lua_gettop(L);
    PropertyAnimatorFactory *obj = ScriptingEngineI::GetScriptingObjectPtr<PropertyAnimatorFactory>(L, 1);
    SpriteDrawStatic *spriteDraw = ScriptingEngineI::GetScriptingObjectPtr<SpriteDrawStatic>(L, 2);
    float delay = lua_tonumberx(L, 3, NULL);
    float duration = lua_tonumberx(L, 4, NULL);

    CallableScriptFunctionSciptableInstance function = CallableScriptFunctionSciptableInstance(-1);
    int functionEndRef = luaL_ref( L, LUA_REGISTRYINDEX );
    if (argc > 4)
    {
        function = CallableScriptFunctionSciptableInstance(functionEndRef);
    }

    PropertyAnimator *result = obj->FadeIn(spriteDraw, "linear", delay, duration, function);
    result->ScriptingInterfaceRegisterFunctions(L, result);
    return 1;
}

static int lua_PropertyAnimatorFactory_FadeOut(lua_State *L)
{
    int argc = lua_gettop(L);
    PropertyAnimatorFactory *obj = ScriptingEngineI::GetScriptingObjectPtr<PropertyAnimatorFactory>(L, 1);
    SpriteDrawStatic *spriteDraw = ScriptingEngineI::GetScriptingObjectPtr<SpriteDrawStatic>(L, 2);
    float delay = lua_tonumberx(L, 3, NULL);
    float duration = lua_tonumberx(L, 4, NULL);

    CallableScriptFunctionSciptableInstance function = CallableScriptFunctionSciptableInstance(-1);
    int functionEndRef = luaL_ref( L, LUA_REGISTRYINDEX );
    if (argc > 4)
    {
        function = CallableScriptFunctionSciptableInstance(functionEndRef);
    }

    PropertyAnimator *result = obj->FadeOut(spriteDraw, "linear", delay, duration, function);
    result->ScriptingInterfaceRegisterFunctions(L, result);
    return 1;
}

std::vector<luaL_Reg> PropertyAnimatorFactory::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        {"FadeIn", &lua_PropertyAnimatorFactory_FadeIn},
        {"FadeOut", &lua_PropertyAnimatorFactory_FadeOut},
    });
    return result;
}
