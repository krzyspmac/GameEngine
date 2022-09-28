//
//  sound_file.hpp
//  Engine
//
//  Created by krzysp on 09/06/2022.
//

#ifndef sound_file_hpp
#define sound_file_hpp

#include "sound_interfaces.h"
#include "pictel_sound.hpp"
#include "callable.hpp"

namespace engine
{
    class SoundFileStateObserver: public SoundFileStateObserverI, public PictelSound::PlayerCallbackI
    {
    public:
        typedef std::shared_ptr<CallableParameters1<SoundFileI*>> FunctionType;
    public:
        SoundFileStateObserver(SoundFileI* parent, FunctionType handler)
        :   SoundFileStateObserverI()
        ,   m_parent(parent)
        ,   m_handler(handler)
        { };

    public: // SoundFileStateObserverI
        void UpdateState(SoundFileState);

    public: // PictelSound::PlayerCallbackI
        void PerformStateCallback(PlayerState);

    private:
        SoundFileI *m_parent;
        FunctionType m_handler;
    };

    class SoundFile: public SoundFileI
    {
        PictelSound::PlayerI *m_soundPlayer;
    public:
        SoundFile(std::string filename);
        ~SoundFile();

        bool Preapre();
        void Play();
        void Pause();
        void Stop();
        void SetVolume(double);
        void SetLoops(bool);
        SoundFileState GetState();
        SoundFileStateObserverI* AddObserver(SoundFileStateObserver::FunctionType);
        void RemoveObserver(SoundFileStateObserverI*);
    };
};

#endif /* sound_file_hpp */
