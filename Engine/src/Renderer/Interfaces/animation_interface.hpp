//
//  animation.h
//  Engine
//
//  Created by krzysp on 04/01/2022.
//

#ifndef animation_h
#define animation_h

#include "common.h"
#include "vector2.hpp"
#include "rotation.hpp"

namespace engine
{
    /** All the defined curve types */
    typedef enum
    {
        NONE
      , LINEAR
    } AnimationCurveType;

    /** float min, float max, float progress */
    typedef std::function<float(float, float, float)> AnimationCurveLambda;

    /** Defines the interface for the animation curve factory */
    class AnimationCurveFactoryI
    {
    public:
        virtual void Prepare() = 0;

        /** Return an animation curve for a type. */
        virtual AnimationCurveLambda Create(AnimationCurveType) = 0;

        /** Return an animation curve for a type as string. */
        virtual AnimationCurveLambda Create(std::string) = 0;

        /** The linear curve */
        virtual AnimationCurveLambda Linear() = 0;
    };

    /** An abstract interface to define the udpate method to be
        called on frame render.
     */
    class AnimationPeriodicUpdateI
    {
    public:
        virtual void Update() = 0;
    };

    /** Defines the animator interface that is used to provide a concrete instance
        of the object actually doing the animation itself. */
    class AnimatorI: public AnimationPeriodicUpdateI
    {
    public:
        virtual AnimationCurveLambda& GetCurve() = 0;
        virtual double GetProgress() = 0;
        virtual void Register(std::function<void(AnimatorI*)>) = 0;
        virtual void Prepare(std::function<void(AnimatorI*)> beginHndlr, std::function<void(AnimatorI*)> endHndlr) = 0;
    };

    /** Defines the animator factory interface used to provde animation capability
        in the engine. */
    class AnimatorFactoryI
    {
    public:
        virtual void Animate(float delay,
                             float seconds,
                             AnimationCurveLambda curve,
                             std::function<void(AnimatorI*)> block,
                             std::function<void(void)> didFinishBlock
                             ) = 0;
    };

    /** All the properties of the sprite that can be modified */
    class SpritePropertiesI
    {
    public:
        virtual void        SetAlpha(float) = 0;
        virtual float       GetAlpha() = 0;
        virtual void        SetScale(float) = 0;
        virtual float       GetScale() = 0;
        virtual void        SetPosition(Vector2) = 0;
        virtual void        SetZPosition(float) = 0;
        virtual Vector2&    GetPosition() = 0;
        virtual void        SetRotation(Rotation) = 0;
        virtual Rotation&   GetRotation() = 0;
    };

    /** Property manipulator. Uses all the properties defined in SpritePropertiesI  */
    class PropertyManupulator
    {
        SpritePropertiesI *m_weakParent;
    public:
        PropertyManupulator(SpritePropertiesI* weakParent)
            : m_weakParent(weakParent)
        { }

        void SetAlpha(AnimatorI*, float);
        void SetScale(AnimatorI*, float);
        void SetPosition(AnimatorI*, Vector2);
        void SetZPosition(AnimatorI*, float);
        void SetRotation(AnimatorI*, Rotation);
    };

    /**  */
    class AnimatablePropertiesI: public SpritePropertiesI
    {
    protected:
        PropertyManupulator* m_propertyAnimator;
    public:
        AnimatablePropertiesI() {
            m_propertyAnimator = new PropertyManupulator(this);
        }

        virtual ~AnimatablePropertiesI() {
            delete m_propertyAnimator;
        };

        auto* animator() { return m_propertyAnimator; };

    };

}; // namespace engine

#endif /* animation_h */
