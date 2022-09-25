//
//  GameSceneIntro.cpp
//  Game-Mac
//
//  Created by krzysp on 25/09/2022.
//

#include "GameSceneIntro.hpp"

GameSceneIntro::GameSceneIntro(GameResolutionState *resState)
    : m_resState(resState)
{
    m_font = engine::Globals::fontManager()->LoadFont("at01.fnt", "at01.png");
    m_scene = engine::Globals::sceneManager()->SceneCreateNew();
    m_textSprite = m_scene->SpriteTextLoad(m_font);

    auto size = m_resState->GetViewportSize();

    m_textSprite->SetText("Test");
    m_textSprite->SetPosition({size.x / 2, size.y / 2});
    m_textSprite->SetColorMod({1.f, 1.f, 1.f, 1.f});
    m_textSprite->SetHorizontalAlignment("center");
    m_textSprite->SetVerticalAlignment("middle");
    m_textSprite->SetScale(2.0f);

    m_scene->SetFrameUpdate([&]{
        FrameUpdate();
    });
}

void
GameSceneIntro::DidActivate() {
}

void
GameSceneIntro::DidDeactivate() {
}

void
GameSceneIntro::FrameUpdate() {
    auto size = m_resState->GetViewportSize();
    printf("width = %f\n", size.x);
}
