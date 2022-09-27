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
    typedef enum
    {
        NONE
      , LINEAR
    } AnimationCurveType;

    /** float min, float max, float progress */
    typedef std::function<float(float, float, float)> AnimationCurveLambda;

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

    /**
     An abstract interface to define the udpate method to be
     called on frame render.
     @private
     */
    class AnimationPeriodicUpdateI
    {
    public:
        virtual void Update() = 0;
    };

    /**
     An abstract interface for the Animatable type.
     @private
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

    class AnimatorI: public AnimationPeriodicUpdateI
    {
    public:
        virtual AnimationCurveLambda& GetCurve() = 0;
        virtual double GetProgress() = 0;
        virtual void Register(AnimationPeriodicUpdateI*) = 0;
        virtual void Register(std::function<void(AnimatorI*)>) = 0;
        virtual void Prepare(std::function<void(AnimatorI*)> beginHndlr, std::function<void(AnimatorI*)> endHndlr) = 0;
    };

    class AnimatorFactoryI
    {
    public:
        virtual void Animate(float delay, float seconds, AnimationCurveLambda curve, std::function<void(AnimatorI*)> block) = 0;
    };

    /** Defines the animatable property. This holds the wanted value and the current value
        since those can be different in different moments in time. Using those two
        parameters it's possible to animate from any value to any value in any moment
        in time.
     */
    template <typename T>
    class AnimatablePropertyItemI: public AnimationPeriodicUpdateI
    {
        T m_currentValue;
        T m_destinationValue;
        std::shared_ptr<AnimatorI> m_valueAnimator;
    public: // AnimatablePropertyItemI
        AnimatablePropertyItemI(T val)
            : AnimationPeriodicUpdateI()
            , m_currentValue(val)
            , m_destinationValue(val)
            , m_valueAnimator(nullptr)
        {
            
        };
        virtual ~AnimatablePropertyItemI()
        {
            
        }

        auto& GetCurrentValue() { return m_currentValue; };
        auto& GetDestinationValue() { return m_destinationValue; };
        auto& GetValueAnimator() { return m_valueAnimator; };
        void Set(T value) {
            m_currentValue = value;
            m_destinationValue = value;
        }
        void Set(AnimatorI *animator, T value) {
            animator->Register(this);
            m_destinationValue = value;
        }

    public: // AnimationPeriodicUpdateI
        void Update() {

        }
    };

    /** All the properties of the sprite that can be modified */
    class SpritePropertiesI
    {
    public:
        virtual void        SetAlpha(float) = 0;
        virtual float       GetAlpha() = 0;
        virtual void        SetScale(float x) = 0;
        virtual float       GetScale() = 0;
        virtual void        SetPosition(Vector2 pos) = 0;
        virtual void        SetZPosition(float zPos) = 0;
        virtual Vector2&    GetPosition() = 0;
        virtual void        SetRotation(Rotation) = 0;
        virtual Rotation&   GetRotation() = 0;
    };

    /** */
//    template <typename T>
    class PropertyManupulatorI
    {
        SpritePropertiesI *m_weakParent;
    public:
        PropertyManupulatorI(SpritePropertiesI* weakParent)
            : m_weakParent(weakParent)
        { }

        void SetAlpha(AnimatorI* animator, float wantedValue) {
            float min = m_weakParent->GetAlpha();
            float max = wantedValue;

            animator->Register([min, max, this](AnimatorI *sender){
                auto& curve = sender->GetCurve();
                auto progress = sender->GetProgress();
                float val = curve(min, max, progress);
                printf("progress=%f\n", progress);
                m_weakParent->SetAlpha(val);
            });
        }
    };

    /** */
    class AnimatablePropertiesI: public SpritePropertiesI
    {
    protected:
        PropertyManupulatorI* m_propertyAnimator;
    public:
        AnimatablePropertiesI() {
            m_propertyAnimator = new PropertyManupulatorI(this);
        }

        virtual ~AnimatablePropertiesI() {
            delete m_propertyAnimator;
        };

        auto* animator() { return m_propertyAnimator; };

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
