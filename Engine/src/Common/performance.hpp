//
//  performance.hpp
//  Engine
//
//  Created by krzysp on 28/12/2021.
//

#ifndef performance_hpp
#define performance_hpp

#include <iostream>
#include "engine.hpp"

namespace engine
{

    inline void performanceMeasure(std::string what, std::function<void(void)>lambda)
    {
        EngineProviderI &provider = ENGINE().getProvider();
        Uint64 start = provider.GetTicks();

        lambda();

        Uint64 end = provider.GetTicks();
        Uint64 delta = end - start;
        std::cout << "performanceMeasure(" << what << ") = " << delta << "ms" << std::endl;
    };
};

#endif /* performance_hpp */
