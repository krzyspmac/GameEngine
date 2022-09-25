#ifndef GameResolutionState_h
#define GameResolutionState_h

#include "interfaces.h"

class GameResolutionState {
    engine::Vector2 m_wantedSize;
    engine::EngineStateI *m_engineState;
public:
    GameResolutionState();
};

#endif /* GameResolutionState_h */
