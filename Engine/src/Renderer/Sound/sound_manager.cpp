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
