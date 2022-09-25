//
//  Game.cpp
//  Game
//
//  Created by krzysp on 25/09/2022.
//

#include <iostream>
#include "Game.hpp"

using namespace engine;

void PictelScriptInit(void) {
    printf("Pictel Script Init!\n");
}

void PictelScriptFrameUpdate(void) {
    printf("Pictel Frame Update!\n");

    auto time = Globals::time();
    printf("time from frame = %f\n", time->GetFrameDeltaSec());
}
