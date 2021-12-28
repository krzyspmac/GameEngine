//
//  function.hpp
//  Engine
//
//  Created by krzysp on 28/12/2021.
//

#ifndef function_hpp
#define function_hpp

#include "common_engine_impl.h"

namespace engine
{

    /// Calculate A, B and C for Ax+By+C=0 out out two points.
    /// A=y1-y2; B=x2-x1; C=x1y2-x2y1
    /// 𝐴=𝑦1−𝑦2, 𝐵=𝑥2−𝑥1 and 𝐶=𝑥1𝑦2−𝑥2𝑦1.
    class Function
    {
    public:
        Function(Vector2 p1, Vector2 p2)
        {
            m_A = p1.y-p2.y;
            m_B = p2.x-p1.x;
            m_C = (p1.x*p2.y)-(p2.x*p1.y);
        }

        float f(float x)
        {
            return -(((m_A * x) + m_C)/ m_B);
        }
    private:
        float m_A;
        float m_B;
        float m_C;
    };
};

#endif /* function_hpp */
