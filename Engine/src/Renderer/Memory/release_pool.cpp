//
//  release_pool.cpp
//  Engine
//
//  Created by x180611 on 05/01/2022.
//

#include "release_pool.hpp"

using namespace engine;

MemoryReleasePool::MemoryReleasePool()
{
}

MemoryReleasePool::~MemoryReleasePool()
{
    Drain();
}

void MemoryReleasePool::Sink(MemoryI *ptr)
{
    if (ptr != nullptr)
    {
        m_pool.emplace_back(ptr);
    }
}

void MemoryReleasePool::Drain()
{
    size_t count = m_pool.size();
    for (int i = 0; i < count; i++)
    {
        MemoryI *obj = m_pool.at(i);
        obj->FreeMem();
    }
    m_pool.clear();
}
