//
//  property_manipualator.cpp
//  Engine
//
//  Created by krzysp on 27/09/2022.
//

#include "animation_interface.hpp"

using namespace engine;

void PropertyManupulator::SetAlpha(AnimatorI* animator, float wantedValue)
{
    float min = m_weakParent->GetAlpha();
    float max = wantedValue;

    animator->Register([min, max, this](AnimatorI *sender){
        auto& curve = sender->GetCurve();
        auto progress = sender->GetProgress();
        float val = curve(min, max, progress);
        m_weakParent->SetAlpha(val);
    });
}
