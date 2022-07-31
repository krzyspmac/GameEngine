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
        ,   affineScale( 1.0 )
        ,   isDirty(false)
        ,   backgroundColor({1.0, 0.0, 1.0, 1.0})
        { };
    } EngineSetup;
};

#endif /* engine_setup_interface_h */
