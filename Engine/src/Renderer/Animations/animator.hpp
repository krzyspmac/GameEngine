//
//  animator.hpp
//  Engine
//
//  Created by krzysp on 27/09/2022.
//

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

        ~Animator()
        {
            printf("Animator deallocation");
        }

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
