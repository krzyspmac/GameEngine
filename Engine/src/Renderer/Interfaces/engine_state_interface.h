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
    /** EngineStateI
        \addtogroup API_GLOBALS
        Holds various information on the state of the engine. Viewport, screen size change
        handler, etc.
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

        /** Registers a screen size change. Once the screen size is changed
            this function will be callsed and the script will have an option
            to modify the desired viewport. That in turn might recreate the
            framebuffer texture size.

            \see EngineStateI::SetViewportSize

            The lambda will receive the parameters:
            - size
            - screen density
         */
        virtual void SetOnScreenSizeChangeHandler(std::function<void(Size, float)>) = 0;
    };
};

#endif /* engine_state_interface_h */
