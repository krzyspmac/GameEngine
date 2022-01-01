//
//  animation_curve_function_linear.cpp
//  Engine
//
//  Created by krzysp on 01/01/2022.
//

#include "animation_curve_function_linear.hpp"
#include "common.h"

using namespace engine;

AnimationCurveFunctionLinear::~AnimationCurveFunctionLinear()
{
}

float AnimationCurveFunctionLinear::f(float progress)
{
    float val = m_min + MAX(0, MIN(m_max, progress * m_diff));
    return val;
}
