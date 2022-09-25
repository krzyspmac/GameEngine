//
//  memory.h
//  Engine
//
//  Created by krzysp on 04/01/2022.
//

#ifndef memory_h
#define memory_h

#include "common.h"

namespace engine
{

    /**
     An abstract interface to deal with releasing object.
     During the course of the lifecycle of the game scripts
     many objects can be created. To limit the number of
     managers, those objects that do not belong to a manager
     land in a common ReleaseQueue. At the end of the script
     (or scene change) the ReleaseQueue is drained. The Queue
     should contain only those object that fit the "dangling
     in memory" criterion.
     
     Some object may `keep` the objects for longer thus preventing
     the MemoryI::ReleaseMem() function from actually releasing the object.
     */
    class MemoryI
    {
        int m_counter;
    public:
        MemoryI() : m_counter(0) { };
        virtual ~MemoryI() { };
        void Keep() {
            m_counter++;
        };
        void Release() {
            m_counter--;
            FreeMem();
            
        };
        void FreeMem() {
            if (m_counter <= 0) {
                delete this;
            }
        };
    };

    /**
     An abstract interface to implement a shared memory pool
     that keeps dangling objects that the game script might
     not have manually removed.
     
     The pool should be drained when there's no danger of removal
     objects in use.
     */
    class MemoryReleasePoolI
    {
    public:
        /** @private */
        virtual ~MemoryReleasePoolI() { };
        
        /**
         Store an object in the pool.
         */
        virtual void Sink(MemoryI*) = 0;
        
        /**
         Drain the pool, calling ReleaseMem on all
         members.
         */
        virtual void Drain() = 0;
    };

}; // namespace engine

#endif /* memory_h */
