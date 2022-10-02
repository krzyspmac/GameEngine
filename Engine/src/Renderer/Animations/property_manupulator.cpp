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

void PropertyManupulator::SetZPosition(AnimatorI* animator, float wantedValue)
{
    float min = m_weakParent->GetScale();
    float max = wantedValue;

    animator->Register([min, max, this](AnimatorI *sender){
        auto& curve = sender->GetCurve();
        auto progress = sender->GetProgress();
        float val = curve(min, max, progress);
        m_weakParent->SetZPosition(val);
    });
}

void PropertyManupulator::SetRotation(AnimatorI* animator, Rotation rotation)
{
    auto startingRotation = m_weakParent->GetRotation();
    auto endingRotation = rotation;

    animator->Register([startingRotation, endingRotation, this](AnimatorI *sender){
        auto& curve = sender->GetCurve();
        auto progress = sender->GetProgress();
        float val = curve(startingRotation.angle, endingRotation.angle, progress);
        m_weakParent->SetRotation(Rotation(val, endingRotation.anchor));
    });
}
