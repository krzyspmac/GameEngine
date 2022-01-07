//
//  console_renderer.hpp
//  Engine
//
//  Created by krzysp on 07/01/2022.
//

#ifndef console_renderer_hpp
#define console_renderer_hpp

#include "common.h"
#include "engine_provider_interface.h"

namespace engine
{
    class ConsoleRendererI
    {
    public:
        virtual void Setup() = 0;

        virtual void DoFrame() = 0;

        virtual void SetConsoleHidden(bool) = 0;
    };
};

#endif /* console_renderer_hpp */
