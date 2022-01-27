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
#include "callable.hpp"

namespace engine
{
    /**
     EngineState
     \addtogroup API_GLOBALS
     */
    /** Holds various information on the state of the engine. Viewport, frames, etc.
     */
    class EngineState
    {
        std::function<void(Size)> m_screenSizeChangeHandler;
        CallableScriptFunctionSciptableInstance m_screenSizeChangeScriptHandler;
    public:
        EngineState();
    public:
        /** Returns the viewport width and height. This is the desired viewport size
            and controls the size of the framebuffer texture. Is reflects what was set
            during initialization and what was modified throughout the course of the
            engine lifcycle.
         */
        Size GetViewportSize();

        /** Set the viewport & scale. This changes the target framebuffer texture size on the
            frame. */
        void SetViewportSize(Size, float);

    public: /** Handlers */

        /** Register a screen resolution change. Once the resolution is changed
            this script function will be callsed and the script will have an option
            to modify the desired resoltion. That in turn might recreate the
            framebuffer texture size. */
        /** @private */
        void SetOnScreenSizeChange(std::function<void(Size)>);

        /** Register a screen resolution change handler. Once the resolution is changed
            this script function will be called and the script will have an option
            to modify the desired resolution. That in turn might recreate the
            framebuffer texture size.
         
            The script receives the parameters:
            - width (int)
            - height (int)
            - pixel dencity (float)

            By default the screen presented to the user is: width/density x height/density.
            When setting the resolution please take the density into account.
         */
        /**
            \code{lua}
            EngineState:SetOnScreenSizeChange(function(width, height, density)
            end)
            \endcode
         */
        void SetOnScreenSizeChange(CallableScriptFunctionSciptableInstance);

        /** Inform that the screen size has changed. */
        /** @private */
        void SendScreenSizeChangeEvent(Size, float);

    /// ScriptingInterface
    public:
        /** @private */
        SCRIPTING_INTERFACE_HEADERS(EngineState);
    };
};

#endif /* engine_state_hpp */
