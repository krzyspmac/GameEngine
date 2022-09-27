
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
    FadeIn();
//    ScaleIn();
    PositionIn();
}

void
GameSceneIntro::FadeIn()
{
    auto animator = engine::Globals::animator();
    auto curve = engine::Globals::curveFactory()->Create(engine::LINEAR);

    animator->Animate(1, .1, curve, [&](auto *animator){
        m_textSprite->animator()->SetAlpha(animator, 1.0);
    }, [&](void) {
        FadeOut();
    });
}

void
GameSceneIntro::ScaleIn()
{
    auto animator = engine::Globals::animator();
    auto curve = engine::Globals::curveFactory()->Create(engine::LINEAR);

    animator->Animate(1, 30, curve, [&](auto *animator){
        m_textSprite->animator()->SetScale(animator, 100);
    }, [&](void) {
    });
}

void
GameSceneIntro::FadeOut()
{
    auto animator = engine::Globals::animator();
    auto curve = engine::Globals::curveFactory()->Create(engine::LINEAR);

    animator->Animate(1, .1, curve, [&](auto *animator){
        m_textSprite->animator()->SetAlpha(animator, 0.0);
    }, [&](void){
        FadeIn();
    });
}

void
GameSceneIntro::PositionIn()
{
    auto animator = engine::Globals::animator();
    auto curve = engine::Globals::curveFactory()->Create(engine::LINEAR);

    animator->Animate(1, 5, curve, [&](auto *animator){
        m_textSprite->animator()->SetPosition(animator, {150, 500});
    }, [&](void){
    });
}
