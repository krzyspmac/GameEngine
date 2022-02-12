//
//  engine_metal_buffer_manager.hpp
//  Engine
//
//  Created by krzysp on 10/02/2022.
//

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
