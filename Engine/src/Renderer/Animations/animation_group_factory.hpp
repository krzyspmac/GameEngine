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
#include "animation_group.hpp"
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
        AnimationGroup* GroupAnimations(AnimationGroupI::AnimationGroupMode mode,
                                        CallableScriptFunctionSciptableInstance m_scriptableFinishFn,
                                        std::vector<AnimatableI*>);
        
        AnimationGroup* GroupAnimations(std::string mode,
                                        CallableScriptFunctionSciptableInstance m_scriptableFinishFn,
                                        std::vector<AnimatableI*>);
        
    /// ScriptingInterface
    public:
        /// @private
        SCRIPTING_INTERFACE_HEADERS(AnimationGroupFactory);
    };
};

#endif /* animation_group_factory_hpp */
