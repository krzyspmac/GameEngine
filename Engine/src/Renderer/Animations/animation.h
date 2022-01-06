//
//  animation.h
//  Engine
//
//  Created by krzysp on 04/01/2022.
//

#ifndef animation_h
#define animation_h

#include "common.h"

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
    };

}; // namespace engine

#endif /* animation_h */
