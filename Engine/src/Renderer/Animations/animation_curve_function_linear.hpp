//
//  animation_curve_function_linear.hpp
//  Engine
//
//  Created by krzysp on 01/01/2022.
//

#ifndef animation_curve_function_linear_hpp
#define animation_curve_function_linear_hpp

#include "animation_curve_function_interface.h"
#include "common.h"

namespace engine
{
    class AnimationCurveFunctionLinear: public AnimationCurveFunctionI
    {
    public:
        using AnimationCurveFunctionI::AnimationCurveFunctionI;

        virtual ~AnimationCurveFunctionLinear();

        float f(float progress);
    };
};

#endif /* animation_curve_function_linear_hpp */
