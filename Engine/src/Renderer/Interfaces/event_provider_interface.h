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
#include "event_provider_interface.h"

namespace engine
{
    typedef enum
    {
        EVENT_NONE = 0
      , EVENT_KEY_FLAG_STATE_CHANGE
      , EVENT_KEY_STATE_CHANGE
      , EVENT_MOUSEMOVE
      , EVENT_MOUSEUP
      , EVENT_GAMEPAD_THUMSTICK_AXIS_CHANGE
      , EVENT_GAMEPAD_CONNECTION_CHANGE
      , EVENT_QUIT
    } EventType;

    typedef enum
    {
        GAMEPAD_THUMBSTICK_AXIS_LEFT = 0
      , GAMEPAD_THUMBSTICK_AXIS_RIGHT
      , GAMEPAD_DPAD
    } GamepadThunbstickAxis;

    typedef enum
    {
        FLAG_NONE   = 0
      , FLAG_SHIFT
      , FLAG_CONTROL
      , FLAG_ALT
      , FLAG_COMMAND
    } EventFlagType;

    typedef enum
    {
        GAMEPAD_TYPE_UNKNOWN = 0,
        GAMEPAD_TYPE_SIMPLE = 1,
        GAMEPAD_TYPE_EXTENDED = 2,
    } GamepadType;

    typedef enum
    {
        GAMEPAD_MAKE_UNKNOWN = 0,
        GAMEPAD_MAKE_SONY = 1,
        GAMEPAD_MAKE_MICROSOFT = 2,
    } GamepadMakeFamily;

    typedef enum
    {
        GAMEPAD_CONNECTION_STATUS_UNKNOWN = 0,
        GAMEPAD_CONNECTION_STATUS_CONNECTED = 1,
        GAMEPAD_CONNECTION_STATUS_DISCRONNECTED = 2
    } GamepadConnectionStatus;

    EventFlagType String2EventFlagType(std::string);

    /** The physical gamepad functionalities. Some of them might not be available
        for every gamepad type. */
    class GamepadDeviceFunctionsI
    {
    public:
        GamepadDeviceFunctionsI() { };
        virtual ~GamepadDeviceFunctionsI() { };

        virtual void SetLight(Color3) = 0;
    };

    /** The physical gamepad handle to exeute functions */
    class GamepadDeviceHandleI: public GamepadDeviceFunctionsI
    {
    public:
        GamepadDeviceHandleI(): GamepadDeviceFunctionsI() { };
        virtual ~GamepadDeviceHandleI() { };
    };

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

    class EventGamepadThumbstickAxisChanged: public EventI
    {
        Vector2 m_vector;
        GamepadThunbstickAxis m_thumbstick;
    public:
        EventGamepadThumbstickAxisChanged()
            : EventI(EVENT_GAMEPAD_THUMSTICK_AXIS_CHANGE)
            , m_vector(Vector2Zero)
            , m_thumbstick(GAMEPAD_THUMBSTICK_AXIS_LEFT)
        { };

        auto& GetVector() { return m_vector; };
        auto& GetThumbstickType() { return m_thumbstick; };
    };

    class EventGamepadConnectionChanged: public EventI
    {
        GamepadType m_gamepadType;
        GamepadMakeFamily m_gamepadFamily;
        GamepadConnectionStatus m_connectionStatus;
        GamepadDeviceHandleI *m_handle;
    public:
        EventGamepadConnectionChanged(GamepadType gamepadType, GamepadMakeFamily gamepadFamily, GamepadConnectionStatus connectionStatus)
            : EventI(EVENT_GAMEPAD_CONNECTION_CHANGE)
            , m_gamepadType(gamepadType)
            , m_gamepadFamily(gamepadFamily)
            , m_connectionStatus(connectionStatus)
            , m_handle(nullptr)
        { };

        auto& GetGamepadType() { return m_gamepadType; };
        auto& GetGamepadFamily() { return m_gamepadFamily; };
        auto& GetConnectionStatus() { return m_connectionStatus; };
        auto& GetDeviceHandle() { return m_handle; };
    };

    /** Declares an abstract interface to provide real events directly into the
        engine. The platform code should setup its own processing and pass those
        events to the event provider.

        During one frame multiple events can be passed.

        Those events are then converted into internal events and distributed
        further to game scripts.

        There exists a finate queue for each type of pre-declared pool of events
        so that there is little to no overhead of object-creation/deletion.
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

        /** Set left gamepad axis, both axis at the same time. Not queued. */
        virtual void PushLeftThumbstickAxisChange(float, float) = 0;

        /** Set right gamepad axis, both axis at the same time. Not queued. */
        virtual void PushRightThumbstickAxisChange(float, float) = 0;

        /** Set dpad axis, both axis at the same time. Not queued. */
        virtual void PushDpadAxisChange(float, float) = 0;

        /** Push gamepad connection event */
        virtual void PushGamepadConnectionEvent(GamepadType gamepadType, GamepadMakeFamily gamepadFamily, GamepadConnectionStatus connectionStatus, GamepadDeviceHandleI *handle) = 0;

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
