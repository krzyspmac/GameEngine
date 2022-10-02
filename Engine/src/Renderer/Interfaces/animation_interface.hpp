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

    /** AnimationCurveFactoryI
        \addtogroup API_GLOBALS
        Defines the interface for the animation curve factory
     */
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

    /** AnimatorFactoryI
        \addtogroup API_GLOBALS
        Defines the animator factory interface used to provde animation capability
        in the engine. */
    class AnimatorFactoryI
    {
    public:
        /** Starts the animation block. In it you should use the AnimatablePropertiesI::animator()
            to use the animator functions.

            @param delay        - delay in seconds
            @param seconds      - animation duration
            @param curve        - chosen animation curve
            @param block        - the animation block; use AnimatablePropertiesI::animator() to animate properties
            @param didFinishBlock - completion handler block
         */
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

    /** AnimatablePropertiesI
        @brief Interface that holds the default `animator` for the sprite.
     */
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
