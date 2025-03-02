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

#ifndef events_manager_hpp
#define events_manager_hpp

#include <iostream>
#include "common.h"
#include "event_provider_interface.h"
#include "engine_provider_interface.h"
#include "interfaces.h"
#include "events_manager_types.hpp"
#include "object_pool.hpp"
#include "gamepad_interface.h"
#include "events_manager_interface.h"

namespace engine
{
    class EventsManager: public EventsManagerI
    {
    public:
        /** The main constructor.
         @private */
        EventsManager(EventProviderI &provider, EngineProviderI &engineProvider);

    public: // EventsManagerI
        int DoEvents();

        EventIdentifier RegisterMouseMovedEvents(std::shared_ptr<CallableParameters1<Origin>>);
        EventIdentifier RegisterMouseClickedEvents(std::shared_ptr<CallableParameters1<Origin>>);
        EventIdentifier RegisterKeyShortcut(std::vector<EventFlagType> modifiers, std::vector<unsigned short>keys, std::shared_ptr<CallableParametersEmpty> fnc);
        EventIdentifier RegisterKeyDown(std::shared_ptr<CallableParameters1<char>>);
        EventIdentifier RegisterKeyUp(std::shared_ptr<CallableParameters1<char>>);
        EventIdentifier RegisterGamepadConnection(std::shared_ptr<CallableParameters2<GamepadI*, bool>>);
        bool IsShiftDown() { return m_shiftKeyDown; };
        bool IsControlDown() { return m_controlKeyDown; };
        bool GetKeyDown(unsigned short key) { return m_keys[key]; };
        void UnregisterEvent(EventIdentifier);
        void Unregister(EventHolderIdentifier*);
        void UnregisterAllEvents();

    public: // other

        auto& GetGamepads() { return m_gamepads; };

    public:
        /** @private */
        bool* GetKeys() { return m_keys; };

    private:
        EventIdentifier m_identifierCounter;
        EventProviderI &m_eventProvider;
        EngineProviderI &m_engineProvider;
        std::vector<EventHolderMouseMoved> m_mouseMoves;
        std::vector<EventHolderMouseClicked> m_mouseClicks;
        std::vector<EventHolderKeyShortcut> m_keyShortcuts;
        std::vector<EventHolderKeyDown> m_keyDowns;
        std::vector<EventHolderKeyDown> m_keyUps;
        std::vector<EventHolderGamepadConnection> m_gamepadConnection;
        std::vector<std::unique_ptr<GamepadI>> m_gamepads;
        bool m_shiftKeyDown;
        bool m_controlKeyDown;
        bool m_keys[KEY_TABLE_SIZE];
        char m_keysWrapper[2];
    };
};

#endif /* events_manager_hpp */
