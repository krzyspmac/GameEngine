//
//  events_manager_interface.h
//  Engine
//
//  Created by krzysp on 28/09/2022.
//

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

    /** EventsManager
        \addtogroup API_GLOBALS
        Allows for registering for keyboard & mouse events
     */
    class EventsManagerI
    {
    public:

        /** Returns 1 when quit is expected. */
        virtual int DoEvents() = 0;

        /** Register a mouse move events for C++. */
        virtual EventIdentifier RegisterMouseMovedEvents(std::shared_ptr<CallableParameters1<Origin>>) = 0;

        /** Register for gamepad connection/disconnection */
        virtual EventIdentifier RegisterGamepadConnection(std::shared_ptr<CallableParameters2<GamepadI*, bool>>) = 0;

        /** Unregister a callback */
        virtual void UnregisterEvent(EventIdentifier) = 0;
    };
};

#endif /* events_manager_interface_h */
