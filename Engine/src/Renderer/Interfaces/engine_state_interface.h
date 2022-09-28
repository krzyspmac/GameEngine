//
//  engine_state_interface.h
//  Engine
//
//  Created by krzysp on 25/09/2022.
//

#ifndef engine_state_interface_h
#define engine_state_interface_h

#include "size.hpp"

namespace engine
{

    /** EngineState
        \addtogroup API_GLOBALS
        Holds various information on the state of the engine. Viewport, frames, etc.
     */
    class EngineStateI
    {
    public:
        /** Returns the viewport width and height. This is the desired viewport size
            and controls the size of the framebuffer texture. Is reflects what was set
            during initialization and what was modified throughout the course of the
            engine lifcycle.
         */
        virtual Size GetViewportSize() = 0;

        /** Set the viewport & scale. This changes the target framebuffer texture size on the
            frame. */
        virtual void SetViewportSize(Size, float) = 0;

        /** Inform that the screen size has changed. */
        /** @private */
        virtual void SendScreenSizeChangeEvent(Size, float) = 0;

        /** Register a screen resolution change. Once the resolution is changed
            this script function will be callsed and the script will have an option
            to modify the desired resoltion. That in turn might recreate the
            framebuffer texture size.

            The lambda will receive the parameters:
            - size
            - screen density
         */
        /** @private */
        virtual void SetOnScreenSizeChange(std::function<void(Size, float)>) = 0;
    };
};

#endif /* engine_state_interface_h */
