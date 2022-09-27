//
//  animation_group_simulateneus
//  Engine
//
//  Created by x180611 on 05/01/2022.
//

#ifndef animation_group_simulateneus_hpp
#define animation_group_simulateneus_hpp

#include "common.h"
#include "animation_interface.hpp"
#include "scripting_engine_provider_interface.h"
#include "callable.hpp"
#include "memory.h"

namespace engine
{
    /**
     Defines an animation group that can animate AnimatableI items in
     simultaneus mode.

     Simultaneus mode runs all animations and waits for their collective end.
     */
    class AnimationGroupSimultaneus
        : public AnimationGroupI
        , public MemoryI
    {
        std::vector<AnimatableI*> m_animatables;
        size_t m_cAnimatablesRunning;
        CallableScriptFunctionSciptableInstance m_scriptableGroupFinishFn;
    public:
        virtual ~AnimationGroupSimultaneus() { printf("Release animation group\n"); };
        
        /**
         Create an animation group given a mode a list of objects.
         */
        AnimationGroupSimultaneus(CallableScriptFunctionSciptableInstance m_scriptableFinishFn,
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
        SCRIPTING_INTERFACE_HEADERS(AnimationGroupSimultaneus);
    };
};

#endif /* animation_group_simulateneus */
