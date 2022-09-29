//
//  time.hpp
//  Engine
//
//  Created by krzysp on 01/01/2022.
//

#ifndef time_hpp
#define time_hpp

#include "common.h"
#include "engine_provider_interface.h"
#include "time_interface.h"
#include <iostream>

namespace engine
{
    class Time: public TimeI
    {
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
        Time(EngineProviderI &provider);

    public:
        Uint64 GetEngineStart();
        double GetEngineStartSec();
        Uint64 GetFrameStart();
        double GetFrameStartSec();
        Uint64 GetFrameDelta();
        double GetFrameDeltaSec();

    public:
        /** @private */
        void Prepare();

        /** @private */
        void PreUpdate();

        /** @private */
        void PostUpdate();
    };
};

#endif /* time_hpp */
