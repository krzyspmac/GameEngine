//
//  periodic_updates_manager.cpp
//  Engine
//
//  Created by krzysp on 01/01/2022.
//

#include "periodic_updates_manager.hpp"

using namespace engine;

void PeriodicUpdatesManager::Add(AnimationPeriodicUpdateI *obj)
{
    m_list.emplace_back(obj);
    m_hasItems = !m_list.empty();
}

void PeriodicUpdatesManager::Remove(AnimationPeriodicUpdateI *toRemove)
{
    for (auto it = m_list.begin(); it != m_list.end(); ++it)
    {
        if ((*it) == toRemove)
        {
            m_list.erase(it);
            break;
        }
    }
    m_hasItems = !m_list.empty();
}

bool PeriodicUpdatesManager::Iterate()
{
    size_t count = m_list.size();
    for (int i = 0; i < count; i++)
    {
        m_list.at(i)->Update();
        if (m_list.size() != count) { return true; }
    }
    return false;
}

void PeriodicUpdatesManager::Update()
{
    while (Iterate()) { };
}
