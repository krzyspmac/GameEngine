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

#ifndef release_pool_hpp
#define release_pool_hpp

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
    };
};

#endif /* release_pool_hpp */
