//
//  animation_curve_factory.cpp
//  Engine
//
//  Created by x180611 on 05/01/2022.
//

#include "animation_curve_factory.hpp"

using namespace engine;

AnimationCurveType Stirng2AnimationCurveType(std::string);

std::function<float(float, float, float)> functionLinearCurve;

AnimationCurveLambda AnimationCurveFactory::Create(AnimationCurveType type)
{
    switch (type)
    {
        case NONE:
        {
            return nullptr;
        }
        case LINEAR:
        {
            return Linear();
        }
    }
}

AnimationCurveLambda AnimationCurveFactory::Create(std::string name)
{
    return Create(Stirng2AnimationCurveType(name));
}

AnimationCurveLambda AnimationCurveFactory::Linear()
{
    return functionLinearCurve;
}

void AnimationCurveFactory::Prepare()
{
    functionLinearCurve = [&](float min, float max, float progress) {
        float m_diff = fabsf(max - min);
        if (min > max)
        {
            float result = min - progress * m_diff;
            return result;
        }
        else
        {
            return min + MAX(0, MIN(max, progress * m_diff));
        }
    };
}

AnimationCurveType Stirng2AnimationCurveType(std::string value)
{
    if (value.compare("linear") == 0)
    {
        return LINEAR;
    }
    else
    {
        return NONE;
    }
}
