#ifndef GameSceneCoordinator_hpp
#define GameSceneCoordinator_hpp

#include "GameSceneInterface.hpp"

class GameSceneCoordinator {
    GameSceneI *m_currentScene;
    std::unique_ptr<GameSceneI> m_introScene;
public:
    GameSceneCoordinator();

public:
    void ShowIntroScene();

private:
    void ActivateScene(GameSceneI*);
};

#endif /* GameSceneCoordinator_hpp */
