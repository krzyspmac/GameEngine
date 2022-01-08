//
//  release_pool.hpp
//  Engine
//
//  Created by x180611 on 05/01/2022.
//

#ifndef release_pool_hpp
#define release_pool_hpp

#include "scripting_engine_provider_interface.h"
#include "memory.h"

namespace engine
{
    /**
     MemoryReleasePool
     \addtogroup API_GLOBALS
     */
    /** Keeps references to object that otherwise are not being managed
        by any other manager. Some animators are being created and returned
        to the script. Those by definition are dangling in memory. In order not
        to loose them thay are sinked in the pool.
     
        Generally only for objects available to the script functions.
        Scene change should automatically take care of its memory pool
     */
    class MemoryReleasePool: public MemoryReleasePoolI
    {
        std::vector<MemoryI*> m_pool;
    public:
        MemoryReleasePool();
        ~MemoryReleasePool();
        
        /** @private */
        void Sink(MemoryI*);
        
        /**
         Drain the memory pool releasing all stored objects.
         This should be done only sparringly as there is a possibility
         that an object in use will be removed in due process.
         Usually drain the resources when one knows those in the pool
         are no longer activly being used.
         */
        void Drain();
        
    /// ScriptingInterface
    public:
        /// @private
        SCRIPTING_INTERFACE_HEADERS(MemoryReleasePool);
    };
};

#endif /* release_pool_hpp */
