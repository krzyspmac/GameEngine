#include <iostream>
#include "GameEntryPoint.hpp"

using namespace engine;

static GameResolutionState *gameResolutionState = nullptr;
static GameSceneCoordinator *gameSceneCoordinator = nullptr;

void PictelScriptInit(void) {
    gameResolutionState = new GameResolutionState();
    gameSceneCoordinator = new GameSceneCoordinator(gameResolutionState);

    gameSceneCoordinator->ShowIntroScene();
}

void PictelScriptFrameUpdate(void) {
    auto time = Globals::time();
    printf("time from frame = %f\n", time->GetFrameDeltaSec());
}
