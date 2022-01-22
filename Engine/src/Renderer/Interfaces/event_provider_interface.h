//
//  event_provider_interface.h
//  RendererAppSDL
//
//  Created by krzysp on 21/12/2021.
//

#ifndef event_provider_interface_h
#define event_provider_interface_h

#include "common.h"
#include "common_engine_impl.h"

namespace engine
{

    typedef enum {
        EVENT_NONE = 0,
        EVENT_KEYDOWN,

        EVENT_MOUSEMOVE,
        EVENT_MOUSEUP,

        EVENT_QUIT,
    } EventType;

    /** Declares an abstract interface for different type of events received from
        the platform handlers. */
    class EventI
    {
        EventType m_eventType;
        bool m_inUse;
    public:
        EventI(EventType type)
            : m_eventType(type)
            , m_inUse(false)
        { };
        const EventType& GetType() { return m_eventType; };
        bool& GetInUse() { return m_inUse; };
    };

    class EventMouseMove: public EventI
    {
        Origin m_location;
    public:
        EventMouseMove(Origin location)
            : EventI(EVENT_MOUSEMOVE)
            , m_location(location)
        { };
        Origin& GetLocation() { return m_location; };
    };

    class EventMouseLeftUp: public EventI
    {
    public:
        EventMouseLeftUp() : EventI(EVENT_MOUSEUP) { };
    };

    /** Declares an abstract interface to provide real events directly into the
        engine. The platform code should setup its own processing and pass those
        events to the event provider.

        During one frame multiple events can be passed.
     */
    class EventProviderI
    {
    public:
        EventProviderI() { };

    public:
        /** Updates the current mouse location if applicable. Also sends out
            a mouse moved event. */
        virtual void PushMouseLocation(Origin) = 0;

        /** Left mouse button up */
        virtual void PushMouseLeftUp() = 0;

        /** Poll an event from the queue. */
        virtual bool PollEvent(EventI **outEvent) = 0;
    };

}; // namespace engine

#endif /* event_provider_interface_h */
