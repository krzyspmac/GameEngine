//
//  sound_file.cpp
//  Engine
//
//  Created by krzysp on 09/06/2022.
//

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
