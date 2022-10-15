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

#ifndef sound_interfaces_h
#define sound_interfaces_h

#include <iostream>
#include <vector>
#include "callable_interface.h"

namespace engine
{
    typedef enum
    {
        UNKNOWN     = -1,
        IDLE        = 0,
        PREPARED    = 10,
        STOPPED     = 11,
        PLAYING     = 12,
        PAUSED      = 13
    } SoundFileState;

    class SoundFileStateObserverI
    {
    public:
        SoundFileStateObserverI() { };

        virtual void UpdateState(SoundFileState) = 0;
    };

    class SoundFileI
    {
    public:
        /** Ogg/vorbis filename existing within the game's data folder */
        /** @private */
        SoundFileI(std::string filename) { }

        /** @private */
        virtual ~SoundFileI() { }

        /** Plays the sound file */
        virtual void Play() = 0;

        /** Prepares the sound file */
        virtual bool Preapre() = 0;

        /** Pauses the sound file */
        virtual void Pause() = 0;

        /** Stops the sound file */
        virtual void Stop() = 0;

        /** Set the volume. 0.0-1.0 */
        virtual void SetVolume(double) = 0;

        /** Set the looping attribute */
        virtual void SetLoops(bool) = 0;

        /** Get the player state */
        virtual SoundFileState GetState() = 0;

        /** Add an observer for the sound file state */
        virtual  SoundFileStateObserverI* AddObserver(std::shared_ptr<CallableParameters1<SoundFileI*>>) = 0;

        /** Remove an observer */
        virtual void RemoveObserver(SoundFileStateObserverI*) = 0;
    };

    /** SoundManagerI
        \addtogroup API_GLOBALS

        Manages the scene's sound files.
     */
    class SoundManagerI
    {
    public:
        /** @private */
        SoundManagerI() { }

        /** Load a sound file. SoundManager manages the memory */
        virtual SoundFileI* Load(std::string) = 0;

        /** Unload a sound file. */
        virtual void Unload(SoundFileI*) = 0;
    };
};

#endif /* sound_interfaces_h */
