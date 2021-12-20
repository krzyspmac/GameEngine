//
//  engine_provider.hpp
//  RendererApp
//
//  Created by krzysp on 19/12/2021.
//

#ifndef engine_provider_hpp
#define engine_provider_hpp

#include "engine_provider_interface.h"

namespace engine
{
    class EngineProvider : public EngineProviderI
    {
    public:
        EngineProvider()
            :EngineProviderI()
        {
        }

//        void DrawDebugText(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, ...) override;
    };
};

#endif /* engine_provider_hpp */
