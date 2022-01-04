//
//  memory.h
//  Engine
//
//  Created by krzysp on 04/01/2022.
//

#ifndef memory_h
#define memory_h

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
     */
    class MemoryI
    {
    public:
        virtual ~MemoryI() { };
        void ReleaseMem() { delete this; };
    };

}; // namespace engine

#endif /* memory_h */
