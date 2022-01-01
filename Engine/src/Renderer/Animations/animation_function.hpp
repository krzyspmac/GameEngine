//
//  animation_function.hpp
//  Engine
//
//  Created by krzysp on 01/01/2022.
//

#ifndef animation_function_hpp
#define animation_function_hpp

#include "scripting_engine_provider_interface.h"
#include "animation_curve_function_interface.h"
#include "engine_provider_interface.h"
#include "time.hpp"

namespace engine
{
    class AnimationPeriodicUpdateI
    {
    public:
        virtual void Update() = 0;
    };

    /**
     Provides a way to animate a value from point a to point b
     along a certain curve. Use AnimationFactory to create a concrete
     instance.

     The AnimationFunction takes min, max, the curve function and the
     duration. Using those values it will a proper function result
     by using AnimationFunction::f().

     The script is resposible for memory management.
     \see AnimationFactory::ReleaseMem()

     \see AnimationFactory.
     */
    class AnimationFunction: public AnimationPeriodicUpdateI
    {
        EngineProviderI &m_engineProvider;
        Time &m_time;
        std::unique_ptr<AnimationCurveFunctionI> m_curve;
        double m_secondsDelay;
        double m_secondsTotal;
        double m_secondsStart;
        double m_secondsPassed;
        double m_val;
        int m_updateFuncRef;
        int m_endFuncRef;
        bool m_isStopped;
    public:
        /**
         @private
         */
        AnimationFunction(std::unique_ptr<AnimationCurveFunctionI> curve, double seconds, int delay, int functionUpdateRef, int functionEndRef);
        /** @private */
        ~AnimationFunction();

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
         Returns current value calcualted when AnimationFunction::Start was initiated
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
        SCRIPTING_INTERFACE_HEADERS(AnimationFunction);
    };
};

#endif /* animation_function_hpp */
