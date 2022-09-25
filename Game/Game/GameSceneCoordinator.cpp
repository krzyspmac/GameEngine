#include "GameSceneCoordinator.hpp"
#include "GameSceneIntro.hpp"

GameSceneCoordinator::GameSceneCoordinator(GameResolutionState *resState)
    : m_currentScene(nullptr)
    , m_resState(resState)
{
}

void
GameSceneCoordinator::ShowIntroScene() {
    if (m_introScene.get() == nullptr) {
        auto *scene = new GameSceneIntro(m_resState);
        m_introScene = std::unique_ptr<GameSceneI>(std::move(scene));
    }
    ActivateScene(m_introScene.get());
}

void
GameSceneCoordinator::ActivateScene(GameSceneI* scene) {
    if (m_currentScene == scene) {
        return;
    }

    if (m_currentScene != nullptr) {
        m_currentScene->SetActive(false);
        m_currentScene->DidDeactivate();
    }

    m_currentScene = scene;
    m_currentScene->SetActive(true);
    m_currentScene->DidActivate();

    engine
        ::Globals
        ::sceneManager()
        ->SceneMakeActive(scene->GetSceneObj());
}
