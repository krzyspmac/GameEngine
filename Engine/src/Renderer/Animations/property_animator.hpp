//
//  property_animator.hpp
//  Engine
//
//  Created by krzysp on 04/01/2022.
//

#ifndef property_animator_hpp
#define property_animator_hpp

#include "scripting_engine_provider_interface.h"
#include "value_animator.hpp"
#include "sprite_draw_interface.h"
#include "animation.h"

namespace engine
{
    /**
     Provides a way to animate properties by using ValueAnimator
     concrete instances.
     */
    class PropertyAnimator: public AnimatableI
    {
        ValueAnimator *m_valueAnimator;
        SpriteDrawI *m_sprite;

    public:
        PropertyAnimator(SpriteDrawI *sprite, ValueAnimator *valueAnimator);

    public: // AnimatableI
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

    /// ScriptingInterface
    public:
        /// @private
        SCRIPTING_INTERFACE_HEADERS(PropertyAnimator);
    };
};

#endif /* property_animator_hpp */
