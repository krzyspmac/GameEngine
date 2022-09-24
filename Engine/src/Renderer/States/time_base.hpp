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
    /** @private */
    class TimeBase
    {
    protected:
        EngineProviderI& m_engineProvider;
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
        /** @private */
        TimeBase(EngineProviderI &provider);

    public:
        /** @private */
        void Prepare();

        /** @private */
        void PreUpdate();

        /** @private */
        void PostUpdate();

    /// ScriptingInterface
    public:
        /** @private */
        SCRIPTING_INTERFACE_HEADERS(TimeBase);
    };
};

#endif /* time_hpp */
