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
        obj->ReleaseMem();
    }
    m_pool.clear();
}

SCRIPTING_INTERFACE_IMPL_NAME(MemoryReleasePool);

static int lua_MemoryReleasePool_Drain(lua_State *L)
{
    MemoryReleasePool *obj = ScriptingEngineI::GetScriptingObjectPtr<MemoryReleasePool>(L, 1);
    obj->Drain();
    return 0;
}

std::vector<luaL_Reg> MemoryReleasePool::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        {"Drain", &lua_MemoryReleasePool_Drain},
    });
    return result;
}
