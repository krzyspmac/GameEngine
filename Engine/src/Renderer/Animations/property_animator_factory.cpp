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
    ::SetAlpha( AnimatablePropertiesI *_object
              , std::string curveType
              , float alpha
              , float delay
              , float duration
              , CallableScriptFunctionParametersEmpty fFinishRef
)
{
    AnimatablePropertiesI& object = *_object;

    CallableCurveLamba *curve = new CallableCurveLamba(0, 1, AnimationCurveFactory::Create(curveType));
    ValueAnimator *linearAnimator = ENGINE().getValueAnimatorFactory()
        .Create(
                  curve
                , delay
                , duration
                , [&](ValueAnimator *self) {
                    float from = object.GetAlpha();
                    float to = static_cast<Holder1<float>*>(self->GetContext())->Get();
                    self->GetCurve()->get()->SetMin(from);
                    self->GetCurve()->get()->SetMax(to);
                }
                , [&](ValueAnimator *self, float val) {
                    object.SetAlpha(val);
                }
                , nullptr);
    linearAnimator->SetContext(new Holder1<float>(alpha));
    linearAnimator->SetFunctionFinish(fFinishRef);

    PropertyAnimator *result = new PropertyAnimator(_object, linearAnimator);
    return result;
}

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
                , [&](ValueAnimator *self) { }
                , [&](ValueAnimator *self, float val) { spr.SetAlpha(val); }
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
                , [&](ValueAnimator *self) { }
                , [&](ValueAnimator *self, float val) { spr.SetAlpha(val); }
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
    AnimatablePropertiesI &object = *sprite;

    auto startingOffset = sprite->GetPosition();

    CallableCurveLamba *curveX = new CallableCurveLamba(startingOffset.x, offset.x, AnimationCurveFactory::Create(curveType));
    ValueAnimator *linearAnimatorX = ENGINE().getValueAnimatorFactory()
        .Create(
                  curveX
                , delay
                , duration
                , [&](ValueAnimator *self) {
                    Vector2 from = object.GetPosition();
                    float to = static_cast<Holder1<Vector2>*>(self->GetContext())->Get().x;
                    self->GetCurve()->get()->SetMin(from.x);
                    self->GetCurve()->get()->SetMax(to);
                }
                , [&](ValueAnimator *self, float val) {
                    object.SetPosition({val, object.GetPosition().y});
                }
                , nullptr);
    //linearAnimatorX->SetFunctionFinish(fFinishRef); only one of the animators should trigger the end function
    linearAnimatorX->SetContext(new Holder1<Vector2>(offset));

    CallableCurveLamba *curveY = new CallableCurveLamba(startingOffset.y, offset.y, AnimationCurveFactory::Create(curveType));
    ValueAnimator *linearAnimatorY = ENGINE().getValueAnimatorFactory()
        .Create(
                  curveY
                , delay
                , duration
                , [&](ValueAnimator *self) {
                    Vector2 from = object.GetPosition();
                    float to = static_cast<Holder1<Vector2>*>(self->GetContext())->Get().y;
                    self->GetCurve()->get()->SetMin(from.y);
                    self->GetCurve()->get()->SetMax(to);
                }
                , [&](ValueAnimator *self, float val) {
                    object.SetPosition({object.GetPosition().x, val});
                }
                , nullptr);
    linearAnimatorY->SetFunctionFinish(fFinishRef);
    linearAnimatorY->SetContext(new Holder1<Vector2>(offset));

    std::vector<ValueAnimator*> list;
    list.emplace_back(linearAnimatorX);
    list.emplace_back(linearAnimatorY);

    PropertyMultipleAnimator *result = new PropertyMultipleAnimator(
         sprite
       , list
    );

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
                , [&](ValueAnimator *self) { }
                , [&](ValueAnimator *self, float val) { }
                , nullptr);
    linearAnimator->SetFunctionFinish(fFinishRef);

    PropertyAnimator *result = new PropertyAnimator(nullptr, linearAnimator);
    return result;
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(PropertyAnimatorFactory);

static int lua_PropertyAnimatorFactory_SetAlpha(lua_State *L)
{
    int argc = lua_gettop(L);
    PropertyAnimatorFactory *obj = ScriptingEngineI::GetScriptingObjectPtr<PropertyAnimatorFactory>(L, 1);
    SpritePropertyManipulatorsI **spriteDrawPtr = (SpritePropertyManipulatorsI**)lua_touserdata(L, 2);
    SpritePropertyManipulatorsI *spriteDraw = *spriteDrawPtr;

    std::string curveType = lua_tostring(L, 3); // linear
    float alpha = lua_tonumber(L, 4);
    float delay = lua_tonumberx(L, 5, NULL);
    float duration = lua_tonumberx(L, 6, NULL);

    CallableScriptFunctionParametersEmpty function = CallableScriptFunctionParametersEmpty::empty();
    int functionEndRef = luaL_ref( L, LUA_REGISTRYINDEX );
    if (argc > 6)
    {
        function = CallableScriptFunctionParametersEmpty(functionEndRef);
    }

    PropertyAnimator *result = obj->SetAlpha(spriteDraw, curveType, alpha, delay, duration, function);
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
    ,   {"SetAlpha",    &lua_PropertyAnimatorFactory_SetAlpha}
    ,   {"SetPosition", &lua_PropertyAnimatorFactory_SetPosition}
    ,   {"Wait",        &lua_PropertyAnimatorFactory_Wait},
    });
    return result;
}
