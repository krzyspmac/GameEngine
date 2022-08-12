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
#include "animation_interface.h"
#include "memory.h"

namespace engine
{
    /**
     Provides a way to animate a value from point a to point b
     along a certain curve. ValueAnimator does not animate object
     properties (like "alpha"). It only provides a way to animate
     values. \see ValueAnimatorFactory to create a concrete property
     animator and \see PropertyAnimatorFactory to create a property
     animator.

     The ValueAnimator takes min, max, the curve function, the
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
        std::function<void(ValueAnimator*)> m_startFunc;
        CallableScriptFunctionParametersEmpty m_startFuncRef;
        CallableScriptFunctionParameters1<float> m_updateFuncRef;
        std::function<void(ValueAnimator*, float)> m_updateFunc;
        CallableScriptFunctionParametersEmpty m_endFuncRef;
        std::function<void(ValueAnimator*)> m_endFunc;
        bool m_isStopped;
        void *m_context;
    public:
        /**
         Create the value animator with callaback as script functions.
         @private
         */
        ValueAnimator(std::unique_ptr<CallableCurveLamba> curve,
                      int delay,
                      double seconds,
                      CallableScriptFunctionParametersEmpty functionStartRef,
                      CallableScriptFunctionParameters1<float> functionUpdateRef,
                      CallableScriptFunctionParametersEmpty functionEndRef);

        /**
         Create the value animator with callaback as C++ lambdas.
         @private
         */
        ValueAnimator(std::unique_ptr<CallableCurveLamba> curve,
                      int delay,
                      double seconds,
                      std::function<void(ValueAnimator*)> functionStartRef,
                      std::function<void(ValueAnimator*, float)> functionUpdateRef,
                      std::function<void(ValueAnimator*)> functionEndRef);

        /** @private */
        ~ValueAnimator();

    public:
        void SetFunctionUpdate(CallableScriptFunctionParameters1<float> f);
        void SetFunctionUpdate(std::function<void(ValueAnimator*, float)> f);
        void SetFunctionFinish(CallableScriptFunctionParametersEmpty f);
        void SetFunctionFinish(std::function<void(ValueAnimator*)> f);

        CallableScriptFunctionParameters1<float> GetunctionUpdateRef();
        std::function<void(ValueAnimator*, float)> GetFunctionUpdate();
        CallableScriptFunctionParametersEmpty GetFunctionFinishRef();
        std::function<void(ValueAnimator*)> GetFunctionFinish();

        auto GetCurve() { return &m_curve; }

        /** Store the context. Takes ownership of the object*/
        void SetContext(void*);
        
        void *GetContext();

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

        /** @private */
        void FreeContext();

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
