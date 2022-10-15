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

#include "GameSceneIntro.hpp"

using namespace engine;

GameSceneIntro::GameSceneIntro(GameResolutionState *resState, GameInputI *gameInput)
    : m_resState(resState)
    , m_inertiaProcessor(IntertiaProcessor())
    , m_gameInput(gameInput)
{
    m_font = Globals::fontManager()->LoadFont("at01.fnt", "at01.png");
    m_scene = Globals::sceneManager()->SceneCreateNew();
    m_textSprite = m_scene->SpriteTextLoad(m_font);

    m_texts = {
        "This game is made using a custom built engine"
      , "Some things might not work.\nA lot of them actually."
      , "Drop me a line if wish.\nMore in the game menu"
    };

    m_scene->SetFrameUpdate([&]{
        FrameUpdate();
    });

    auto size = m_resState->GetViewportSize();
    auto* atlasMgr = Globals::spriteAtlasManager();

    auto* atlasBackgroundItem = atlasMgr->SpriteAtlasLoad("background.json", "background.png");
    m_background = m_scene->SpriteStaticLoad(atlasBackgroundItem, "background.png");

    auto* atlasAnimatedSpriteItem = atlasMgr->SpriteAtlasLoad("player_Idle.json", "player_Idle.tga");
    m_animated = m_scene->SpriteAnimatedLoad(250, atlasAnimatedSpriteItem);
    m_animated->SetPosition({100,100});
    m_animated->SetAcceptsLight(false);

    m_textSprite->SetText("Test");
    m_textSprite->SetPosition({size.x / 2, size.y / 2});
    m_textSprite->SetColorMod({1.f, 1.f, 1.f, 1.f});
    m_textSprite->SetHorizontalAlignment("center");
    m_textSprite->SetVerticalAlignment("middle");
    m_textSprite->SetScale(2.0f);
    m_textSprite->SetAlpha(0.0f);
    m_textSprite->SetAcceptsLight(true);

    m_light = m_scene->CreateLight("linear", {0.f, 1.f, 0.f}, 0.5, {100, 100}, 50, 1.);

    m_sound = Globals::soundManager()->Load("Rondo_Alla_Turka.ogg");
    m_sound->AddObserver(CallableParameters1<SoundFileI *>::make_shared([&](SoundFileI* sender){
        printf("Sound state = %d\n", sender->GetState());
    }));

    m_inertiaProcessor.SetPosition(m_animated->GetPosition());
}

void GameSceneIntro::DidActivate()
{
    ContinueAnimation();
}

void GameSceneIntro::DidDeactivate() { }

void GameSceneIntro::FrameUpdate()
{
    m_inertiaProcessor.UpdateForceVector(m_gameInput->GetLeftThumbstickVector());
    m_inertiaProcessor.Tick();
    m_animated->SetPosition(m_inertiaProcessor.GetPosition());
}

void GameSceneIntro::ContinueAnimation()
{
    FadeIn();
    RotationIn();
    m_sound->Play();
}

void GameSceneIntro::FadeIn()
{
    auto animator = Globals::animator();
    auto curve = Globals::curveFactory()->Create(LINEAR);

    animator->Animate(1, .1, curve, [&](auto *animator){
        m_textSprite->animator()->SetAlpha(animator, 1.0);
    }, [&](void) {
        FadeOut();
    });
}

void GameSceneIntro::ScaleIn()
{
    auto animator = Globals::animator();
    auto curve = Globals::curveFactory()->Create(LINEAR);

    animator->Animate(1, 30, curve, [&](auto *animator){
        m_textSprite->animator()->SetScale(animator, 100);
    }, [&](void) {
    });
}

void GameSceneIntro::FadeOut()
{
    auto animator = Globals::animator();
    auto curve = Globals::curveFactory()->Create(LINEAR);

    animator->Animate(1, .1, curve, [&](auto *animator){
        m_textSprite->animator()->SetAlpha(animator, 0.0);
    }, [&](void){
        FadeIn();
    });
}

void GameSceneIntro::PositionIn()
{
    auto animator = Globals::animator();
    auto curve = Globals::curveFactory()->Create(LINEAR);

    animator->Animate(1, 5, curve, [&](auto *animator){
        m_textSprite->animator()->SetPosition(animator, {150, 500});
    }, [&](void){
    });
}

void GameSceneIntro::RotationIn()
{
    auto animator = Globals::animator();
    auto curve = Globals::curveFactory()->Create(LINEAR);

    animator->Animate(1, 5, curve, [&](auto *animator){
        m_textSprite->animator()->SetRotation(animator, Rotation(M_PI, {0, 0}));
    }, [&](void){
    });
}
