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

#include "sound_file.hpp"
#include "engine_interface.h"

using namespace engine;

static inline SoundFileState PictelSoundState2SoundFileState(PlayerState);

SoundFile::SoundFile(std::string filename)
:   SoundFileI(filename)
{
    m_soundPlayer = PictelSound::PlayerI::CreateFromFile(ENGINE().getFileAccess().GetFullPath(filename).c_str());
}

SoundFile::~SoundFile()
{
    if (m_soundPlayer != nullptr)
    {   delete m_soundPlayer;
        m_soundPlayer = nullptr;
    }
}

bool SoundFile::Preapre()
{
    if (m_soundPlayer == nullptr)
    {   return false;
    }

    return m_soundPlayer->Open();
}

void SoundFile::Play()
{
    if (m_soundPlayer == nullptr)
    {   return;
    }

    m_soundPlayer->Play();
}

void SoundFile::Pause()
{
    if (m_soundPlayer == nullptr)
    {   return;
    }

    m_soundPlayer->Pause();
}

void SoundFile::Stop()
{
    if (m_soundPlayer == nullptr)
    {   return;
    }

    m_soundPlayer->Stop();
}

void SoundFile::SetVolume(double volume)
{
    if (m_soundPlayer == nullptr)
    {   return;
    }

    m_soundPlayer->SetVolume(volume);
}

void SoundFile::SetLoops(bool loops)
{
    if (m_soundPlayer == nullptr)
    {   return;
    }

    m_soundPlayer->SetLoops(loops);
}

SoundFileState SoundFile::GetState()
{
    if (m_soundPlayer == nullptr)
    {   return UNKNOWN;
    }

    return PictelSoundState2SoundFileState(m_soundPlayer->GetState());
}

SoundFileStateObserverI* SoundFile::AddObserver(std::shared_ptr<CallableParameters1<SoundFileI*>> handler)
{
    if (m_soundPlayer == nullptr)
    {   return nullptr;
    }

    auto callback = new SoundFileStateObserver(this, handler);
    m_soundPlayer->AddCallback(std::move(callback));
    return callback;
}

void SoundFile::RemoveObserver(SoundFileStateObserverI* observer)
{
    if (m_soundPlayer == nullptr)
    {   return;
    }

    m_soundPlayer->RemoveCallback((SoundFileStateObserver*)observer);
}

void SoundFileStateObserver::UpdateState(SoundFileState state)
{
    m_handler->Call(m_parent);
}

void SoundFileStateObserver::PerformStateCallback(PlayerState state)
{
    UpdateState(PictelSoundState2SoundFileState(state));
}

inline SoundFileState PictelSoundState2SoundFileState(PlayerState state)
{
    switch (state)
    {
        case PLAYER_STOPPED:
            return STOPPED;
        case PLAYER_PREPARED:
            return PREPARED;
        case PLAYER_PLAYING:
            return PLAYING;
        case PLAYER_PAUSED:
            return PAUSED;
        case PLAYER_STOPPING:
            return PLAYING;
        case PLAYER_DISCARDED:
            return UNKNOWN;
    }
}
