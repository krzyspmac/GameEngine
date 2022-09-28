// Copyright (c) 2022 Krzysztof Pawłowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

#include "GameSceneCoordinator.hpp"
#include "GameSceneIntro.hpp"
#include "GameInput.hpp"

GameSceneCoordinator::GameSceneCoordinator(GameResolutionState *resState)
    : m_currentScene(nullptr)
    , m_resState(resState)
    , m_gameInput(new GameInput())
{
}

void
GameSceneCoordinator::ShowIntroScene() {
    if (m_introScene.get() == nullptr) {
        auto *scene = new GameSceneIntro(m_resState, m_gameInput);
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
