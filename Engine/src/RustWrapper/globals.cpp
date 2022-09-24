//
//  sample_class.cpp
//  Engine
//
//  Created by krzysp on 24/09/2022.
//

#include <stdio.h>
#include "globals.hpp"
#include "easy.h"

using namespace engine;

Globals::Globals()
{
    printf("Sample class init\n");
}

engine::Time *Globals::time()
{
    return &(ENGINE().getTime());
}
