//
//  animation.h
//  Engine
//
//  Created by krzysp on 04/01/2022.
//

#ifndef animation_h
#define animation_h

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
    public:
        /**
         Starts the animation.
         */
        virtual void Start() = 0;

        /**
         Stops the animation.
         */
        virtual void Stop() = 0;
    };

}; // namespace engine

#endif /* animation_h */
