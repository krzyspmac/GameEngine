//
//  property_animator_factory.hpp
//  Engine
//
//  Created by krzysp on 04/01/2022.
//

#ifndef property_animator_factory_hpp
#define property_animator_factory_hpp

#include "scripting_engine_provider_interface.h"
#include "property_animator.hpp"
#include "sprite_draw_interface.h"
#include "callable.hpp"

namespace engine
{
    /**
     PropertyAnimatorFactory
     \addtogroup API_GLOBALS
     */
    class PropertyAnimatorFactory
    {
    public:
        /**
         Creates a `fade in` effect that animates SpriteDrawI::SetAlpha.
         @param sprite      - the sprite renderer to animate
         @param delay       - initial delay in seconds; pass 0 to start without delay
         @param duration    - duration in seconds
         @param fFinishRef  - finish function ref; function parameter is the created
                              PropertyAnimator. [optiona] LUA can ommit this parameter
         */
        PropertyAnimator *FadeIn(SpriteDrawI *sprite,
                                 float delay,
                                 float duration,
                                 CallableScriptFunctionSciptableInstance fFinishRef
                                 );

        /**
         Creates a `fade in` effect that animates SpriteDrawI::SetAlpha.
         Available only in C++
         @private
         @param sprite      - the sprite renderer to animate
         @param delay       - initial delay in seconds; pass 0 to start without delay
         @param duration    - duration in seconds
         @param fFinishRef  - finish function ref; function parameter is the created
                              PropertyAnimator. [optiona] LUA can ommit this parameter
         */
        PropertyAnimator *FadeIn(SpriteDrawI *sprite,
                                 float delay,
                                 float duration,
                                 std::function<void(void)> fFinishRef
                                 );

    /// ScriptingInterface
    public:
        /// @private
        SCRIPTING_INTERFACE_HEADERS(PropertyAnimatorFactory);
    };
};

#endif /* property_animator_factory_hpp */
