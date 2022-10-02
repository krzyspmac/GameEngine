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

#include "engine_metal_buffer_manager.hpp"

#define DEFAULT_BLOCK_SIZE  (128 * 1024)

using namespace engine;

MetalBufferManager* MetalBufferManager::Shared()
{
    static MetalBufferManager *sharedInstance = new MetalBufferManager();
    return sharedInstance;
}

MetalBufferManager::MetalBufferManager()
    : m_currentBuffer(nullptr)
    , m_currentBufferSize(0)
    , m_currentBufferLeftBytes(0)

{
}

MetalBufferManager::~MetalBufferManager()
{
    Free();
}

void MetalBufferManager::NewBlock(MTL::Device *device)
{
    auto* blockBuffer = device->newBuffer(DEFAULT_BLOCK_SIZE, MTL::ResourceStorageModeShared);
    m_buffers.emplace_back(blockBuffer);
    m_currentBuffer = blockBuffer;
    m_currentBufferSize = 0;
    m_currentBufferLeftBytes = DEFAULT_BLOCK_SIZE;
}

void MetalBufferManager::Free()
{
    for (auto& buffer : m_buffers)
    {
        buffer->release();
    }

    m_buffers.clear();
    m_currentBuffer = nullptr;
    m_currentBufferSize = 0;
    m_currentBufferLeftBytes = DEFAULT_BLOCK_SIZE;
}

void MetalBufferManager::RegisterData(MTL::Device *device, void *bytes, size_t length, std::function<void(MTL::Buffer*, size_t offset)> result)
{
    if (m_currentBuffer == nullptr || m_currentBufferLeftBytes <= length)
    {
        NewBlock(device);
    }

    if (m_currentBuffer == nullptr)
    {
        printf("Could not create a buffer for data!");
        return;
    }

    // Copy data over to the buffer.
    void *ptr = static_cast<char *>(m_currentBuffer->contents()) + m_currentBufferSize;
    memcpy(ptr, bytes, length);

    // Inform the lambda of the result
    result(m_currentBuffer, m_currentBufferSize);

    // Increase the bytes used counter
    m_currentBufferSize += length;
    m_currentBufferLeftBytes -= length;
}
