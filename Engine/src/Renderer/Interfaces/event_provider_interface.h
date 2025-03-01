// Copyright (c) 2022 Krzysztof Pawłowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef event_provider_interface_h
#define event_provider_interface_h

#include "common.h"
#include "size.hpp"
#include "vector2.hpp"

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
      , EVENT_GAMEPAD_BUTTON_ACTION_CHANGE
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

    /**
     All face buttons are required to be analog in the Extended profile. These must be arranged
     in the diamond pattern given below:

       Y
      / \
     X   B
      \ /
       A

     */
    typedef enum
    {
        GAMEPAD_BUTTON_A                     = 0
      , GAMEPAD_BUTTON_B                     = 1
      , GAMEPAD_BUTTON_X                     = 2
      , GAMEPAD_BUTTON_Y                     = 3
      , GAMEPAD_BUTTON_MENU                  = 4
      , GAMEPAD_BUTTON_OPTIONS               = 5
      , GAMEPAD_BUTTON_LEFT_TRIGGER          = 6
      , GAMEPAD_BUTTON_LEFT_SHOULDER         = 7
      , GAMEPAD_BUTTON_RIGHT_TRIGGER         = 8
      , GAMEPAD_BUTTON_RIGHT_SHOULDER        = 9
      , GAMEPAD_BUTTON_LEFT_THUMBSTICK_BTN   = 10
      , GAMEPAD_BUTTON_RIGHT_THUMBSTICK_BTN  = 11
    } GamepadButtonType;

    typedef enum
    {
        GAMEPAD_BUTTON_ACTION_PRESSED = 0,
        GAMEPAD_BUTTON_ACTION_DEPRESSED = 1,
    } GamepadButtonAction;

    typedef struct GamepadButtonActionHolder
    {
        /** button type */
        GamepadButtonType button;

        /** button action, pressed, depressed, etc. */
        GamepadButtonAction action;

        /** button value, for certain buttons this can be between 0.0 and 1.0*/
        float value;

        GamepadButtonActionHolder(GamepadButtonType button, GamepadButtonAction action, float value)
        {
            this->button = button;
            this->action = action;
            this->value = value;
        }
    } GamepadButtonActionHolder;

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

    class EventGamepadButtonEventChanged: public EventI
    {
        GamepadButtonActionHolder m_action;
    public:
        EventGamepadButtonEventChanged()
            : EventI(EVENT_GAMEPAD_BUTTON_ACTION_CHANGE)
            , m_action(GamepadButtonActionHolder(GAMEPAD_BUTTON_A, GAMEPAD_BUTTON_ACTION_PRESSED, 0.0f))
        { };

        auto& GetAction() { return m_action; };
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

        /** Push button action */
        virtual void PushButtonAction(GamepadButtonActionHolder) = 0;

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
