//
//  globals.hpp
//  Engine
//
//  Created by krzysp on 25/09/2022.
//

#ifndef globals_hpp
#define globals_hpp

#include "interfaces.h"

namespace engine
{

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
