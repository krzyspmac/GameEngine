//
//  property_animator_factory.hpp
//  Engine
//
//  Created by krzysp on 04/01/2022.
//

#ifndef property_animator_factory_hpp
#define property_animator_factory_hpp

#include "property_animator.hpp"
#include "property_animator_multiple.hpp"
#include "sprite_draw_interface.h"
#include "callable.hpp"
#include "animation_curve_factory.hpp"
#include "property_animator_factory_interface.h"

namespace engine
{
    class PropertyAnimatorFactory: public PropertyAnimatorFactoryI
    {
    public:
        PropertyAnimatorI *SetAlpha(AnimatablePropertiesI *object,
                                   std::string curveType,
                                   float alpha,
                                   float delay,
                                   float duration,
                                   std::shared_ptr<CallableParametersEmpty> endFnc
                                   );

        PropertyAnimatorI *FadeIn(AnimatablePropertiesI *object,
                                  std::string curveType,
                                  float delay,
                                  float duration,
                                  std::shared_ptr<CallableParametersEmpty> endFnc
                                  );

        PropertyAnimatorI *FadeOut(AnimatablePropertiesI *object,
                                   std::string curveType,
                                   float delay,
                                   float duration,
                                   std::shared_ptr<CallableParametersEmpty> endFnc
                                  );

        PropertyAnimatorI *SetPosition(AnimatablePropertiesI *object,
                                       std::string curveType,
                                       Vector2 offset,
                                       float delay,
                                       float duration,
                                       std::shared_ptr<CallableParametersEmpty> endFnc
                                       );

        PropertyAnimatorI *Wait(float delay,
                                float duration,
                                std::shared_ptr<CallableParametersEmpty> endFnc
                                );
    };
};

#endif /* property_animator_factory_hpp */
