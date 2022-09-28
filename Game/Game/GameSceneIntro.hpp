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

#ifndef GameSceneIntro_hpp
#define GameSceneIntro_hpp

#include "game_scene_interface.hpp"
#include "interfaces.h"
#include "GameResolutionState.hpp"
#include "InertiaProcessor.hpp"

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

    IntertiaProcessor m_inertiaProcessor;
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
