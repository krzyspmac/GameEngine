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

void PropertyManupulator::SetScale(AnimatorI* animator, float wantedValue)
{
    float min = m_weakParent->GetScale();
    float max = wantedValue;

    animator->Register([min, max, this](AnimatorI *sender){
        auto& curve = sender->GetCurve();
        auto progress = sender->GetProgress();
        float val = curve(min, max, progress);
        m_weakParent->SetScale(val);
    });
}

void PropertyManupulator::SetPosition(AnimatorI* animator, Vector2 wantedValue)
{
    auto& startPosition = m_weakParent->GetPosition();
    Vector2 endPosition = wantedValue;

    animator->Register([startPosition, endPosition, this](AnimatorI *sender){
        auto& curve = sender->GetCurve();
        auto progress = sender->GetProgress();
        float x = curve(startPosition.x, endPosition.x, progress);
        float y = curve(startPosition.y, endPosition.y, progress);
        m_weakParent->SetPosition({x, y});
    });
}
