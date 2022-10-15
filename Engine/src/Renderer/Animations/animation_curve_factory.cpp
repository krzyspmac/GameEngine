// Copyright (c) 2022 Krzysztof Pawłowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

#include "animation_curve_factory.hpp"
#include <math.h>

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
            float result = MAX(0, min - progress * m_diff);
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
