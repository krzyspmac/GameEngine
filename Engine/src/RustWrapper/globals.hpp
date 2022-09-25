//
//  rust_wrapper.h
//  Engine
//
//  Created by krzysp on 24/09/2022.
//

#ifndef rust_wrapper_h
#define rust_wrapper_h

#include "common_engine_impl.h"
#include "time.hpp"
#include "callable_scripting.hpp"
#include "engine_state.hpp"

namespace engine
{

    class Globals
    {
    protected:
        Globals();

    public:
        static engine::Time *time();

        static engine::EngineState *engineState();
    };
}

#endif /* rust_wrapper_h */
