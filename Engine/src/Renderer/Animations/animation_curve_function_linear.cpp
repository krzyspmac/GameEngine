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

//TODO: requires refactor
float AnimationCurveFunctionLinear::f(float progress)
{
    if (m_min > m_max)
    {
        return m_min - progress * m_diff;
    }
    else
    {
        return m_min + MAX(0, MIN(m_max, progress * m_diff));
    }
}
