//
//  value_animator_factory.hpp
//  Engine
//
//  Created by krzysp on 01/01/2022.
//

#ifndef value_animator_factory_hpp
#define value_animator_factory_hpp

#include "value_animator.hpp"
#include "scripting_engine_provider_interface.h"
#include "callable.hpp"
#include "animation_curve_factory.hpp"

namespace engine
{
    /**
     ValueAnimatorFactory
     \addtogroup API_GLOBALS
     */
    /**
     Provides different concrete value animator instances
     to be used to change values along preferred curves.

     Starting an animation adds it to the
     frame update queue and the animator is automatic.
     If the value or time interval is exeeded the animator
     ends automatically and gets removed from the update queue.
     */
    class ValueAnimatorFactory
    {
    public:
        /** @private */
        ValueAnimatorFactory() { };

    public:
        /**
         Creates an animator function `linear` that changes
         a value from min to max over certain seconds. Takes
         two functions as parameters (update and end).
         
         @param min -   animate from this value
         @param max -   animate to this value
         @param seconds - animate over this many seconds
         @param delay - initial delay in seconds
         @param functionUpdateRef - script function that gets called
         each time an update is needed (linked to fps). Reveived
         paramters include the value computed.
         @param functionEndRef - script function that gets called
         when the animation is finished. Received parameter
         includes `self` as in the animation so the script
         can release it.
         
         \include AnimationFactory_CreateLinear.lua
         */
        ValueAnimator *Create(CallableCurveLamba *curve,
                              float delay,
                              float duration,
                              CallableScriptFunctionNumber functionUpdateRef,
                              CallableScriptFunctionSciptableInstance functionEndRef);

        /** @private */
        ValueAnimator *Create(CallableCurveLamba *curve,
                              float delay,
                              float duration,
                              std::function<void(float)> functionUpdateRef,
                              std::function<void(ValueAnimator*)> functionEndRef);

    /// ScriptingInterface
    public:
        /// @private
        SCRIPTING_INTERFACE_HEADERS(ValueAnimatorFactory);
    };
};

#endif /* value_animator_factory_hpp */
