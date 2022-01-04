//
//  property_animator_factory.cpp
//  Engine
//
//  Created by krzysp on 04/01/2022.
//

#include "property_animator_factory.hpp"
#include "sprite_draw_static.hpp"
#include "engine.hpp"

using namespace engine;

PropertyAnimator *PropertyAnimatorFactory::FadeIn(SpriteDrawI *sprite, float delay, float duration, CallableScriptFunctionSciptableInstance fFinishRef)
{
    SpriteDrawI &spr = *sprite;

    ValueAnimator *linearAnimator = GetMainEngine()->getValueAnimatorFactory()
        .CreateLinear(  0
                      , 255
                      , duration
                      , delay
                      , [&](float val) { spr.SetAlpha(val); }
                      , nullptr
                    );
    linearAnimator->SetFunctionFinish(fFinishRef);

    PropertyAnimator *result = new PropertyAnimator(sprite, linearAnimator);
    return result;
}

PropertyAnimator *PropertyAnimatorFactory::FadeIn(SpriteDrawI *sprite, float delay, float duration, std::function<void(void)> fFinishRef)
{
    SpriteDrawI &spr = *sprite;
    ValueAnimator *linearAnimator = GetMainEngine()->getValueAnimatorFactory()
        .CreateLinear(  0
                      , 255
                      , duration
                      , delay
                      , [&](float val) { spr.SetAlpha(val); }
                      , [&](ValueAnimator *sender){ sender->ReleaseMem(); }
                      );

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

    PropertyAnimator *result = obj->FadeIn(spriteDraw, delay, duration, function);
    result->ScriptingInterfaceRegisterFunctions(L, result);
    return 1;
}

std::vector<luaL_Reg> PropertyAnimatorFactory::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        {"FadeIn", &lua_PropertyAnimatorFactory_FadeIn},
    });
    return result;
}
