//
//  GameSceneIntro.cpp
//  Game-Mac
//
//  Created by krzysp on 25/09/2022.
//

#include "GameSceneIntro.hpp"

GameSceneIntro::GameSceneIntro() {
    m_font = engine::Globals::fontManager()->LoadFont("at01.fnt", "at01.png");
    m_scene = engine::Globals::sceneManager()->SceneCreateNew();
    m_textSprite = m_scene->SpriteTextLoad(m_font);

    m_textSprite->SetText("Test");
    m_textSprite->SetPosition({100.f, 100.f});
    m_textSprite->SetColorMod({1.f, 1.f, 1.f, 1.f});
    m_textSprite->SetScale(2.0f);
}

void
GameSceneIntro::DidActivate() {
}

void
GameSceneIntro::DidDeactivate() {
}
