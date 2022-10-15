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

#ifndef globals_hpp
#define globals_hpp

#include "interfaces.h"

namespace engine
{
    /** Globals
        \addtogroup API_GLOBALS
        Provides different managers for the game scripts and is generally the main
        connection point between the game scripts and the engine itself.
        Those are static and it's safe to keep their references.
     */
    class Globals
    {
    protected:
        Globals();

    public:
        static TimeI *time();

        static EngineStateI *engineState();

        static FontManagerI *fontManager();

        static EventsManagerI *eventsManager();

        static SpriteAtlasManagerI* spriteAtlasManager();

        static SceneManagerI *sceneManager();

        static AnimatorFactoryI *animator();

        static AnimationCurveFactoryI *curveFactory();

        static SoundManagerI* soundManager();
    };
}

#endif /* globals_hpp */
