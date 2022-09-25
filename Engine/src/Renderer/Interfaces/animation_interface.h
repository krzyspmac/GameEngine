//
//  animation.h
//  Engine
//
//  Created by krzysp on 04/01/2022.
//

#ifndef animation_h
#define animation_h

#include "common.h"
#include "common_engine_impl.h"
#include "vector2.hpp"
#include "rotation.hpp"

namespace engine
{
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

    /** Defines the properties that can be animated */
    class AnimatablePropertiesI
    {
    public:
        /** Scale setter */
        virtual void SetAlpha(float) = 0;

        /** Scale getter */
        virtual float GetAlpha() = 0;

        virtual void SetScale(float x) = 0;
        virtual float GetScale() = 0;

        /** Position this sprite in x,y axis game coordinates */
        virtual void SetPosition(Vector2 pos) = 0;

        /** Set the z-axis position.
            Possible values range from 0.0 to 1.0, 0.0 being closest to the "camera" and
            1.0 being further away. Of two object: one being at 1.0 and one being at 0.0
            the one at 0.0 will overlap the one at 1.0.
            */
        virtual void SetZPosition(float zPos) = 0;

        /** Get this sprite's position in game coordinates */
        virtual Vector2& GetPosition() = 0;

        /** Set rotation, specify anchor point in x,y (-1 -> 1)*/
        virtual void SetRotation(Rotation) = 0;

        /** Get this sprite's rotation */
        virtual Rotation &GetRotation() = 0;
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
