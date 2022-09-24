//
//  time.hpp
//  Engine
//
//  Created by krzysp on 01/01/2022.
//

#ifndef time_hpp
#define time_hpp

#ifndef SCRIPTING_WRAPPER_BUILD
#include "scripting_engine_provider_interface.h"
#include "engine_provider_interface.h"
#include <iostream>
#endif

#include "common.h"

namespace engine
{
    /**
     Time
     \addtogroup API_GLOBALS
     */
    class Time
    {
    private:
        __scriptintWrapperHidden(
        EngineProviderI& m_engineProvider;
        )
        Uint64 m_beginning;
        Uint64 m_engineStart;
        double m_engineStatSec;
        Uint64 m_frameStart;
        double m_frameStartSec;
        Uint64 m_previousFrameStart;
        double m_previousFrameStartSec;
        Uint64 m_frameDelta;
        double m_frameDeltaSec;
    public:
        __scriptintWrapperHidden(
        /** @private */
        Time(EngineProviderI &provider);
        )

    public:

        /**
         Returns the number of milliseconds since the moment
         the drawing engine started. For SDL as the drawing
         library this resets ~49 days.
         */
        Uint64 GetEngineStart();

        /**
         The same as Time::GetEngineStart() but in seconds.
         */
        double GetEngineStartSec();

        /**
         Returns the number of milliseconds from the frame start.
         */
        Uint64 GetFrameStart();

        /**
         The same as Time::GetFrameStart() but in seconds.
         */
        double GetFrameStartSec();

        /**
         Returns the interval between the last frame and the current
         one in milliseconds.
         */
        Uint64 GetFrameDelta();

        /**
         The same as Time::GetFrameDelta() but in seconds.
         */
        double GetFrameDeltaSec();

    public:
        /** @private */
        void Prepare();

        /** @private */
        void PreUpdate();

        /** @private */
        void PostUpdate();

    __scriptintWrapperHidden(
    /// ScriptingInterface
    public:
        /** @private */
        SCRIPTING_INTERFACE_HEADERS(Time);
    )
    };
};

#endif /* time_hpp */
