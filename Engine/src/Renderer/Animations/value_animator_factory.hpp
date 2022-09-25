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
#include "value_animator_factory_interface.h"

namespace engine
{
    class ValueAnimatorFactory: public ValueAnimatorFactoryI
    {
    public:
        ValueAnimatorFactory() { };
        virtual ~ValueAnimatorFactory() { };

    public:
        ValueAnimatorI *Create(CallableCurveLamba *curve,
                               float delay,
                               float duration,
                               std::function<void(ValueAnimatorI*)> functionStartRef,
                               std::function<void(ValueAnimatorI*, float)> functionUpdateRef,
                               std::function<void(ValueAnimatorI*)> functionEndRef);

    /// ScriptingInterface
    public:
        /// @private
        SCRIPTING_INTERFACE_HEADERS(ValueAnimatorFactory);
    };
};

#endif /* value_animator_factory_hpp */
