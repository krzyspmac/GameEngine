//
//  animation_function.hpp
//  Engine
//
//  Created by krzysp on 01/01/2022.
//

#ifndef animation_function_hpp
#define animation_function_hpp

#include "scripting_engine_provider_interface.h"
#include "engine_provider_interface.h"
#include "time.hpp"
#include "callable.hpp"

namespace engine
{
    /**
     An abstract interface to define the udpate method to be
     called on frame render.
     */
    class AnimationPeriodicUpdateI
    {
    public:
        virtual void Update() = 0;
    };

    /**
     Provides a way to animate a value from point a to point b
     along a certain curve. ValueAnimator does not animate object
     properties (like "alpha"). It only provides a way to animate
     values. \see AnimationFactory to create a concrete property
     animator.

     The ValueAnimator takes min, max, the curve function and the
     duration.

     The script is resposible for memory management.
     \see AnimationFactory::ReleaseMem()

     \see AnimationFactory.
     */
    class ValueAnimator: public AnimationPeriodicUpdateI
    {
        EngineProviderI &m_engineProvider;
        Time &m_time;
        std::unique_ptr<CallableCurveLamba> m_curve;
        double m_secondsDelay;
        double m_secondsTotal;
        double m_secondsStart;
        double m_secondsPassed;
        double m_val;
        CallableScriptFunctionNumber m_updateFuncRef;
        CallableScriptFunctionSciptableInstance m_endFuncRef;
        bool m_isStopped;
    public:
        /**
         @private
         */
        ValueAnimator(std::unique_ptr<CallableCurveLamba> curve, double seconds, int delay, CallableScriptFunctionNumber functionUpdateRef, CallableScriptFunctionSciptableInstance  functionEndRef);
        
        /** @private */
        ~ValueAnimator();

    public:
        /**
         Starts the animation. Adds the animation to the default engine run loop so
         it runs automatically. It will periodically call the function
         specified when creating the function.
         */
        void Start();

        /**
         Stops the animation.
         */
        void Stop();

        /**
         Returns current value calcualted when ValueAnimator::Start was initiated
         */
        float GetValue();

        /** @private */
        void CallbackExecute();

        /**
         Releases this object. This is necessary as the created instance is not
         kept anywhere in the cache. The script is resposible for the memory
         management.
         Also stops the animation.
         */
        void ReleaseMem();

    // AnimationPeriodicUpdateI
    public:
        void Update();

    /// ScriptingInterface
    public:
        /// @private
        SCRIPTING_INTERFACE_HEADERS(ValueAnimator);
    };
};

#endif /* animation_function_hpp */
