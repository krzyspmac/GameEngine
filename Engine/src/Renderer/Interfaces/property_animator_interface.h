//
//  property_animator_interface.h
//  Engine
//
//  Created by krzysp on 12/08/2022.
//

#ifndef property_animator_interface_h
#define property_animator_interface_h

#include "animation_interface.hpp"
#include "memory.h"

namespace engine
{
    /**
     Provides a way to animate properties by using ValueAnimator
     concrete instances.
     Takes ownership of the value animator.
     */
    class PropertyAnimatorI
        : public AnimatableI
        , public MemoryI
    {
    public:
        PropertyAnimatorI()
            : AnimatableI()
            , MemoryI()
        { };

        virtual ~PropertyAnimatorI() { };
    };

};

#endif /* property_animator_interface_h */
