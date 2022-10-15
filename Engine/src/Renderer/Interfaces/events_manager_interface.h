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

#ifndef events_manager_interface_h
#define events_manager_interface_h

#include "callable_interface.h"
#include "gamepad_interface.h"

namespace engine
{
    /** Holder identifier */
    typedef unsigned int EventIdentifier;

    /** The base for all event holders */
    class EventHolderIdentifier
    {
        EventIdentifier m_identifier;
    public:
        EventHolderIdentifier(EventIdentifier identifier) : m_identifier(identifier) { };

        auto GetIdentifier() { return m_identifier; };
    };

    /** EventsManagerI
        \addtogroup API_GLOBALS

        Allows for registering for keyboard, mouse events & gamepad events.
     */
    class EventsManagerI
    {
    public:

        /** Returns 1 when quit is expected. */
        virtual int DoEvents() = 0;

        /** Checks for the control modifier */
        virtual bool IsShiftDown() = 0;

        /** Checks for the control modifier */
        virtual bool IsControlDown() = 0;

        /** Checks the status of a key */
        virtual bool GetKeyDown(unsigned short key) = 0;

        /** Register a mouse move events event handler */
        virtual EventIdentifier RegisterMouseMovedEvents(std::shared_ptr<CallableParameters1<Origin>>) = 0;

        /** Register a mouse click event handler */
        virtual EventIdentifier RegisterMouseClickedEvents(std::shared_ptr<CallableParameters1<Origin>>) = 0;

        /** Register key shortcut */
        virtual EventIdentifier RegisterKeyShortcut(std::vector<EventFlagType> modifiers, std::vector<unsigned short>keys, std::shared_ptr<CallableParametersEmpty> fnc) = 0;

        /** Register a key down event handler */
        virtual EventIdentifier RegisterKeyDown(std::shared_ptr<CallableParameters1<char>>) = 0;

        /** Register a key up event handler */
        virtual EventIdentifier RegisterKeyUp(std::shared_ptr<CallableParameters1<char>>) = 0;

        /** Register for gamepad connection/disconnection */
        virtual EventIdentifier RegisterGamepadConnection(std::shared_ptr<CallableParameters2<GamepadI*, bool>>) = 0;

        /** Returns the adress to the static list of keys. bool[KEY_TABLE_SIZE]. True for the key being pressed. */
        virtual bool *GetKeys() = 0;

        /** Unregister a callback */
        virtual void UnregisterEvent(EventIdentifier) = 0;

        /** Unregister a callback */
        virtual void Unregister(EventHolderIdentifier*) = 0;

        /** Unregister all events */
        virtual void UnregisterAllEvents() = 0;
    };
};

#endif /* events_manager_interface_h */
