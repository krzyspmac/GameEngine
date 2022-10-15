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

#ifndef animator_h
#define animator_h

#include "animation_interface.hpp"
#include "time.hpp"

namespace engine
{
    class Animator: public AnimatorI
    {
        double m_secondsDelay;
        double m_secondsDuration;
        double m_secondsStart;
        double m_secondsCurrent;
        double m_progress;
        Time& m_time;
        AnimationCurveLambda m_curve;
        std::function<void(AnimatorI*)> m_beginHndlr;
        std::function<void(AnimatorI*)> m_endHndlr;
        std::vector<std::function<void(AnimatorI*)>> blocks;
    public:
        Animator(double delay, double duration, Time& time, AnimationCurveLambda curve);

        ~Animator() { }

        double GetProgress() {
            return m_progress;
        }

        AnimationCurveLambda& GetCurve() {
            return m_curve;
        }

        void Register(std::function<void(AnimatorI*)> lamda);

        void Prepare(std::function<void(AnimatorI*)> beginHndlr, std::function<void(AnimatorI*)> endHndlr);

        void Update();

    private:
        void UpdateBlocks();
    };
}

#endif /* animator_h */
