//
//  animation_curve_factory.hpp
//  Engine
//
//  Created by x180611 on 05/01/2022.
//

#ifndef animation_curve_factory_hpp
#define animation_curve_factory_hpp

#include "common.h"
#include "animation_interface.hpp"

namespace engine
{
    class AnimationCurveFactory: public AnimationCurveFactoryI
    {
    public:
        void Prepare();
        
        AnimationCurveLambda Create(AnimationCurveType);
        
        AnimationCurveLambda Create(std::string);

        AnimationCurveLambda Linear();
    };
};

#endif /* animation_curve_factory_hpp */
