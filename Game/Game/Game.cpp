#include <iostream>
#include "Game.hpp"

using namespace engine;

static GameResolutionState *gameResolutionState = nullptr;
static GameSceneCoordinator *gameSceneCoordinator = nullptr;

void PictelScriptInit(void) {
    printf("Pictel Script Init!\n");

    gameResolutionState = new GameResolutionState();
    gameSceneCoordinator = new GameSceneCoordinator();

    gameSceneCoordinator->ShowIntroScene();
}

void PictelScriptFrameUpdate(void) {
    printf("Pictel Frame Update!\n");

    auto time = Globals::time();
    printf("time from frame = %f\n", time->GetFrameDeltaSec());
}
