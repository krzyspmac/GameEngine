//
//  sound_interfaces.h
//  Engine
//
//  Created by krzysp on 09/06/2022.
//

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
