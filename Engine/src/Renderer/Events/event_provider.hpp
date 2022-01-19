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

    public:
        void DoEvent();
        void SetMouseLocation(Origin);
        int PollEvent(EVENT *event, SDL_Event *originalEvent);
    };

}; // namespace engine

#endif /* event_provider_hpp */
