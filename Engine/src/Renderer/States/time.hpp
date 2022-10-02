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

#ifndef time_hpp
#define time_hpp

#include "common.h"
#include "time_interface.h"
#include "engine_provider_interface.h"
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
