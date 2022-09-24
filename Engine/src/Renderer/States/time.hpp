//
//  time_export.hpp
//  Engine
//
//  Created by krzysp on 24/09/2022.
//

#ifndef time_export_hpp
#define time_export_hpp

#include "common.h"
#include "time_scriptng.hpp"

#ifndef SCRIPTING_WRAPPER_BUILD
    #include "time_base.hpp"
#else
    #define TimeBase DummyClass
#endif

namespace engine
{
    /**
     Time
     \addtogroup API_GLOBALS
     */
    class Time: public TimeBase, public TimeExtInterface
    {
    public:
        using TimeBase::TimeBase;

    public:
        Uint64 GetEngineStart();
        double GetEngineStartSec();
        Uint64 GetFrameStart();
        double GetFrameStartSec();
        Uint64 GetFrameDelta();
        double GetFrameDeltaSec();
    };
};

#endif /* time_export_hpp */
