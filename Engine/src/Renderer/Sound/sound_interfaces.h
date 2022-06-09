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

namespace engine
{
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
    };

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
