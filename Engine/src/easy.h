//
//  easy.h
//  Engine
//
//  Created by krzysp on 08/01/2022.
//

#ifndef easy_h
#define easy_h

#include "engine_interface.h"
#include "static_objects.hpp"
    #define ENGINE() StaticObjects::engine()

#include "console_renderer_interface.h"
    #define LOGGER() ENGINE().getConsoleRenderer().GetLogger()
    #define TERMINAL() ENGINE().getConsoleRenderer().GetTerminal()

#endif /* easy_h */
