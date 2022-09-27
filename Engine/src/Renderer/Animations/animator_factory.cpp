//
//  animator_factory.cpp
//  Engine
//
//  Created by krzysp on 27/09/2022.
//

#include "animator_factory.hpp"
#include "animator.hpp"
#include "easy.h"

using namespace engine;

void AnimatorFactory::Animate(float delay, float seconds, AnimationCurveLambda curve, std::function<void(AnimatorI*)> block) {

    Animator *animator = new Animator(delay, seconds, ENGINE().getTime(), curve);

    animator->Prepare([&](AnimatorI* sender){
        block(sender);
    }, [&](AnimatorI*){
        delete animator;
    });
}
