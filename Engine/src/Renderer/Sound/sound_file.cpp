//
//  sound_file.cpp
//  Engine
//
//  Created by krzysp on 09/06/2022.
//

#include "sound_file.hpp"
#include "engine_interface.h"

using namespace engine;

SoundFile::SoundFile(std::string filename)
:   SoundFileI(filename)
{
    m_soundRef = PictelSoundCreate(GetMainEngine()->getFileAccess().GetFullPath(filename).c_str());
}

SoundFile::~SoundFile()
{
    if (m_soundRef != nullptr)
    {   PictelSoundRelease(m_soundRef);
        m_soundRef = nullptr;
    }
}

bool SoundFile::Preapre()
{
    if (m_soundRef == nullptr)
    {   return false;
    }

    return PictelSoundOpen(m_soundRef);
}

void SoundFile::Play()
{
    if (m_soundRef == nullptr)
    {   return;
    }

    PictelSoundPlay(m_soundRef);
}

void SoundFile::Pause()
{
    if (m_soundRef == nullptr)
    {   return;
    }

    PictelSoundPause(m_soundRef);
}

void SoundFile::Stop()
{
    if (m_soundRef == nullptr)
    {   return;
    }

    PictelSoundStop(m_soundRef);
}

void SoundFile::SetVolume(double volume)
{
    if (m_soundRef == nullptr)
    {   return;
    }

    PictelSoundSetVolume(m_soundRef, volume);
}

void SoundFile::SetLoops(bool loops)
{
    if (m_soundRef == nullptr)
    {   return;
    }

    PictelSoundSetLoops(m_soundRef, loops);
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

std::vector<luaL_Reg> SoundFile::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "Play",       &lua_Play }
    ,   { "Pause",      &lua_Pause }
    ,   { "Stop",       &lua_Stop }
    ,   { "SetVolume",  &lua_SetVolume }
    ,   { "SetLoops",   &lua_SetLoops }
    });
    return result;
}
