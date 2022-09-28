
#include "GameSceneIntro.hpp"

using namespace engine;

GameSceneIntro::GameSceneIntro(GameResolutionState *resState)
    : m_resState(resState)
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

    m_callabackGamepadConnectionId = engine
        ::Globals
        ::eventsManager()
        ->RegisterGamepadConnection(
            CallableParameters2<GamepadI *, bool>::make_shared([&](auto* gamepad, bool){
                OnGamepadConnection(gamepad);
            })
        );

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
}

void GameSceneIntro::DidActivate()
{
    ContinueAnimation();
}

void GameSceneIntro::DidDeactivate() { }

void GameSceneIntro::OnGamepadConnection(GamepadI* gamepad)
{
    if (gamepad != nullptr) {
        gamepad->RegisterLeftThumbstickAxis(CallableParameters1<Vector2>::make_shared([&](Vector2 vect){

        }));
        gamepad->RegisterRightThumbstickAxis(CallableParameters1<Vector2>::make_shared([&](Vector2 vect){

        }));
        gamepad->RegisterButtonTapped(CallableParameters3<GamepadButtonType, GamepadButtonAction, float>::make_shared([&](auto buttonType, auto buttonAction, auto value){

        }));
    }
}

void GameSceneIntro::FrameUpdate() { }

void GameSceneIntro::ContinueAnimation()
{
    FadeIn();
    RotationIn();
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
