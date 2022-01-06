//
//  engine_state_hpp
//  EngineState
//
//  Created by krzysp on 01/01/2022.
//

#ifndef engine_state_hpp
#define engine_state_hpp

#include "scripting_engine_provider_interface.h"
#include "common_engine_impl.h"

namespace engine
{
    /**
     EngineState
     \addtogroup API_GLOBALS
     */
    /**
     Holds various information on the state of the engine. Viewport, frames, etc.
     */
    class EngineState
    {
    public:
        /**
         Returns the viewport width and height.
         */
        Size& GetViewportSize();

    /// ScriptingInterface
    public:
        /** @private */
        SCRIPTING_INTERFACE_HEADERS(EngineState);
    };
};

#endif /* engine_state_hpp */
