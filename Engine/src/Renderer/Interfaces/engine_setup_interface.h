//
//  engine_setup_interface.h
//  Engine
//
//  Created by krzysp on 24/01/2022.
//

#ifndef engine_setup_interface_h
#define engine_setup_interface_h

#include "common.h"
#include "common_engine_impl.h"

namespace engine
{
    typedef struct EngineSetup
    {
        /** The game folder in relation to the executable path */
        std::string gameFolder;

        /** The initial resolution */
        Size resolution;

        /** Uses the gamepad if connected. The last one will be used.
            Default is true.
         */
        bool gamepad_support;

        /** Uses the gamepad virtual interface when gamepad is not availagle;
            only on iOS.
            Default is false.
         */
        bool gamepad_virtual_support;

        /** The scale to apply to the whole framebuffer. Allows for keeping
            the framebuffer resolution while scaling the whole screen.
            Default is 1.
         */
        float affineScale;

        /** Can mark the setup as dirty to inform the main renderer pass that
            changes have to pulled and reintegrated. */
        bool isDirty;

        /** Renderer background color */
        Color4 backgroundColor;

        EngineSetup()
        :   resolution( {320, 200} )
        ,   gamepad_support(true)
        ,   gamepad_virtual_support(false)
        ,   affineScale( 1.0 )
        ,   isDirty(false)
        ,   backgroundColor({1.0, 0.0, 1.0, 1.0})
        { };
    } EngineSetup;
};

#endif /* engine_setup_interface_h */
