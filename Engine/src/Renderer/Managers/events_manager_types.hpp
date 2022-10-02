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

#ifndef events_manager_types_hpp
#define events_manager_types_hpp

#include <iostream>
#include "common.h"
#include "event_provider_interface.h"
#include "engine_provider_interface.h"
#include "interfaces.h"
#include "gamepad_interface.h"
#include "callable_interface.h"
#include "events_manager_interface.h"
#include "defs.h"

#define KEY_TABLE_SIZE 256

namespace engine
{

    /** The base class for all event holder types. Identifier is used to mark
        the event in order to remove it from the event hander list. */
    /** @private */
    template <typename T>
    class EventHolderI: public EventHolderIdentifier
    {
    public:
        EventHolderI(EventIdentifier identifier)
            : EventHolderIdentifier(identifier)
        { };

    public:
        virtual void Process(T*) = 0;
    };

    /** The base for all LUA script event handlers
     */
    /** @private */
    class EventHolderScript
    {
    public:
        EventHolderScript() { };
    };

    /** Void Handler */
    class EventHolderVoid: public EventHolderI<void>, public EventHolderScript
    {
        std::shared_ptr<CallableParametersEmpty> m_script;
    public:
        EventHolderVoid(EventIdentifier identifier, std::shared_ptr<CallableParametersEmpty> fnc)
            : EventHolderI<void>(identifier)
            , EventHolderScript()
            , m_script(fnc)
        { };

        void Process(void*);
    };

    /** Script variation of the EventHolderKeyShortcutPressed */
    class EventHolderKeyDown: public EventHolderI<char>, public EventHolderScript
    {
        typedef std::shared_ptr<CallableParameters1<char>> FunctionType;
        FunctionType m_script;
    public:
        EventHolderKeyDown(EventIdentifier identifier, FunctionType fnc)
            : EventHolderI<char>(identifier)
            , EventHolderScript()
            , m_script(fnc)
        { };

        void Process(char*);
    };

    /** Holder for mouse moved event. Provides the position. */
    /** @private */
    class EventHolderMouseMoved: public EventHolderI<Origin>, public EventHolderScript
    {
        typedef std::shared_ptr<CallableParameters1<Origin>> FunctionType;

        FunctionType m_script;
    public:
        EventHolderMouseMoved(EventIdentifier identifier, FunctionType fnc)
            : EventHolderI<Origin>(identifier)
            , EventHolderScript()
            , m_script(fnc)
        { };

        void Process(Origin*);
    };

    /** Holder for mouse clicked event. */
    /** @private */
    class EventHolderMouseClicked: public EventHolderMouseMoved
    {
        using EventHolderMouseMoved::EventHolderMouseMoved;
    };

    typedef std::vector<EventFlagType>  EventHolderKeyShortcutFlagsList;
    typedef std::vector<unsigned short> EventHolderKeyShortcutKeyList;

    /** Gamepad Connection Event Handler */
    class EventHolderKeyShortcut: public EventHolderI<void>, public EventHolderScript
    {
        EventHolderKeyShortcutFlagsList m_flags;
        EventHolderKeyShortcutKeyList m_keys;
        std::shared_ptr<CallableParametersEmpty> m_script;
    public:
        EventHolderKeyShortcut(EventIdentifier identifier, EventHolderKeyShortcutFlagsList flags, EventHolderKeyShortcutKeyList keys, std::shared_ptr<CallableParametersEmpty> fnc)
            : EventHolderI<void>(identifier)
            , EventHolderScript()
            , m_script(fnc)
            , m_flags(flags)
            , m_keys(keys)
        { };

        bool Matches(bool shiftDown, bool controlDown, bool keys[KEY_TABLE_SIZE]);
        void Process(void*);
    };

    /** Gamepad Connection Event Handler */
    class EventHolderGamepadConnection: public EventHolderI<GamepadI*>, public EventHolderScript
    {
        std::shared_ptr<CallableParameters2<GamepadI*, bool>> m_script;
    public:
        EventHolderGamepadConnection(EventIdentifier identifier, std::shared_ptr<CallableParameters2<GamepadI*, bool>> fnc)
            : EventHolderI<GamepadI*>(identifier)
            , EventHolderScript()
            , m_script(fnc)
        { };

        void Process(GamepadI**);
    };

    /** Gamepad Stick Event Handler */
    class EventHolderGamepadStickAxis: public EventHolderI<Vector2>, public EventHolderScript
    {
        std::shared_ptr<CallableParameters1<Vector2>> m_script;
    public:
        EventHolderGamepadStickAxis(EventIdentifier identifier, std::shared_ptr<CallableParameters1<Vector2>> fnc)
            : EventHolderI<Vector2>(identifier)
            , EventHolderScript()
            , m_script(fnc)
        { };

        void Process(Vector2*);
    };

    /** Gamepad Button Event Holder */
    class EventHolderGamepadButton: public EventHolderI<GamepadButtonActionHolder>, public EventHolderScript
    {
        std::shared_ptr<CallableParameters3<GamepadButtonType, GamepadButtonAction, float>> m_script;
    public:
        EventHolderGamepadButton(EventIdentifier identifier, std::shared_ptr<CallableParameters3<GamepadButtonType, GamepadButtonAction, float>> fnc)
            : EventHolderI<GamepadButtonActionHolder>(identifier)
            , EventHolderScript()
            , m_script(fnc)
        { };

        void Process(GamepadButtonActionHolder*);
    };
};

#endif /* events_manager_types_hpp */
