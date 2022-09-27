
#include "GameSceneIntro.hpp"

GameSceneIntro::GameSceneIntro(GameResolutionState *resState)
    : m_resState(resState)
{
    m_font = engine::Globals::fontManager()->LoadFont("at01.fnt", "at01.png");
    m_scene = engine::Globals::sceneManager()->SceneCreateNew();
    m_textSprite = m_scene->SpriteTextLoad(m_font);

    m_texts = {
        "This game is made using a custom built engine"
      , "Some things might not work.\nA lot of them actually."
      , "Drop me a line if wish.\nMore in the game menu"
    };

    auto size = m_resState->GetViewportSize();

    m_textSprite->SetText("Test");
    m_textSprite->SetPosition({size.x / 2, size.y / 2});
    m_textSprite->SetColorMod({1.f, 1.f, 1.f, 1.f});
    m_textSprite->SetHorizontalAlignment("center");
    m_textSprite->SetVerticalAlignment("middle");
    m_textSprite->SetScale(2.0f);
    m_textSprite->SetAlpha(0.0f);

    m_scene->SetFrameUpdate([&]{
        FrameUpdate();
    });

    ContinueAnimation();
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

void
GameSceneIntro::ContinueAnimation() {
//    auto propertyAnimatorFactory = engine::Globals::propertyAnimatorFactory();

//    m_textSprite->SetAlpha(0.5);

//    m_fadeIn = propertyAnimatorFactory
//        ->FadeIn(m_textSprite, "linear", 0.2, 1, std::shared_ptr<engine::CallbackEmpty>(new engine::CallbackEmpty([&] {
//            m_fadeOut->Start();
//            }))
//    );
//
//    m_fadeOut = propertyAnimatorFactory
//        ->FadeOut(m_textSprite, "linear", 0.2, 1, std::shared_ptr<engine::CallbackEmpty>(new engine::CallbackEmpty([&] {
//            m_fadeIn->Start();
//            }))
//    );
//
//    m_fadeIn->Start();

    /*

     Animator::Animate(delay, duration, curve, [&]{
        myObject->SetAlpha(0.5);
     });

     Animator::Animate(delay, duration, curve, [&](auto *animator){
        myObject->animator(animator).SetAlpha(0.5);
     });


     */

    auto animator = engine::Globals::animator();
    auto curve = engine::Globals::curveFactory()->Create(engine::LINEAR);

    m_textSprite->SetAlpha(0.f);

    animator->Animate(1, 30, curve, [&](auto *animator){
        m_textSprite->animator()->SetAlpha(animator, 1.0);
        //m_textSprite->GetAnimatableAlpha().Set(animator, 1.0f);
    });
}
