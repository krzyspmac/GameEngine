//
//  GameSceneIntro.hpp
//  Game-Mac
//
//  Created by krzysp on 25/09/2022.
//

#ifndef GameSceneIntro_hpp
#define GameSceneIntro_hpp

#include "game_scene_interface.hpp"
#include "interfaces.h"
#include "GameResolutionState.hpp"

class GameSceneIntro: public GameSceneI {
    GameResolutionState *m_resState;
    engine::FontI *m_font;
    engine::SceneI *m_scene;
    engine::SpriteRepresentationTextI *m_textSprite;
    engine::SpriteRepresentationI *m_background;
    engine::SpriteRepresentationI *m_animated;
    engine::LightI *m_light;
    std::vector<std::string> m_texts;

    engine::SoundFileI *m_sound;

    std::shared_ptr<engine::CallableParameters2<engine::GamepadI *, bool>>  m_callabackGamepadConnection;
    engine::EventIdentifier m_callabackGamepadConnectionId;
public: // GameSceneIntro
    GameSceneIntro(GameResolutionState*);
    void FrameUpdate();

public: // GameSceneI
    engine::SceneI *GetSceneObj() { return m_scene; };
    void DidActivate();
    void DidDeactivate();

public: // Events
    void OnGamepadConnection(engine::GamepadI*);

private:
    void ContinueAnimation();

    void FadeIn();
    void FadeOut();
    void ScaleIn();
    void PositionIn();
    void RotationIn();
};

#endif /* GameSceneIntro_hpp */
