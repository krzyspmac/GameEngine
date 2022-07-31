//
//  static_objects.hpp
//  Engine-Mac
//
//  Created by krzysp on 31/07/2022.
//

#ifndef static_objects_hpp
#define static_objects_hpp

#include <stdio.h>
#include "engine_interface.h"

namespace engine
{
    template <typename T>
    class StaticMgr
    {
    private:
        T* m_value;

    public:
        StaticMgr()
            : m_value(nullptr)
        { };

        T* get()
        {
            return m_value;
        }

        void set(T *value)
        {
            m_value = value;
        }
    };

    class StaticObjects
    {
    public:
        static void init();

        static EngineI &engine();
        static void engine_provide(EngineI*);
    };
};

#endif /* static_objects_hpp */
