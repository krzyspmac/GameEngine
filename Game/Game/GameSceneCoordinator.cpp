#include "GameSceneCoordinator.hpp"
#include "GameSceneIntro.hpp"

GameSceneCoordinator::GameSceneCoordinator()
    : m_currentScene(nullptr)
{
}

void
GameSceneCoordinator::ShowIntroScene() {
    if (m_introScene.get() == nullptr) {
        m_introScene = std::unique_ptr<GameSceneI>(std::move(new GameSceneIntro()));
    }
    ActivateScene(m_introScene.get());
}

void
GameSceneCoordinator::ActivateScene(GameSceneI* scene) {
    if (m_currentScene != scene) {
        if (m_currentScene != nullptr) {
            m_currentScene->SetActive(false);
            m_currentScene->DidDeactivate();
        }
        m_currentScene = scene;
        m_currentScene->SetActive(true);
        m_currentScene->DidActivate();

        engine::Globals::sceneManager()->SceneMakeActive(scene->GetSceneObj());
    }
}
