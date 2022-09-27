//
//  animator_factory.hpp
//  Engine
//
//  Created by krzysp on 27/09/2022.
//

#ifndef animator_factory_hpp
#define animator_factory_hpp

#include "animation_interface.hpp"

namespace engine
{
    class AnimatorFactory: public AnimatorFactoryI
    {
    public:
        void Animate(float delay,
                     float seconds,
                     AnimationCurveLambda curve,
                     std::function<void(AnimatorI*)> block,
                     std::function<void(void)> didFinishBlock
                     );
    };
};

#endif /* animator_factory_hpp */
