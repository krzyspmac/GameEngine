//
//  animation_curve_factory.hpp
//  Engine
//
//  Created by x180611 on 05/01/2022.
//

#ifndef animation_curve_factory_hpp
#define animation_curve_factory_hpp

#include "common.h"

namespace engine
{
    typedef enum
    {
        NONE
      , LINEAR
    } AnimationCurveType;

    typedef std::function<float(float, float, float)> AnimationCurveLambda;

    class AnimationCurveFactory
    {
    public:
        static void Prepare();
        
        /**
         Return an animation curve for a type.
         */
        static AnimationCurveLambda Create(AnimationCurveType);
        
        /**
         Return an animation curve for a type as string.
         */
        static AnimationCurveLambda Create(std::string);
        
        /** The linear curve */
        static AnimationCurveLambda Linear();
    };
};

#endif /* animation_curve_factory_hpp */
