//
//  events_manager.hpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#ifndef events_manager_hpp
#define events_manager_hpp

#include "event_provider_interface.h"
#include "engine_provider_interface.h"
#include "common_engine_impl.h"
#include "common.h"

#include <iostream>

namespace engine
{
    ///
    ///
    template <class T>
    class EventHolderI
    {
    public:
        EventHolderI() { };

    public:
        virtual void Process(T*) = 0;
    };

    ///
    ///
    template <class T>
    class EventHolderLambda
    {
    public:
        EventHolderLambda(std::function<void(T*)> lambda): m_lambda(lambda) { };
        void Process(T *val) { m_lambda(val); };

    private:
        std::function<void(T*)> m_lambda;
    };

#pragma mark - Designated event holders

    ///
    ///
    class EventHolderMouseMoved: public EventHolderLambda<Origin> {
        using EventHolderLambda::EventHolderLambda;
    };

    ///
    ///
    class EventHolderMouseClicked: public EventHolderLambda<void> {
        using EventHolderLambda::EventHolderLambda;
    };

    ///
    ///
    class EventHolderSDLEvent: public EventHolderLambda<SDL_Event> {
        using EventHolderLambda::EventHolderLambda;
    };

    ///
    ///
    class EventsManager
    {
    public:
        EventsManager(EventProviderI &provider, EngineProviderI &engineProvider): m_eventProvider(provider), m_engineProvider(engineProvider) { };

    /// General events handling
    public:
        /// Returns 1 when quit is expected.
        int DoEvents();

    /// Register for various events
    public:
        void RegisterMouseMovedEvents(EventHolderMouseMoved);
        void RegisterMouseClickedEvents(EventHolderMouseClicked);
        void RegisterGeneralInputEvents(EventHolderSDLEvent);

    private:
        EventProviderI &m_eventProvider;
        EngineProviderI &m_engineProvider;
        std::vector<EventHolderMouseMoved> m_mouseMoves;
        std::vector<EventHolderMouseClicked> m_mouseClicks;
        std::vector<EventHolderSDLEvent> m_generalInput;
    };

};

#endif /* events_manager_hpp */
