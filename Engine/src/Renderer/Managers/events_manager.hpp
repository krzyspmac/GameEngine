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
    class EventsManager
    {
    public:
        EventsManager(EventProviderI &provider, EngineProviderI &engineProvider);

    /// General events handling
    public:
        /// Returns 1 when quit is expected.
        int DoEvents();

    /// Register for various events
    public:
        void RegisterMouseMovedEvents(EventHolderMouseMoved);
        void RegisterMouseClickedEvents(EventHolderMouseClicked);

    /// Public getters
    public:
        bool IsShiftDown() { return m_shiftKeyDown; };
        bool IsControlDown() { return m_controlKeyDown; };
        auto& GetKeys() { return m_keys; };
        bool GetKeyDown(unsigned short key) { return m_keys[key]; };

    private:
        EventProviderI &m_eventProvider;
        EngineProviderI &m_engineProvider;
        std::vector<EventHolderMouseMoved> m_mouseMoves;
        std::vector<EventHolderMouseClicked> m_mouseClicks;

        bool m_shiftKeyDown;
        bool m_controlKeyDown;
        bool m_keys[256];
    };

};

#endif /* events_manager_hpp */
