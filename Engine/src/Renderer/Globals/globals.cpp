//
//  globals.cpp
//  Engine
//
//  Created by krzysp on 25/09/2022.
//

#include "globals.hpp"
#include "common_engine_impl.h"
#include "easy.h"
#include "time.hpp"

using namespace engine;

TimeI *Globals::time()
{
    return static_cast<TimeI*>(&(ENGINE().getTime()));
}
