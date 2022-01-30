//
//  events_manager_types.hpp
//  Engine
//
//  Created by krzysp on 30/01/2022.
//

#ifndef events_manager_types_hpp
#define events_manager_types_hpp

#include <iostream>
#include "common.h"
#include "event_provider_interface.h"
#include "engine_provider_interface.h"
#include "common_engine_impl.h"
#include "scripting_engine_provider_interface.h"
#include "callable.hpp"
#include "defs.h"

#define KEY_TABLE_SIZE 256

namespace engine
{
    /** Holder identifier
     @private
     */
    typedef unsigned int EventIdentifier;

    /** The base class for all event holder types. Identifier is used to mark
        the event in order to remove it from the event hander list. */
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

    /** The base for all lambda/C++ event handlers
     */
    /** @private */
    template <class T>
    class EventHolderLambda: public EventHolderI<T>
    {
    protected:
        std::function<void(T*)> m_lambda;
    public:
        EventHolderLambda(EventIdentifier identifier, std::function<void(T*)> lambda)
            : EventHolderI<T>(identifier)
            , m_lambda(lambda)
        { };

        void Process(T *val) { m_lambda(val); };
    };

    /** The base for all LUA script event handlers
     */
    /** @private */
    class EventHolderScript
    {
    protected:
        CallableScriptFunctionSciptableInstance m_function;
    public:
        EventHolderScript(CallableScriptFunctionSciptableInstance fnc)
            : m_function(fnc)
        { };
    };

    /** @private */
    class EventHolderScriptCallableMousePosition: public EventHolderI<Origin>, public EventHolderScript
    {
    public:
        EventHolderScriptCallableMousePosition(EventIdentifier identifier, CallableScriptFunctionSciptableInstance fnc)
            : EventHolderI<Origin>(identifier)
            , EventHolderScript(fnc)
        { };

        void Process(Origin *val);
    };

    /** Holder for key combination pressed */
    /** @private */
    class EventHolderKeyShortcutPressed
    {
        std::vector<EventFlagType> m_modifiers;
        std::vector<unsigned short> m_keys;
    public:
        EventHolderKeyShortcutPressed(std::vector<EventFlagType> modifiers, std::vector<unsigned short>keys)
            : m_modifiers(modifiers)
            , m_keys(keys)
        { };

        auto& GetModifiers() { return m_modifiers; };
        auto& GetKeys() { return m_keys; };
        bool Matches(bool shiftDown, bool controlDown, bool keys[KEY_TABLE_SIZE]);
    };

    /** Lambda variation of the EventHolderKeyShortcutPressed */
    class EventHolderKeyShortcutPressedLambda: public EventHolderKeyShortcutPressed, public EventHolderLambda<void>
    {
    public:
        EventHolderKeyShortcutPressedLambda(EventIdentifier identifier, std::function<void(void*)> lambda, std::vector<EventFlagType> modifiers, std::vector<unsigned short>keys)
            : EventHolderKeyShortcutPressed(modifiers, keys)
            , EventHolderLambda<void>(identifier, lambda)
        { };

        void Process(void *val) { m_lambda(nullptr); };
    };

    /** Script variation of the EventHolderKeyShortcutPressed */
    class EventHolderKeyShortcutPressedScript: public EventHolderI<void>, public EventHolderKeyShortcutPressed, public EventHolderScript
    {
    public:
        EventHolderKeyShortcutPressedScript(EventIdentifier identifier, CallableScriptFunctionSciptableInstance fnc, std::vector<EventFlagType> modifiers, std::vector<unsigned short>keys)
            : EventHolderI<void>(identifier)
            , EventHolderKeyShortcutPressed(modifiers, keys)
            , EventHolderScript(fnc)
        { };

        void Process(void *val);
    };
};

#endif /* events_manager_types_hpp */
