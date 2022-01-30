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

#define KEY_TABLE_SIZE 256

namespace engine
{
    /** Holder identifier
     @private
     */
    typedef unsigned int EventIdentifier;

    /** @private */
    template <class T>
    class EventHolderI
    {
        EventIdentifier m_identifier;
    public:
        EventHolderI(EventIdentifier identifier)
            : m_identifier(identifier)
        { };
        
        auto GetIdentifier() { return m_identifier; };

    public:
        virtual void Process(T*) = 0;
    };

    /** @private */
    template <class T>
    class EventHolderLambda: public EventHolderI<T>
    {
        std::function<void(T*)> m_lambda;
    public:
        EventHolderLambda(EventIdentifier identifier, std::function<void(T*)> lambda)
            : EventHolderI<T>(identifier)
            , m_lambda(lambda)
        { };

        void Process(T *val) { m_lambda(val); };
    };

    /** @private */
    class EventHolderScriptCallableMousePosition: public EventHolderI<Origin>
    {
        CallableScriptFunctionSciptableInstance m_function;
    public:
        EventHolderScriptCallableMousePosition(EventIdentifier identifier, CallableScriptFunctionSciptableInstance fnc)
            : EventHolderI<Origin>(identifier)
            , m_function(fnc)
        { };

        void Process(Origin *val);
    };

#pragma mark - Designated event holders

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

    /** Holder for key combination pressed */
    /** @private */
    class EventHolderKeyShortcutPressed: public EventHolderLambda<void>
    {
        using EventHolderLambda::EventHolderLambda;
        std::vector<EventFlagType> m_modifiers;
        std::vector<unsigned short> m_keys;
    public:
        EventHolderKeyShortcutPressed(EventIdentifier identifier, std::function<void(void*)> lambda, std::vector<EventFlagType> modifiers, std::vector<unsigned short>keys)
            : EventHolderLambda<void>(identifier, lambda)
            , m_modifiers(modifiers)
            , m_keys(keys)
        { };

        auto& GetModifiers() { return m_modifiers; };
        auto& GetKeys() { return m_keys; };
        bool Matches(bool shiftDown, bool controlDown, bool keys[KEY_TABLE_SIZE]);
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
        EventIdentifier RegisterMouseMovedEvents(CallableScriptFunctionSciptableInstance);

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
        EventIdentifier RegisterMouseClickedEvents(CallableScriptFunctionSciptableInstance);

        /** Register a key combination for C++.
            @private */
        EventIdentifier RegisterKeyShortcut(std::vector<EventFlagType> modifiers, std::vector<unsigned short>keys, std::function<void(void*)> lambda);

        /** @private */
        void UnregisterEvent(EventIdentifier);

        /** @private */
        void UnregisterAllEvents();

    public: /** Public getters */
        bool IsShiftDown() { return m_shiftKeyDown; };
        bool IsControlDown() { return m_controlKeyDown; };
        auto& GetKeys() { return m_keys; };
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
        std::vector<EventHolderKeyShortcutPressed> m_keyshortcuts;

        bool m_shiftKeyDown;
        bool m_controlKeyDown;
        bool m_keys[KEY_TABLE_SIZE];
    };
};

#endif /* events_manager_hpp */
