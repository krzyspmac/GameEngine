//
//  animation_static.cpp
//  Engine
//
//  Created by x180611 on 05/01/2022.
//

#include "animation_static.hpp"

using namespace engine;

std::function<float(float, float, float)> functionLinearCurve;

static void SetupLinearCurve()
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

void SetupStaticCurves()
{
    SetupLinearCurve();
};
