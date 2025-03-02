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
#include "ParticleEmitter.hpp"

using namespace engine;

class GameSceneIntro: public GameSceneI {
    GameResolutionState *m_resState;
    FontI *m_font;
    SceneI *m_scene;
    SpriteRepresentationTextI *m_textSprite;
    SpriteRepresentationI *m_background;
    SpriteRepresentationI *m_animated;
    LightI *m_light;
    std::vector<std::string> m_texts;

    engine::SoundFileI *m_sound;
    IntertiaProcessor m_inertiaProcessor;
    GameInputI *m_gameInput;

    ParticleEmitter *m_particleEmitter;
    SpriteAtlasI *m_ParticlesSpriteAtlas;
public: // GameSceneIntro
    GameSceneIntro(GameResolutionState*, GameInputI*);
    void FrameUpdate();

public: // GameSceneI
    engine::SceneI *GetSceneObj() { return m_scene; };
    void DidActivate();
    void DidDeactivate();

public: // Events

private:
    void ContinueAnimation();

    void FadeIn();
    void FadeOut();
    void ScaleIn();
    void PositionIn();
    void RotationIn();
};

#endif /* GameSceneIntro_hpp */
