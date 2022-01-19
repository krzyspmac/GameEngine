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
        std::vector<std::unique_ptr<EventI>> m_poolMouseMove;
        std::vector<std::unique_ptr<EventI>> m_poolMouseLeftUp;
        std::vector<EventI*> m_eventQueue;
    public:
        EventProvider();

    public:
        void    PushMouseLocation(Origin);
        void    PushMouseLeftUp();
        bool    PollEvent(EventI **outEvent);

    private:
        void    EventsPoolPopulate();
        EventI* EventsPoolDequeue(EventType type);

        void    EventPush(EventI*);

    private: // helpers
        std::vector<std::unique_ptr<EventI>> *EventsPoolForType(EventType type);
    };

}; // namespace engine

#endif /* event_provider_hpp */
