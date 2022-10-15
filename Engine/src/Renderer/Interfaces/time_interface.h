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

#ifndef time_interface_h
#define time_interface_h

#include "common.h"

namespace engine
{
    /** TimeI
        \addtogroup API_GLOBALS
        Keeps the time for the engine including game engine start and incremental time
        between each frame so it's possible to properly animate different sprites/states.
     */
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
