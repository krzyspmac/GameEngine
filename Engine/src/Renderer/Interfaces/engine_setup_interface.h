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
    typedef struct
    {
        /** The initial resolution */
        Size resolution;
    } EngineSetup;
};

#endif /* engine_setup_interface_h */
