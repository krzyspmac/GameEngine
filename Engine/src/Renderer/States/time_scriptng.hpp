//
//  time_scriptng.hpp
//  Engine
//
//  Created by krzysp on 24/09/2022.
//

#ifndef time_scriptng_h
#define time_scriptng_h

#include "common.h"

namespace engine
{

    class TimeExtInterface {

    public:
        /**
         Returns the number of milliseconds since the moment
         the drawing engine started. For SDL as the drawing
         library this resets ~49 days.
         */
        Uint64 GetEngineStart() { return 0; };

        /**
         The same as Time::GetEngineStart() but in seconds.
         */
        double GetEngineStartSec() { return 0.0f; };

        /**
         Returns the number of milliseconds from the frame start.
         */
        Uint64 GetFrameStart() { return 0; };

        /**
         The same as Time::GetFrameStart() but in seconds.
         */
        double GetFrameStartSec() { return 0.0f; };

        /**
         Returns the interval between the last frame and the current
         one in milliseconds.
         */
        Uint64 GetFrameDelta() { return 0; };

        /**
         The same as Time::GetFrameDelta() but in seconds.
         */
        double GetFrameDeltaSec() { return 0.0f; };
    };
};


#endif /* time_scriptng_h */
