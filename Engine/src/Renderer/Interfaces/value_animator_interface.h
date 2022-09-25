//
//  value_animator_interface.h
//  Engine
//
//  Created by krzysp on 25/09/2022.
//

#ifndef value_animator_interface_h
#define value_animator_interface_h

#include "callable_interface.h"
#include "animation_interface.h"

namespace engine
{
    class ValueAnimatorI
        : public AnimationPeriodicUpdateI
        , public AnimatableI
    {
    public:
        /** Create the value animator with callaback as script functions.
         */
        ValueAnimatorI(std::unique_ptr<CallableCurveLamba> curve,
                       int delay,
                       double seconds,
                       std::function<void(ValueAnimatorI*)> callabackFunctionStart,
                       std::function<void(ValueAnimatorI*, float)> callabackFunctionUpdate,
                       std::function<void(ValueAnimatorI*)> callbackFunctionEnd
                       ) { };

    public: // AnimationPeriodicUpdateI
        virtual void Update() = 0;

    public: // AnimatableI
        virtual void Start() = 0;
        virtual void Stop() = 0;

    };
};

#endif /* value_animator_interface_h */
