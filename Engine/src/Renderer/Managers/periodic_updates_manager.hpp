//
//  periodic_updates_manager.hpp
//  Engine
//
//  Created by krzysp on 01/01/2022.
//

#ifndef periodic_updates_manager_hpp
#define periodic_updates_manager_hpp

#include "common.h"
#include "animation_interface.hpp"

namespace engine
{
    /**
     Keeps a list of AnimationPeriodicUpdateI. Does not handle its memory.
     */
    class PeriodicUpdatesManager
    {
        std::vector<AnimationPeriodicUpdateI*> m_list;
        bool m_hasItems;
    public:
        PeriodicUpdatesManager(): m_hasItems(false) { };

    private:
        /**
         Returns true if there's a need to restart the iteration
         (in case of a removed item for instance).
         */
        bool Iterate();

    public:
        /**
         */
        void Add(AnimationPeriodicUpdateI *obj);

        /**
         */
        void Remove(AnimationPeriodicUpdateI *obj);

        /**
         */
        void Update();
    };
};

#endif /* periodic_updates_manager_hpp */
