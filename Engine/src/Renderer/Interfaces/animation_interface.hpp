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
        virtual void Animate(float delay, float seconds, AnimationCurveLambda curve, std::function<void(AnimatorI*)> block) = 0;
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

        void SetAlpha(AnimatorI* animator, float wantedValue);
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














// deprecated


    /**
     An abstract interface for the Animatable type.
     */
    class AnimatableI
    {
    protected:
        std::function<void(AnimatableI*)> m_animatableFinishL;
        bool m_isRunning;
    public:
        AnimatableI()
            : m_animatableFinishL(nullptr)
            , m_isRunning(false)
        { };

        /**
         Starts the animation.
         */
        virtual void Start() = 0;

        /**
         Stops the animation.
         */
        virtual void Stop() = 0;

        /**
         Is the animation running?
         */
        bool IsRunning() { return m_isRunning; };

        /**
         Registers one delegate for the animation finish state.
         */
        void AnimatableSetFinishLambda(std::function<void(AnimatableI*)> l) { m_animatableFinishL = l; };

        /**
         */
        std::function<void(AnimatableI*)> AnimatableGetFinishLambda() { return m_animatableFinishL; };
    };

    /**
     Defines an abstract interface for an animation block.
     */
    class AnimationGroupI: public AnimatableI
    {
    public:
        typedef enum
        {
            ANIMATION_SIMULTANEUS
          , ANIMATION_SEQUENCE
        } AnimationGroupMode;

        static AnimationGroupMode GetGroupTypeFromString(std::string type)
        {
            if (type.compare("simultaneus") == 0)
            {
                return ANIMATION_SIMULTANEUS;
            }
            else
            {
                return ANIMATION_SEQUENCE;
            }
        }
    };



}; // namespace engine

#endif /* animation_h */
