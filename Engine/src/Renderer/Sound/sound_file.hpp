//
//  sound_file.hpp
//  Engine
//
//  Created by krzysp on 09/06/2022.
//

#ifndef sound_file_hpp
#define sound_file_hpp

#include "sound_interfaces.h"
#include "pictel_sound.h"
#include "scripting_engine_provider_interface.h"

namespace engine
{
    class SoundFile: public SoundFileI
    {
        PictelSoundRef m_soundRef;
        
    public:
        SoundFile(std::string filename);
        ~SoundFile();

        bool Preapre();
        void Play();
        void Pause();
        void Stop();

    /// ScriptingInterface
    public:
        /** @private */
        SCRIPTING_INTERFACE_HEADERS(SoundFile);
    };
};

#endif /* sound_file_hpp */
