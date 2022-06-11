//
//  sound_file.hpp
//  Engine
//
//  Created by krzysp on 09/06/2022.
//

#ifndef sound_file_hpp
#define sound_file_hpp

#include "sound_interfaces.h"
#include "scripting_engine_provider_interface.h"
#include "pictel_sound.hpp"
#include "callable.hpp"

namespace engine
{
    class SoundFileStateObserverLUA: public SoundFileStateObserverI, public PictelSound::PlayerCallbackI
    {
        CallableScriptFunctionNumber m_luaFunc;
    public:
        SoundFileStateObserverLUA(CallableScriptFunctionI::CallableScriptFunctionRef function)
        :   SoundFileStateObserverI()
        ,   m_luaFunc(CallableScriptFunctionNumber(function))
        { };

        void UpdateState(SoundFileState);

    public: // PictelSound::PlayerCallbackI
        void PerformStateCallback(PlayerState);
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
        SoundFileStateObserverI* AddObserver(CallableScriptFunctionI::CallableScriptFunctionRef);
        void RemoveObserver(SoundFileStateObserverI*);

    /// ScriptingInterface
    public:
        /** @private */
        SCRIPTING_INTERFACE_HEADERS(SoundFile);
    };
};

#endif /* sound_file_hpp */
