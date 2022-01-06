//
//  animation_group_sequence.hpp
//  Engine
//
//  Created by krzysp on 06/01/2022.
//

#ifndef animation_group_sequence_hpp
#define animation_group_sequence_hpp

#include "common.h"
#include "animation.h"
#include "scripting_engine_provider_interface.h"
#include "callable.hpp"
#include "memory.h"

namespace engine
{

    /**
     Defines an animation group that can animate AnimatableI items in
     sequence mode.

     Sequence runs each animation in order and waits for all animations to
     finish.
     */
    class AnimationGroupSequence
        : public AnimationGroupI
        , public MemoryI
    {
        std::vector<AnimatableI*> m_animatables;
        size_t m_iCurrentAnimatable;
        CallableScriptFunctionSciptableInstance m_scriptableGroupFinishFn;
    public:
        virtual ~AnimationGroupSequence() { printf("Release animation group\n"); };

        /**
         Create an animation group given a mode a list of objects.
         */
        AnimationGroupSequence(CallableScriptFunctionSciptableInstance m_scriptableFinishFn,
                               std::vector<AnimatableI*>
                               );

    public: // AnimatableI
        void Start();
        void Stop();

    private:
        void Prepare();
        void PlayCurrent();
        void PlayNext();
        void DidFinish();

    /// ScriptingInterface
    public:
        /// @private
        SCRIPTING_INTERFACE_HEADERS(AnimationGroupSequence);
    };
};

#endif /* animation_group_sequence_hpp */
