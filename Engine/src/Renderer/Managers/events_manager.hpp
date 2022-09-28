//
//  events_manager.hpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#ifndef events_manager_hpp
#define events_manager_hpp

#include <iostream>
#include "common.h"
#include "event_provider_interface.h"
#include "engine_provider_interface.h"
#include "interfaces.h"
#include "scripting_engine_provider_interface.h"
#include "callable.hpp"
#include "events_manager_types.hpp"
#include "object_pool.hpp"
#include "gamepad_interface.h"
#include "events_manager_interface.h"

namespace engine
{
    /** Holder for mouse moved events for scripting. Provides the position. */
    /** @private */
    class EventHolderMouseMovedScript: public EventHolderScriptCallableMousePosition
    {
        using EventHolderScriptCallableMousePosition::EventHolderScriptCallableMousePosition;
    };

    /** Holder for key shortcut for C++ */
    /** @private */
    class EventHolderKeyShortcutLambda: public EventHolderKeyShortcutPressedLambda
    {
        using EventHolderKeyShortcutPressedLambda::EventHolderKeyShortcutPressedLambda;
    };

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
        
        EventIdentifier RegisterGamepadConnection(std::shared_ptr<CallableParameters2<GamepadI*, bool>>);

    public: // other
        /** Register a key combination for C++.
            @private */
        EventIdentifier RegisterKeyShortcut(std::vector<EventFlagType> modifiers, std::vector<unsigned short>keys, std::function<void(void*)> lambda);

        /** Register a key combination for scripting.

            \code{lua}
            EventsManager:RegisterKeyShortcutsEvents("shift|control", "w|t", function()
                print("shift & control & w & t pressed simulataneously")
            end)
            \endcode
         */
        EventIdentifier RegisterKeyShortcut(std::vector<EventFlagType> modifiers, std::vector<unsigned short>keys, CallableScriptFunctionParametersEmpty);

        /** Register any key down event */
        EventIdentifier RegisterKeyDown(CallableScriptFunctionParameters1<char>);

        EventIdentifier RegisterKeyUp(CallableScriptFunctionParameters1<char>);

        /** Retrieve the gamepads */
        auto& GetGamepads() { return m_gamepads; };

        /** Unregisters an event for a given identifier. */
        void UnregisterEvent(EventIdentifier);

        void Unregister(EventHolderIdentifier*);

        /** @private */
        void UnregisterAllEvents();

    public: /** Public getters */

        /** Checkf for the shift modifier */
        bool IsShiftDown() { return m_shiftKeyDown; };

        /** Checks for the control modifier */
        bool IsControlDown() { return m_controlKeyDown; };

        /** @private */
        auto& GetKeys() { return m_keys; };

        /** @private */
        bool GetKeyDown(unsigned short key) { return m_keys[key]; };

    private: /** scripting */
        /** @private */
        SCRIPTING_INTERFACE_HEADERS(EventsManager);

    private: /** Variables */
        EventIdentifier m_identifierCounter;
        EventProviderI &m_eventProvider;
        EngineProviderI &m_engineProvider;
        std::vector<EventHolderMouseMoved> m_mouseMoves;
        std::vector<EventHolderMouseClicked> m_mouseClicks;
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
