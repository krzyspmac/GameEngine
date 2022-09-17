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
#include "common_engine_impl.h"
#include "scripting_engine_provider_interface.h"
#include "callable.hpp"
#include "events_manager_types.hpp"
#include "object_pool.hpp"
#include "gamepad_interface.h"

namespace engine
{
    /** Holder for mouse moved event. Provides the position. */
    /** @private */
    class EventHolderMouseMoved: public EventHolderLambda<Origin>
    {
        using EventHolderLambda::EventHolderLambda;
    };

    /** Holder for mouse moved events for scripting. Provides the position. */
    /** @private */
    class EventHolderMouseMovedScript: public EventHolderScriptCallableMousePosition
    {
        using EventHolderScriptCallableMousePosition::EventHolderScriptCallableMousePosition;
    };

    /** Holder for mouse clicked events for scripting. Provides the position. */
    /** @private */
    class EventHolderMouseClickedScript: public EventHolderScriptCallableMousePosition
    {
        using EventHolderScriptCallableMousePosition::EventHolderScriptCallableMousePosition;
    };

    /** Holder for mouse clicked event. */
    /** @private */
    class EventHolderMouseClicked: public EventHolderLambda<void>
    {
        using EventHolderLambda::EventHolderLambda;
    };

    /** Holder for key shortcut for C++ */
    /** @private */
    class EventHolderKeyShortcutLambda: public EventHolderKeyShortcutPressedLambda
    {
        using EventHolderKeyShortcutPressedLambda::EventHolderKeyShortcutPressedLambda;
    };

    /**
     EventsManager
     \addtogroup API_GLOBALS
     */
    /** Allows for registering for keyboard & mouse events
     */
    class EventsManager
    {
    public:
        /** The main constructor.
         @private */
        EventsManager(EventProviderI &provider, EngineProviderI &engineProvider);

    public: /** General events handling */
        /** Returns 1 when quit is expected.
            @private */
        int DoEvents();

    public: /** Register for various events */
        /** Register a mouse move events for C++.
            @private */
        EventIdentifier RegisterMouseMovedEvents(std::function<void(Origin*)> lambda);

        /** Register a mouse move event handler for scripting.
            The script will get the x and y position in viewport coordinates.

            \code{lua}
            EventsManager:RegisterMouseMovedEvents(function(x, y)
                print("Mouse position = " .. x .. ", " .. y)
            end)
            \endcode
         */
        EventIdentifier RegisterMouseMovedEvents(CallableScriptFunctionParameters2<float, float>);

        /** Register a mouse click event handler for C++.
            @private */
        EventIdentifier RegisterMouseClickedEvents(std::function<void(void*)> lambda);

        /** Register a mouse click event handler for scripting.

            \code{lua}
            EventsManager:RegisterMouseClickedEvents(function(x, y)
                print("Mouse click position = " .. x .. ", " .. y)
            end)
            \endcode
            */
        EventIdentifier RegisterMouseClickedEvents(CallableScriptFunctionParameters2<float, float>);

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

        /** Register a left thumbstick axis change. If not avilable will not get called

            \code{lua}
             EventsManager:RegisterLeftThumbstickAxis(function(x, y)
                 -- process, like: self.vector:set(x, y)
             end)
            \endcode
         */
        EventIdentifier RegisterLeftThumbstickAxis(CallableScriptFunctionParameters1<Vector2>);


        /** Register a right thumbstick axis change. If not avilable will not get called

            \code{lua}
             EventsManager:RegisterRightThumbstickAxis(function(x, y)
                 -- process, like: self.vector:set(x, y)
             end)
            \endcode
         */
        EventIdentifier RegisterRightThumbstickAxis(CallableScriptFunctionParameters1<Vector2>);

        /** Register for gamepad connection/disconnection */
        EventIdentifier RegisterGamepadConnection(CallableScriptFunctionParameters2<GamepadI, bool>);

        /** Retrieve the gamepads */
        auto& GetGamepads() { return m_gamepads; };

        /** Unregisters an event for a given identifier. */
        void UnregisterEvent(EventIdentifier);

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
        std::vector<EventHolderMouseMovedScript> m_mouseMovesScript;
        std::vector<EventHolderMouseClicked> m_mouseClicks;
        std::vector<EventHolderMouseClickedScript> m_mouseClickedScript;
        std::vector<EventHolderKeyShortcutLambda> m_keyshortcuts;
        std::vector<EventHolderKeyShortcutPressedScript> m_keyshortcutsScript;
        std::vector<EventHolderKeyDown> m_keyDowns;
        std::vector<EventHolderKeyDown> m_keyUps;
        std::vector<EventHolderGamepadStickAxis> m_leftStickAxisChange;
        std::vector<EventHolderGamepadStickAxis> m_rightStickAxisChange;
        std::vector<EventHolderGamepadConnection> m_gamepadConnection;
        std::vector<std::unique_ptr<GamepadI>> m_gamepads;
        bool m_shiftKeyDown;
        bool m_controlKeyDown;
        bool m_keys[KEY_TABLE_SIZE];
        char m_keysWrapper[2];
    };
};

#endif /* events_manager_hpp */
