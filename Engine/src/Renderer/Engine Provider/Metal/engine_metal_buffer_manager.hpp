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

#ifndef engine_metal_buffer_manager_hpp
#define engine_metal_buffer_manager_hpp

#include "common.h"
#include <iostream>
#include <vector>
#include <Metal/Metal.hpp>
#include "AAPLShaderTypes.h"

namespace engine
{
    /** A manager to limit the amount of memory used by MTLBuffer. By default MTLBuffer
        can allocate memory in chunks. Having each large chunk holding just a couple
        or vertices is not efficient. This manager combines different objects into
        one block. */
    class MetalBufferManager
    {
        std::vector<MTL::Buffer*> m_buffers;
        MTL::Buffer *m_currentBuffer;
        size_t m_currentBufferSize;
        size_t m_currentBufferLeftBytes;
    public:

        /** */
        MetalBufferManager();
        ~MetalBufferManager();
        static MetalBufferManager* Shared();
        
        /** Registers memory for a buffer. Returns the pointer for the buffer
            and the the offset to be used when rendering the particular part. */
        void RegisterData(MTL::Device*, void *bytes, size_t length, std::function<void(MTL::Buffer*, size_t offset)> result);

        /** Frees the buffer. */
        void Free();

    private:
        void NewBlock(MTL::Device*);
    };
};

#endif /* engine_metal_buffer_manager_hpp */
