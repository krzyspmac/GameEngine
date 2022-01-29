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

#define KEY_TABLE_SIZE 256

namespace engine
{
    /***/
    template <class T>
    class EventHolderI
    {
    public:
        EventHolderI() { };

    public:
        virtual void Process(T*) = 0;
    };

    /***/
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

    /** Holder for mouse moved event. Provides the position. */
    class EventHolderMouseMoved: public EventHolderLambda<Origin> {
        using EventHolderLambda::EventHolderLambda;
    };

    /** Holder for mouse clicked event. */
    class EventHolderMouseClicked: public EventHolderLambda<void> {
        using EventHolderLambda::EventHolderLambda;
    };

    /** Holder for key combination pressed */
    class EventHolderKeyShortcutPressed: public EventHolderLambda<void> {
        using EventHolderLambda::EventHolderLambda;
        std::vector<EventFlagType> m_modifiers;
        std::vector<unsigned short> m_keys;
    public:
        EventHolderKeyShortcutPressed(std::function<void(void*)> lambda, std::vector<EventFlagType> modifiers, std::vector<unsigned short>keys)
            : EventHolderLambda<void>(lambda)
            , m_modifiers(modifiers)
            , m_keys(keys)
        { };

        auto& GetModifiers() { return m_modifiers; };
        auto& GetKeys() { return m_keys; };
        bool Matches(bool shiftDown, bool controlDown, bool keys[KEY_TABLE_SIZE]);
    };

    /***/
    class EventsManager
    {
    public:
        EventsManager(EventProviderI &provider, EngineProviderI &engineProvider);

    public: /** General events handling */
        /// Returns 1 when quit is expected.
        int DoEvents();

    public: /** Register for various events */
        void RegisterMouseMovedEvents(EventHolderMouseMoved);
        void RegisterMouseClickedEvents(EventHolderMouseClicked);
        void RegisterKeyShortcut(std::vector<EventFlagType> modifiers, std::vector<unsigned short>keys, std::function<void(void*)> lambda);

    public: /** Public getters */
        bool IsShiftDown() { return m_shiftKeyDown; };
        bool IsControlDown() { return m_controlKeyDown; };
        auto& GetKeys() { return m_keys; };
        bool GetKeyDown(unsigned short key) { return m_keys[key]; };

    private: /** Variables */
        EventProviderI &m_eventProvider;
        EngineProviderI &m_engineProvider;
        std::vector<EventHolderMouseMoved> m_mouseMoves;
        std::vector<EventHolderMouseClicked> m_mouseClicks;
        std::vector<EventHolderKeyShortcutPressed> m_keyshortcuts;

        bool m_shiftKeyDown;
        bool m_controlKeyDown;
        bool m_keys[KEY_TABLE_SIZE];
    };
};

#endif /* events_manager_hpp */
