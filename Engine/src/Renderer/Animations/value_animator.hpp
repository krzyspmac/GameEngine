//
//  animation_function.hpp
//  Engine
//
//  Created by krzysp on 01/01/2022.
//

#ifndef animation_function_hpp
#define animation_function_hpp

//#include "scripting_engine_provider_interface.h"
#include "engine_provider_interface.h"
#include "time.hpp"
#include "callable.hpp"
#include "animation_interface.hpp"
#include "memory.h"
#include "value_animator_interface.h"

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
        : public ValueAnimatorI
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
        std::function<void(ValueAnimatorI*)> m_startFunc;
        std::function<void(ValueAnimatorI*, float)> m_updateFunc;
        std::function<void(ValueAnimatorI*)> m_endFunc;
        bool m_isStopped;
        void *m_context;

    public: // ValueAnimatorI
        ValueAnimator(std::unique_ptr<CallableCurveLamba> curve,
                       int delay,
                       double seconds,
                       std::function<void(ValueAnimatorI*)> callabackFunctionStart,
                       std::function<void(ValueAnimatorI*, float)> callabackFunctionUpdate,
                       std::function<void(ValueAnimatorI*)> callbackFunctionEnd
                       );

        virtual ~ValueAnimator();

    public:
        void SetFunctionUpdate(std::function<void(ValueAnimatorI*, float)> f);
        void SetFunctionFinish(std::function<void(ValueAnimatorI*)> f);

        auto& GetFunctionUpdate() { return m_updateFunc; };
        auto& GetFunctionFinish() { return m_endFunc; };
        auto& GetCurve() { return m_curve; }

        /** Store the context. Takes ownership of the object*/
        void SetContext(void*);
        
        void *GetContext();

    public: // AnimatableI
        void Start();
        void Stop();

    public: // MemoryI
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

//    /// ScriptingInterface
//    public:
//        /// @private
//        SCRIPTING_INTERFACE_HEADERS(ValueAnimator);
    };
};

#endif /* animation_function_hpp */
