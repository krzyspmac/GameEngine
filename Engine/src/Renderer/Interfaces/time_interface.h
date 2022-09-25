//
//  time_interface.h
//  Engine
//
//  Created by krzysp on 25/09/2022.
//

#ifndef time_interface_h
#define time_interface_h

#include "common.h"

namespace engine
{
    class TimeI
    {
    public:
        /**
         Returns the number of milliseconds since the moment
         the drawing engine started. For SDL as the drawing
         library this resets ~49 days.
         */
        virtual Uint64 GetEngineStart() = 0;

        /**
         The same as Time::GetEngineStart() but in seconds.
         */
        virtual double GetEngineStartSec() = 0;

        /**
         Returns the number of milliseconds from the frame start.
         */
        virtual Uint64 GetFrameStart() = 0;

        /**
         The same as Time::GetFrameStart() but in seconds.
         */
        virtual double GetFrameStartSec() = 0;

        /**
         Returns the interval between the last frame and the current
         one in milliseconds.
         */
        virtual Uint64 GetFrameDelta() = 0;

        /**
         The same as Time::GetFrameDelta() but in seconds.
         */
        virtual double GetFrameDeltaSec() = 0;

    };
};

#endif /* time_interface_h */
