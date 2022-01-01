//
//  animation_curve_function_interface.h
//  Engine
//
//  Created by krzysp on 01/01/2022.
//

#ifndef animation_curve_function_interface_h
#define animation_curve_function_interface_h

namespace engine
{
    class AnimationCurveFunctionI
    {
    protected:
        float m_min;
        float m_max;
        float m_diff;
    public:
        AnimationCurveFunctionI(float min, float max) : m_min(min), m_max(max), m_diff(m_max - m_min) { };
        virtual ~AnimationCurveFunctionI() { };
        
        float GetMin() { return m_min; };
        float GetMax() { return m_max; };
        virtual float f(float progress) = 0;
    };
};

#endif /* animation_curve_function_interface_h */
