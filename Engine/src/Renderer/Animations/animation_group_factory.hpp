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
#include "animation_interface.hpp"
#include "property_animator.hpp"

namespace engine
{
    /**
        AnimationGroupFactory
        \addtogroup API_GLOBALS
     */
    /** Provides ready to use animation groups.
        Animations are groupped in either simultaneus or sequence groups.
        Each can receive a function as the last parameter that
        reveices a callback when the group finished animating.

        Using groups one can easly order a set of property animators
        to run. Then animation groups can be chained together.

     \code{lua}
          local group = AnimationGroupFactory:GroupAnimations(
            'simultaneus'
          , PropertyAnimatorFactory:FadeIn(sky, 1, 3)
          )
     \endcode

     \code{lua}
         -- animate a group of animators and receive a callback
         -- when the group finished animating
         local group = AnimationGroupFactory:GroupAnimations(
            'sequence'
         ,  PropertyAnimatorFactory:FadeIn(sky, 1, 3)
         ,  PropertyAnimatorFactory:FadeOut(tetx, 0, 3)
         ,  function()
            end
         )
     \endcode

        Animation groups are added to the common MemoryPool that is cleared
        by the Scene when its lifecycle is up.
     */
    class AnimationGroupFactory
    {
    public:
        /** Create an animation group for the simultaneus mode.
            In LUA this is simply:
            \code{lua}
            AnimationGroupFactory:GroupAnimations('simultaneus'...)
            \endcode
         */
        AnimationGroupSimultaneus* GroupAnimationsSimulataneus(CallableScriptFunctionSciptableInstance, std::vector<AnimatableI*>);

        /** Create an animation group for the sequence mode.
         In LUA this is simply:
         \code{lua}
         AnimationGroupFactory:GroupAnimations('sequence'...)
         \endcode
         */
        AnimationGroupSequence* GroupAnimationsSequence(CallableScriptFunctionSciptableInstance, std::vector<AnimatableI*>);

    public: /** Scripting */
        /// @private
        SCRIPTING_INTERFACE_HEADERS(AnimationGroupFactory);
    };
};

#endif /* animation_group_factory_hpp */
