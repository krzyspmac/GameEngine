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

EventsManagerI *Globals::eventsManager()
{
    return static_cast<EventsManagerI*>(&(ENGINE().getEventsManager()));
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

SoundManagerI *Globals::soundManager()
{
    return static_cast<SoundManagerI*>(&(ENGINE().getSoundManager()));
}
