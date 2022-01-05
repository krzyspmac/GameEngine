//
//  animation_group.hpp
//  Engine
//
//  Created by x180611 on 05/01/2022.
//

#ifndef animation_group_hpp
#define animation_group_hpp

#include "common.h"
#include "animation.h"
#include "scripting_engine_provider_interface.h"
#include "callable.hpp"
#include "memory.h"

namespace engine
{
    /**
     Defines an animation group that can animate AnimatableI items in either
     simultaneus or sequence mode.

     Simultaneus mode runs all animations and waits for their collective end.
     Sequence runs each animation in order and waits for all animations to
     finish.
     */
    class AnimationGroup
        : public AnimationGroupI
        , public AnimatableI
        , public MemoryI
    {
        std::vector<AnimatableI*> m_animatables;
        size_t m_cAnimatablesRunning;
        CallableScriptFunctionSciptableInstance m_scriptableFinishFn;
    public:
        virtual ~AnimationGroup() { printf("Release animation group\n"); };
        
        /**
         Create an animation group given a mode a list of objects.
         */
        AnimationGroup(AnimationGroupMode,
                       CallableScriptFunctionSciptableInstance m_scriptableFinishFn,
                       std::vector<AnimatableI*>
                       );
        
        AnimationGroup(std::string mode,
                       CallableScriptFunctionSciptableInstance m_scriptableFinishFn,
                       std::vector<AnimatableI*>
                       );

    public: // AnimatableI
        void Start();
        void Stop();
        
    private:
        void Prepare();
        void DidFinish();
        
    /// ScriptingInterface
    public:
        /// @private
        SCRIPTING_INTERFACE_HEADERS(AnimationGroup);
    };
};

#endif /* animation_group_hpp */
