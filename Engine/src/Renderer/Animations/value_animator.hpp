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
#include "animation.h"
#include "memory.h"

namespace engine
{
    /**
     Provides a way to animate a value from point a to point b
     along a certain curve. ValueAnimator does not animate object
     properties (like "alpha"). It only provides a way to animate
     values. \see ValueAnimatorFactory to create a concrete property
     animator.

     The ValueAnimator takes min, max, the curve function the
     duration and two callbacks: the update function and the finish
     function.

     The script is resposible for memory management.
     \see ValueAnimatorFactory::ReleaseMem()

     \see ValueAnimatorFactory.
     */
    class ValueAnimator
        : public AnimationPeriodicUpdateI
        , public AnimatableI
        , public MemoryI
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
        ValueAnimator(std::unique_ptr<CallableCurveLamba> curve, double seconds, int delay, CallableScriptFunctionNumber functionUpdateRef, CallableScriptFunctionSciptableInstance functionEndRef);
        
        /** @private */
        ~ValueAnimator();

    /// AnimatableI
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

    /// MemoryI
    public:
        /**
         Relase the memory if this object.
         */
        void ReleaseMem();

    public:
        /**
         Returns current value calcualted when ValueAnimator::Start was initiated
         @private
         */
        float GetValue();

    private:

        /** @private */
        void CallbackExecute();

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
