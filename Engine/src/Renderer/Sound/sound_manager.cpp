//
//  sound_manager.cpp
//  Engine
//
//  Created by krzysp on 09/06/2022.
//

#include "sound_manager.hpp"
#include "sound_file.hpp"
#include "general.hpp"

using namespace engine;

SoundManager::SoundManager()
:   SoundManagerI()
{
}

SoundFileI* SoundManager::Load(std::string filename)
{
    auto sound = new SoundFile(filename);
    if (!sound)
    {   return nullptr;
    }

    if (!sound->Preapre())
    {   delete sound;
        return nullptr;
    }

    m_items.emplace_back(std::move(sound));
    return sound;
}

void SoundManager::Unload(SoundFileI* item)
{
    for (auto it = m_items.begin(); it != m_items.end(); ++it)
    {
        if (it->get() == item)
        {
            m_items.erase(it);
            return;
        }
    }
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(SoundManager);

static int lua_Load(lua_State *L)
{
    SoundManager **ptr = (SoundManager**)luaL_checkudata(
        L, 1, SoundManager::ScriptingInterfaceName().c_str()
    );
    if (ptr != nullptr && dynamic_cast<SoundManager*>(*ptr) == nullptr) { return 0; }

    std::string filename = luaL_checkstring(L, 2);
    SoundFile *soundFile = (SoundFile*)(*ptr)->Load(filename);
    if (soundFile != nullptr)
    {   soundFile->ScriptingInterfaceRegisterFunctions(L, soundFile);
        return 1;
    }
    else
    {   return 0;
    }
}

static int lua_Unload(lua_State *L)
{
    SoundManager **mgr = (SoundManager**)luaL_checkudata(
        L, 1, SoundManager::ScriptingInterfaceName().c_str()
    );
    if (mgr != nullptr && dynamic_cast<SoundManager*>(*mgr) == nullptr) { return 0; }

    SoundFile **sound = (SoundFile**)luaL_checkudata(
        L, 2, SoundFile::ScriptingInterfaceName().c_str()
    );
    if (sound != nullptr && dynamic_cast<SoundFile*>(*sound) == nullptr) { return 0; }

    (*mgr)->Unload(*sound);
    return 0;
}

std::vector<luaL_Reg> SoundManager::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "Load",   &lua_Load }
    ,   { "Unload", &lua_Unload }
    });
    return result;
}
