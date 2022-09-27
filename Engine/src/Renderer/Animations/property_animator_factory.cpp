//
//  property_animator_factory.cpp
//  Engine
//
//  Created by krzysp on 04/01/2022.
//

#include "property_animator_factory.hpp"
#include "sprite_representation_static.hpp"
#include "animation_curve_factory.hpp"
#include "animation_interface.hpp"
#include "engine.hpp"

using namespace engine;

PropertyAnimatorI *PropertyAnimatorFactory
    ::SetAlpha( AnimatablePropertiesI *_object
              , std::string curveType
              , float alpha
              , float delay
              , float duration
              , std::shared_ptr<CallableParametersEmpty> endFnc
)
{
    AnimatablePropertiesI& object = *_object;
    auto &animationCurveFactory = ENGINE().getAnimationCurveFactory();

    CallableCurveLamba *curve = new CallableCurveLamba(0, 1, animationCurveFactory.Create(curveType));
    ValueAnimatorI *linearAnimator = ENGINE().getValueAnimatorFactory()
        .Create(
                  curve
                , delay
                , duration
                , [&](ValueAnimatorI *_self) {
                    ValueAnimator *self = static_cast<ValueAnimator*>(_self);
                    float from = object.GetAlpha();
                    float to = static_cast<Holder1<float>*>(self->GetContext())->Get();
                    self->GetCurve().get()->SetMin(from);
                    self->GetCurve().get()->SetMax(to);
                }
                , [&](ValueAnimatorI *self, float val) {
                    object.SetAlpha(val);
                }
                , nullptr);

    ValueAnimator *linearAnimatorImpl = static_cast<ValueAnimator*>(linearAnimator);

    linearAnimatorImpl->SetContext(new Holder1<float>(alpha));
    linearAnimatorImpl->SetFunctionFinish([&]([[maybe_unused]] ValueAnimatorI *sender){
        endFnc.get()->Call();
    });

    PropertyAnimator *result = new PropertyAnimator(_object, linearAnimatorImpl);
    return result;
}

PropertyAnimatorI *PropertyAnimatorFactory
    ::FadeIn( AnimatablePropertiesI *sprite
            , std::string curveType
            , float delay
            , float duration
            , std::shared_ptr<CallableParametersEmpty> endFnc)
{
    AnimatablePropertiesI &spr = *sprite;
    auto &animationCurveFactory = ENGINE().getAnimationCurveFactory();

    CallableCurveLamba *curve = new CallableCurveLamba(0, 1, animationCurveFactory.Create(curveType));
    ValueAnimatorI *linearAnimator = ENGINE().getValueAnimatorFactory()
        .Create(
                  curve
                , delay
                , duration
                , [&](ValueAnimatorI *self) { }
                , [&](ValueAnimatorI *self, float val) {
                    spr.SetAlpha(val);
                }
                , nullptr);

    ValueAnimator *linearAnimatorImpl = static_cast<ValueAnimator*>(linearAnimator);

    linearAnimatorImpl->SetFunctionFinish([endFnc](ValueAnimatorI *sender){
        endFnc.get()->Call();
    });

    PropertyAnimator *result = new PropertyAnimator(sprite, linearAnimatorImpl);
    return result;
}

PropertyAnimatorI *PropertyAnimatorFactory
    ::FadeOut(  AnimatablePropertiesI *sprite
              , std::string curveType
              , float delay
              , float duration
              , std::shared_ptr<CallableParametersEmpty> endFnc)
{
    AnimatablePropertiesI &spr = *sprite;
    auto &animationCurveFactory = ENGINE().getAnimationCurveFactory();

    CallableCurveLamba *curve = new CallableCurveLamba(1, 0, animationCurveFactory.Create(curveType));
    ValueAnimatorI *linearAnimator = ENGINE().getValueAnimatorFactory()
        .Create(
                  curve
                , delay
                , duration
                , [&](ValueAnimatorI *self) { }
                , [&](ValueAnimatorI *self, float val) { spr.SetAlpha(val); }
                , nullptr);

    ValueAnimator *linearAnimatorImpl = static_cast<ValueAnimator*>(linearAnimator);

    linearAnimatorImpl->SetFunctionFinish([&](ValueAnimatorI *sender){
        endFnc.get()->Call();
    });

    PropertyAnimator *result = new PropertyAnimator(sprite, linearAnimatorImpl);
    return result;
}

PropertyAnimatorI *PropertyAnimatorFactory
    ::SetPosition(  AnimatablePropertiesI *sprite
                  , std::string curveType
                  , Vector2 offset
                  , float delay
                  , float duration
                  , std::shared_ptr<CallableParametersEmpty> endFnc)
{
    AnimatablePropertiesI &object = *sprite;
    auto &animationCurveFactory = ENGINE().getAnimationCurveFactory();

    auto startingOffset = sprite->GetPosition();

    CallableCurveLamba *curveX = new CallableCurveLamba(startingOffset.x, offset.x, animationCurveFactory.Create(curveType));
    ValueAnimatorI *linearAnimatorX = ENGINE().getValueAnimatorFactory()
        .Create(
                  curveX
                , delay
                , duration
                , [&](ValueAnimatorI *_self) {
                    ValueAnimator *self = static_cast<ValueAnimator*>(_self);
                    Vector2 from = object.GetPosition();
                    float to = static_cast<Holder1<Vector2>*>(self->GetContext())->Get().x;
                    self->GetCurve().get()->SetMin(from.x);
                    self->GetCurve().get()->SetMax(to);
                }
                , [&](ValueAnimatorI *self, float val) {
                    object.SetPosition({val, object.GetPosition().y});
                }
                , nullptr);

    ValueAnimator *linearAnimatorXImpl = static_cast<ValueAnimator*>(linearAnimatorX);

    linearAnimatorXImpl->SetContext(new Holder1<Vector2>(offset));

    CallableCurveLamba *curveY = new CallableCurveLamba(startingOffset.y, offset.y, animationCurveFactory.Create(curveType));
    ValueAnimatorI *linearAnimatorY = ENGINE().getValueAnimatorFactory()
        .Create(
                  curveY
                , delay
                , duration
                , [&](ValueAnimatorI *_self) {
                    ValueAnimator *self = static_cast<ValueAnimator*>(_self);
                    Vector2 from = object.GetPosition();
                    float to = static_cast<Holder1<Vector2>*>(self->GetContext())->Get().y;
                    self->GetCurve().get()->SetMin(from.y);
                    self->GetCurve().get()->SetMax(to);
                }
                , [&](ValueAnimatorI *self, float val) {
                    object.SetPosition({object.GetPosition().x, val});
                }
                , nullptr);

    ValueAnimator *linearAnimatorYImpl = static_cast<ValueAnimator*>(linearAnimatorY);

    linearAnimatorYImpl->SetFunctionFinish([&](ValueAnimatorI *sender){
        endFnc.get()->Call();
    });
    linearAnimatorYImpl->SetContext(new Holder1<Vector2>(offset));

    std::vector<ValueAnimator*> list;
    list.emplace_back(linearAnimatorXImpl);
    list.emplace_back(linearAnimatorYImpl);

    PropertyMultipleAnimator *result = new PropertyMultipleAnimator(
         sprite
       , list
    );

    return result;
}

PropertyAnimatorI *PropertyAnimatorFactory
    ::Wait(float delay, float duration, std::shared_ptr<CallableParametersEmpty> endFnc)
{
    auto &animationCurveFactory = ENGINE().getAnimationCurveFactory();

    CallableCurveLamba *curve = new CallableCurveLamba(1, 0, animationCurveFactory.Create(LINEAR));
    ValueAnimatorI *linearAnimator = ENGINE().getValueAnimatorFactory()
        .Create(
                  curve
                , delay
                , duration
                , [&](ValueAnimatorI *self) { }
                , [&](ValueAnimatorI *self, float val) { }
                , nullptr);

    ValueAnimator *linearAnimatorImpl = static_cast<ValueAnimator*>(linearAnimator);

    linearAnimatorImpl->SetFunctionFinish([&](ValueAnimatorI *sender){
        endFnc->Call();
    });

    PropertyAnimator *result = new PropertyAnimator(nullptr, linearAnimatorImpl);
    return result;
}
