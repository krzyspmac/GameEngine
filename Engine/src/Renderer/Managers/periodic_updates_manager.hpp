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
