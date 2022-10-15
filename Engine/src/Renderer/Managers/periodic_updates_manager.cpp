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
