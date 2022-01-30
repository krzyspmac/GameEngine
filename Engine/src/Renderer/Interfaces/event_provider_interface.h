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
    typedef enum
    {
        EVENT_NONE = 0
      , EVENT_KEY_FLAG_STATE_CHANGE
      , EVENT_KEY_STATE_CHANGE
      , EVENT_MOUSEMOVE
      , EVENT_MOUSEUP
      , EVENT_QUIT
    } EventType;

    typedef enum
    {
        FLAG_NONE   = 0
      , FLAG_SHIFT
      , FLAG_CONTROL
      , FLAG_ALT
      , FLAG_COMMAND
    } EventFlagType;

    EventFlagType String2EventFlagType(std::string);

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

    class EventKeyFlagStateChanged: public EventI
    {
        bool m_state;
        EventFlagType m_flagType;
    public:
        EventKeyFlagStateChanged() : EventI(EVENT_KEY_FLAG_STATE_CHANGE), m_state(false) { };
        EventFlagType& GetFlagType() { return m_flagType; };
        bool& GetState() { return m_state; };
    };

    class EventKeyStateChanged: public EventI
    {
        unsigned short m_key;
        bool m_keyDown;
    public:
        EventKeyStateChanged() : EventI(EVENT_KEY_STATE_CHANGE), m_key(0), m_keyDown(false) { };
        auto& GetKey() { return m_key; };
        bool& GetIsDown() { return m_keyDown; };
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

        /** Shift state changed */
        virtual void PushFlagsChange(EventFlagType, bool) = 0;

        /** Key state changed */
        virtual void PushKeyStateChange(unsigned short, bool) = 0;

        /** Poll an event from the queue. */
        virtual bool PollEvent(EventI **outEvent) = 0;
    };


    /** Public ASCII codes */
    typedef enum
    {
        CODE_TIDLE = '`'
    } ASCIIKeyCode;

}; // namespace engine

#endif /* event_provider_interface_h */
