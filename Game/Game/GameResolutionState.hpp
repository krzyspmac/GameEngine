//
//  GameResolutionState.h
//  Game
//
//  Created by krzysp on 25/09/2022.
//

#ifndef GameResolutionState_h
#define GameResolutionState_h

#include "game_include.hpp"

class GameResolutionState {
    engine::Vector2 m_wantedSize;
    engine::EngineStateI *m_engineState;
public:
    GameResolutionState();
};

#endif /* GameResolutionState_h */
