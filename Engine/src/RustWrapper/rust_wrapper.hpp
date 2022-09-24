//
//  rust_wrapper.h
//  Engine
//
//  Created by krzysp on 24/09/2022.
//

#ifndef rust_wrapper_h
#define rust_wrapper_h

#include "time.hpp"

namespace engine
{

    class Globals
    {
    protected:
        Globals();

    public:
        static engine::Time &time();
    };
}

#endif /* rust_wrapper_h */
