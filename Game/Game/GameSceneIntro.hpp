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
    std::vector<std::string> m_texts;
public: // GameSceneIntro
    GameSceneIntro(GameResolutionState*);
    void FrameUpdate();

public: // GameSceneI
    engine::SceneI *GetSceneObj() { return m_scene; };
    void DidActivate();
    void DidDeactivate();

private:
    void ContinueAnimation();

    void FadeIn();
    void FadeOut();
    void ScaleIn();
};

#endif /* GameSceneIntro_hpp */
