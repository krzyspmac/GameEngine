//
//  property_animator_multiple.hpp
//  Engine-Mac
//
//  Created by krzysp on 12/08/2022.
//

#ifndef property_animator_multiple_hpp
#define property_animator_multiple_hpp

#include "scripting_engine_provider_interface.h"
#include "value_animator.hpp"
#include "sprite_draw_interface.h"
#include "animation_interface.h"
#include "property_animator_interface.h"
#include "memory.h"

namespace engine
{
    /**
     Provides a way to use multiple value animators
     */
    class PropertyMultipleAnimator: public PropertyAnimatorI
    {
        std::vector<std::unique_ptr<ValueAnimator>> m_animators;
        int m_animatorsFinished;

    public:
        PropertyMultipleAnimator(AnimatablePropertiesI*, std::vector<ValueAnimator*>);
        virtual ~PropertyMultipleAnimator();
        
    public: // AnimatableI
        void Start();
        void Stop();

    public: // MemoryI
        void FreeMem();

    public: // ScriptingInterface
        /// @private
        SCRIPTING_INTERFACE_HEADERS(PropertyMultipleAnimator);
    };
};

#endif /* property_animator_multiple_hpp */
