//
//  property_animator_factory.hpp
//  Engine
//
//  Created by krzysp on 04/01/2022.
//

#ifndef property_animator_factory_hpp
#define property_animator_factory_hpp

#include "scripting_engine_provider_interface.h"
#include "property_animator.hpp"
#include "sprite_draw_interface.h"
#include "callable.hpp"
#include "animation_curve_factory.hpp"

namespace engine
{
    /**
     PropertyAnimatorFactory
     \addtogroup API_GLOBALS
     */
    class PropertyAnimatorFactory
    {
    public:
        /**
         Creates a `fade in` effect that animates SpriteDrawI::SetAlpha.
         @param sprite      - the sprite renderer to animate
         @param curveType   - 'linear'
         @param delay       - initial delay in seconds; pass 0 to start without delay
         @param duration    - duration in seconds
         @param fFinishRef  - finish function ref; function parameter is the created
                              PropertyAnimator. [optiona] LUA can ommit this parameter

         \code{lua}
         -- fade in the skySprite for 3 seconds with a 1 second delay
         local propertyAnimator = PropertyAnimatorFactory:FadeIn(skySprite, 1, 3)
         \endcode

         \code{lua}
         -- fade in the skySprite for 3 seconds with a 1 second delay and pass in a completion function
         local propertyAnimator = PropertyAnimatorFactory:FadeIn(skySprite, 1, 3, function()
            -- animation is finished
         end)
         \endcode

         \code{lua}
         -- fade in the skySprite for 3 seconds with a 1 second delay and pass in a completion function
         local propertyAnimator = PropertyAnimatorFactory:FadeIn(skySprite, 1, 3, function(animator)
            print("Animator " .. animator .. " is finished")
         end)
         \endcode
         */
        PropertyAnimator *FadeIn(SpriteRepresentationI *sprite,
                                 std::string curveType,
                                 float delay,
                                 float duration,
                                 CallableScriptFunctionParametersEmpty fFinishRef
                                 );

        PropertyAnimator *FadeIn(SpriteRepresentationI *sprite,
                                 AnimationCurveType curveType,
                                 float delay,
                                 float duration,
                                 std::function<void(void)> fFinishRef
                                 );

        /**
         Creates a `fade in` effect that animates SpriteDrawI::SetAlpha.
         @param sprite      - the sprite renderer to animate
         @param curveType   - 'linear'
         @param delay       - initial delay in seconds; pass 0 to start without delay
         @param duration    - duration in seconds
         @param fFinishRef  - finish function ref; function parameter is the created
                              PropertyAnimator. [optiona] LUA can ommit this parameter

         \code{lua}
         -- fade out the skySprite for 3 seconds with a 1 second delay
         local propertyAnimator = PropertyAnimatorFactory:FadeOut(skySprite, 1, 3)
         \endcode

         \code{lua}
         -- fade out the skySprite for 3 seconds with a 1 second delay and pass in a completion function
         local propertyAnimator = PropertyAnimatorFactory:FadeIn(FadeOut, 1, 3, function()
            -- animation is finished
         end)
         \endcode

         \code{lua}
         -- fade out the skySprite for 3 seconds with a 1 second delay and pass in a completion function
         local propertyAnimator = PropertyAnimatorFactory:FadeIn(skySprite, 1, 3, function(animator)
            print("Animator " .. animator .. " is finished")
         end)
         \endcode
         */
        PropertyAnimator *FadeOut(SpriteRepresentationI *sprite,
                                  std::string curveType,
                                  float delay,
                                  float duration,
                                  CallableScriptFunctionParametersEmpty fFinishRef
                                 );

        PropertyAnimator *FadeOut(SpriteRepresentationI *sprite,
                                  AnimationCurveType curveType,
                                  float delay,
                                  float duration,
                                  std::function<void(void)> fFinishRef
                                 );

        
    /// ScriptingInterface
    public:
        /// @private
        SCRIPTING_INTERFACE_HEADERS(PropertyAnimatorFactory);
    };
};

#endif /* property_animator_factory_hpp */
