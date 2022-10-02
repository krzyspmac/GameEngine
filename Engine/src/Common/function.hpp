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

#ifndef function_hpp
#define function_hpp

#include "interfaces.h"

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
