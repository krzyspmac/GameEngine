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
}

void
GameSceneIntro::DidActivate() {
}

void
GameSceneIntro::DidDeactivate() {
}
