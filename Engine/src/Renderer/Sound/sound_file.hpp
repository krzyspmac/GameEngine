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

#ifndef sound_file_hpp
#define sound_file_hpp

#include "sound_interfaces.h"
#include "pictel_sound.hpp"

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
