//
//  globals.cpp
//  Engine
//
//  Created by krzysp on 25/09/2022.
//

#include "globals.hpp"
#include "interfaces.h"
#include "easy.h"
#include "time.hpp"
#include "animation_curve_factory.hpp"
#include "animator.hpp"
#include "animator_factory.hpp"

using namespace engine;

TimeI * Globals::time()
{
    return static_cast<TimeI*>(&(ENGINE().getTime()));
}

EngineStateI * Globals::engineState()
{
    return static_cast<EngineStateI*>(&(ENGINE().getEngineState()));
}

FontManagerI * Globals::fontManager()
{
    return static_cast<FontManagerI*>(&(ENGINE().getFontManager()));
}

SpriteAtlasManagerI* Globals::spriteAtlasManager()
{
    return static_cast<SpriteAtlasManagerI*>(&(ENGINE().getAtlasManager()));
}

SceneManagerI * Globals::sceneManager()
{
    return static_cast<SceneManagerI*>(&(ENGINE().getSceneManager()));
}

AnimationCurveFactoryI *Globals::curveFactory()
{
    return static_cast<AnimationCurveFactoryI*>(&(ENGINE().getAnimationCurveFactory()));
}

AnimatorFactoryI *Globals::animator()
{
    static AnimatorFactory *animator = new AnimatorFactory();
    return animator;
}
