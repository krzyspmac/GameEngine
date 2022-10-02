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
