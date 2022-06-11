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
    m_soundPlayer = PictelSound::PlayerI::CreateFromFile(GetMainEngine()->getFileAccess().GetFullPath(filename).c_str());
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

SoundFileStateObserverI* SoundFile::AddObserver(CallableScriptFunctionI::CallableScriptFunctionRef function)
{
    if (m_soundPlayer == nullptr)
    {   return nullptr;
    }

    auto callback = new SoundFileStateObserverLUA(function);
    m_soundPlayer->AddCallback(std::move(callback));
    return callback;
}

void SoundFile::RemoveObserver(SoundFileStateObserverI* observer)
{
    if (m_soundPlayer == nullptr)
    {   return;
    }

    m_soundPlayer->RemoveCallback((SoundFileStateObserverLUA*)observer);
}

//
// SoundFileStateObserverLUA
//

void SoundFileStateObserverLUA::UpdateState(SoundFileState state)
{
    m_luaFunc.PerformCall(state);
}

void SoundFileStateObserverLUA::PerformStateCallback(PlayerState state)
{
    UpdateState(PictelSoundState2SoundFileState(state));
}

//
// Scripting
//

SCRIPTING_INTERFACE_IMPL_NAME(SoundFile);

static int lua_Play(lua_State *L)
{
    SoundFile **ptr = (SoundFile**)luaL_checkudata(
        L, 1, SoundFile::ScriptingInterfaceName().c_str()
    );
    if (ptr != nullptr && dynamic_cast<SoundFile*>(*ptr) == nullptr) { return 0; }

    (*ptr)->Play();
    return 0;
}

static int lua_Pause(lua_State *L)
{
    SoundFile **ptr = (SoundFile**)luaL_checkudata(
        L, 1, SoundFile::ScriptingInterfaceName().c_str()
    );
    if (ptr != nullptr && dynamic_cast<SoundFile*>(*ptr) == nullptr) { return 0; }

    (*ptr)->Pause();
    return 0;
}

static int lua_Stop(lua_State *L)
{
    SoundFile **ptr = (SoundFile**)luaL_checkudata(
        L, 1, SoundFile::ScriptingInterfaceName().c_str()
    );
    if (ptr != nullptr && dynamic_cast<SoundFile*>(*ptr) == nullptr) { return 0; }

    (*ptr)->Stop();
    return 0;
}

static int lua_SetVolume(lua_State *L)
{
    SoundFile **ptr = (SoundFile**)luaL_checkudata(
        L, 1, SoundFile::ScriptingInterfaceName().c_str()
    );
    if (ptr != nullptr && dynamic_cast<SoundFile*>(*ptr) == nullptr) { return 0; }

    double volume = lua_tonumber(L, 2);
    (*ptr)->SetVolume(volume);
    return 0;
}

static int lua_SetLoops(lua_State *L)
{
    SoundFile **ptr = (SoundFile**)luaL_checkudata(
        L, 1, SoundFile::ScriptingInterfaceName().c_str()
    );
    if (ptr != nullptr && dynamic_cast<SoundFile*>(*ptr) == nullptr) { return 0; }

    bool loops = lua_tonumber(L, 2);
    (*ptr)->SetLoops(loops);
    return 0;
}

static int lua_AddObserver(lua_State *L)
{
    SoundFile *obj = ScriptingEngineI::GetScriptingObjectPtr<SoundFile>(L, 1);
    int functionRef = luaL_ref( L, LUA_REGISTRYINDEX );

    auto result = obj->AddObserver(functionRef);
    lua_pushlightuserdata(L, result);
    return 1;
}

static int lua_RemoveObserver(lua_State *L)
{
    SoundFile *obj = ScriptingEngineI::GetScriptingObjectPtr<SoundFile>(L, 1);
    SoundFileStateObserverI *observer = (SoundFileStateObserverI*)lua_touserdata(L, 2);

    obj->RemoveObserver(observer);
    return 0;
}

std::vector<luaL_Reg> SoundFile::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "Play",           &lua_Play }
    ,   { "Pause",          &lua_Pause }
    ,   { "Stop",           &lua_Stop }
    ,   { "SetVolume",      &lua_SetVolume }
    ,   { "SetLoops",       &lua_SetLoops }
    ,   { "AddObserver",    &lua_AddObserver }
    ,   { "RemoveObserver", &lua_RemoveObserver }
    });
    return result;
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
