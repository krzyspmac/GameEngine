//
//  animation_factory.hpp
//  Engine
//
//  Created by krzysp on 01/01/2022.
//

#ifndef animation_factory_hpp
#define animation_factory_hpp

#include "animation_function.hpp"
#include "scripting_engine_provider_interface.h"

namespace engine
{
    /**
     AnimationFactory
     \addtogroup API_GLOBALS
     */
    /**
     Provides different concrete animation instances
     to be used to change values along preffered curves.

     Starting an animation adds it to the
     frame update queue and the animation is automatic.
     If the value or time interval is exeeded the animation
     ends automatically and gets removed from the update queue.

     The caller is resposible for the memory allocated when
     creating animators. Call `ReleaseMem` on received
     animation functions when no longer needing them.
     */
    class AnimationFactory
    {
    public:
        /** @private */
        AnimationFactory() { };

    public:
        /**
         Creates an animation function `linear` that animates
         a value from min to max over certain seconds. Takes
         `functionRef` as a scripting function parameter.

         @param min -   animate from this value
         @param max -   animate to this value
         @param seconds - animate over this many seconds
         @param functionUpdateRef - script function that gets called
            each time an update is needed (linked to fps)
         @param functionEndRef - script function that gets called
            when the animation is finished

         \include AnimationFactory_CreateLinear.lua
         */
        AnimationFunction *CreateLinear(float min, float max, double seconds, int functionUpdateRef, int functionEndRef);

    /// ScriptingInterface
    public:
        /// @private
        SCRIPTING_INTERFACE_HEADERS(AnimationFactory);
    };
};

#endif /* animation_factory_hpp */
