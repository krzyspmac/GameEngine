#ifndef GameSceneCoordinator_hpp
#define GameSceneCoordinator_hpp

#include "game_scene_interface.hpp"
#include "GameResolutionState.hpp"

class GameSceneCoordinator {
    GameResolutionState *m_resState;
    GameSceneI *m_currentScene;
    std::unique_ptr<GameSceneI> m_introScene;
public:
    GameSceneCoordinator(GameResolutionState*);

public:
    void ShowIntroScene();

private:
    void ActivateScene(GameSceneI*);
};

#endif /* GameSceneCoordinator_hpp */
