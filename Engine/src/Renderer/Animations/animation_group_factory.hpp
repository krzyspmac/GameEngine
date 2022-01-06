//
//  animation_group_factory.hpp
//  Engine
//
//  Created by x180611 on 05/01/2022.
//

#ifndef animation_group_factory_hpp
#define animation_group_factory_hpp

#include "common.h"
#include "scripting_engine_provider_interface.h"
#include "animation_group_simulateneus.hpp"
#include "animation_group_sequence.hpp"
#include "animation.h"
#include "property_animator.hpp"

namespace engine
{
    /**
    Provides ready to use animation groups.
     */
    class AnimationGroupFactory
    {
    public:
        /**
         Create an animation group for the simultaneus mode.
         */
        AnimationGroupSimultaneus* GroupAnimationsSimulataneus(CallableScriptFunctionSciptableInstance, std::vector<AnimatableI*>);

        /**
         Create an animation group for the sequence mode.
         */
        AnimationGroupSequence* GroupAnimationsSequence(CallableScriptFunctionSciptableInstance, std::vector<AnimatableI*>);

    /// ScriptingInterface
    public:
        /// @private
        SCRIPTING_INTERFACE_HEADERS(AnimationGroupFactory);
    };
};

#endif /* animation_group_factory_hpp */
