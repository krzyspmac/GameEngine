//
//  globals.cpp
//  Engine
//
//  Created by krzysp on 25/09/2022.
//

#include "globals.hpp"
#include "interfaces.h"
#include "easy.h"
#include "time.hpp"
#include "animation_curve_factory.hpp"

using namespace engine;

TimeI * Globals::time()
{
    return static_cast<TimeI*>(&(ENGINE().getTime()));
}

EngineStateI * Globals::engineState()
{
    return static_cast<EngineStateI*>(&(ENGINE().getEngineState()));
}

FontManagerI * Globals::fontManager()
{
    return static_cast<FontManagerI*>(&(ENGINE().getFontManager()));
}

SceneManagerI * Globals::sceneManager()
{
    return static_cast<SceneManagerI*>(&(ENGINE().getSceneManager()));
}

PropertyAnimatorFactoryI *Globals::propertyAnimatorFactory()
{
    return static_cast<PropertyAnimatorFactoryI*>(&(ENGINE().getPropertyAnimatorFactory()));
}

AnimationCurveFactoryI *Globals::curveFactory()
{
    return static_cast<AnimationCurveFactoryI*>(&(ENGINE().getAnimationCurveFactory()));
}

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
    std::vector<AnimationPeriodicUpdateI*> list;
    std::vector<std::function<void(AnimatorI*)>> blocks;
public:
    Animator(double delay, double duration, Time& time, AnimationCurveLambda curve)
        : m_secondsDelay(delay)
        , m_secondsDuration(duration)
        , m_secondsCurrent(0.f)
        , m_progress(0.f)
        , m_time(time)
        , m_curve(curve)
        , m_beginHndlr(nullptr)
        , m_endHndlr(nullptr)
    {
        m_secondsStart = time.GetEngineStartSec();
        ENGINE().getPeriodicUpdatesManager().Add(this);
    };

    ~Animator()
    {
        printf("asd");
    }

    double GetProgress() {
        return m_progress;
    }

    void Register(AnimationPeriodicUpdateI* obj) {
        list.emplace_back(obj);
    };

    void Register(std::function<void(AnimatorI*)> lamda) {
        blocks.push_back(lamda);
    }

    void Prepare(std::function<void(AnimatorI*)> beginHndlr, std::function<void(AnimatorI*)> endHndlr) {
        m_beginHndlr = beginHndlr;
        m_endHndlr = endHndlr;

        m_beginHndlr(this);
    }

    AnimationCurveLambda& GetCurve() {
        return m_curve;
    }

    void Update();
};

void Animator::Update() {
    m_secondsCurrent = m_time.GetEngineStartSec() - m_secondsStart;
    printf("udpate %1.2f seconds\n", m_secondsCurrent);

    m_progress = MIN(1.f, m_secondsCurrent / m_secondsDuration);

    if (m_progress >= 1.f) {
        for(auto it = blocks.begin(); it != blocks.end(); ++it) {
            (*it)(this);
        }
        m_endHndlr(this);
        ENGINE().getPeriodicUpdatesManager().Remove(this);
    }
    else {
            // update all other items

            // check if time has passed

        for(auto it = list.begin(); it != list.end(); ++it) {
            (*it)->Update();
        }

        for(auto it = blocks.begin(); it != blocks.end(); ++it) {
            (*it)(this);
        }
    }
}





class AnimatorFactory: public AnimatorFactoryI
{
public:
    void Animate(float delay, float seconds, AnimationCurveLambda curve, std::function<void(AnimatorI*)> block);
};

void AnimatorFactory::Animate(float delay, float seconds, AnimationCurveLambda curve, std::function<void(AnimatorI*)> block) {

    Animator *animator = new Animator(delay, seconds, ENGINE().getTime(), curve);
    auto& animationCurveFactory = ENGINE().getAnimationCurveFactory();

    animator->Prepare([&](AnimatorI* sender){
        block(sender);
    }, [&](AnimatorI*){
        delete animator;
    });
}

AnimatorFactoryI *Globals::animator()
{
    static AnimatorFactory *animator = new AnimatorFactory();
    return animator;
}
