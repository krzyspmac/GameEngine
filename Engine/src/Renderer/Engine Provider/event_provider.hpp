//
//  event_provider.hpp
//  RendererAppSDL
//
//  Created by krzysp on 21/12/2021.
//

#ifndef event_provider_hpp
#define event_provider_hpp

#include "common.h"
#include "event_provider_interface.h"

namespace engine
{
    class EventProvider: public EventProviderI
    {
    public:
        EventProvider(): EventProviderI() { };

        int PollEvent(EVENT *event);
    };

}; // namespace engine

#endif /* event_provider_hpp */
