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

        Holds various information on the state of the engine. Viewport, screen size change
        handler, etc.

        \addtogroup API_GLOBALS
     */
    /** @brief Engine state holder

        Holds various information on the state of the engine. This should be used to
        setup an observer for the screen size change so that the game has a chance
        to react and, maybe, change the viewport size.

        The default implementation should register for screen size change event
        via EngineStateI::SetOnScreenSizeChangeHandler and provide the wanted viewport size
        via EngineStateI::SetViewportSize.

        The code below takes the screen size provided in the handler and calcualtes and
        scale for the game leaving the viewport size unchanged.

        \code{.cpp}
        auto engineState = engine::Globals::engineState()
        engineState->SetOnScreenSizeChangeHandler([&](engine::Size size, float density) {
            // have the wanted size ready somewhere
            engine::Vector2 wantedSize = { 320, 200 };

            // calcualte the scale provided we don't want to change the viewport size
            float scale = MIN((float)size.width / wantedSize.x, (float)size.height / wantedSize.y);

            // update the viewport size with the modified scale; this is a pixel-art
            // game so it should scale by using nearest-neighbour
            engineState->SetViewportSize({(int)wantedSize.x, (int)wantedSize.y}, scale);
        });
        \endcode
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
