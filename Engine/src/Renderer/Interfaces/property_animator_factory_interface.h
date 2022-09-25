    //
    //  property_animator_factory_interface.h
    //  Engine
    //
    //  Created by krzysp on 25/09/2022.
    //

#ifndef property_animator_factory_interface_h
#define property_animator_factory_interface_h

#include "property_animator_interface.h"

namespace engine
{
    class PropertyAnimatorFactoryI
    {
    public:
        /** Creates a SetAlpha effect that animates the alpha channel to a specific
         value over a given time interval.
         @param object      - the sprite renderer to animate
         @param curveType   - 'linear'
         @param alpha       - alpha value
         @param delay       - initial delay in seconds; pass 0 to start without delay
         @param duration    - duration in seconds
         @param endFnc      - finish function ref; uses MemoryI and keeps its own memory,
                              new engine::CallableParametersEmpty()
         */
        virtual PropertyAnimatorI *SetAlpha(AnimatablePropertiesI *object,
                                            std::string curveType,
                                            float alpha,
                                            float delay,
                                            float duration,
                                            engine::CallableParametersEmpty *endFnc
                                            ) = 0;

        /** Creates a `fade in` effect that animates the alpha channel to a specific
         value over a given time interval.
         @param object      - the sprite renderer to animate
         @param curveType   - 'linear'
         @param delay       - initial delay in seconds; pass 0 to start without delay
         @param duration    - duration in seconds
         @param endFnc      - finish function ref; uses MemoryI and keeps its own memory
                              new engine::CallableParametersEmpty()
         */
        virtual PropertyAnimatorI *FadeIn(AnimatablePropertiesI *object,
                                          std::string curveType,
                                          float delay,
                                          float duration,
                                          engine::CallableParametersEmpty *endFnc
                                          ) = 0;

        /**
         Creates a `fade in` effect that animates SpriteDrawI::SetAlpha.
         @param object      - the sprite renderer to animate
         @param curveType   - 'linear'
         @param delay       - initial delay in seconds; pass 0 to start without delay
         @param duration    - duration in seconds
         @param endFnc      - finish function ref; uses MemoryI and keeps its own memory
                              new engine::CallableParametersEmpty()
         */
        virtual PropertyAnimatorI *FadeOut(AnimatablePropertiesI *object,
                                           std::string curveType,
                                           float delay,
                                           float duration,
                                           engine::CallableParametersEmpty *endFnc
                                           ) = 0;

        /**
         Creates a "wait" animator that does nothing.
         new engine::CallableParametersEmpty()
         */
        virtual PropertyAnimatorI *Wait(float delay,
                                        float duration,
                                        engine::CallableParametersEmpty*
                                        ) = 0;
    };
};

#endif /* property_animator_factory_interface_h */
