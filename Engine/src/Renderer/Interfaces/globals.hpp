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
