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
#include "interfaces.h"
#include "scripting_engine_provider_interface.h"
#include "gamepad_interface.h"
#include "callable.hpp"
#include "callable_interface.h"
#include "events_manager_interface.h"
#include "defs.h"

#define KEY_TABLE_SIZE 256

namespace engine
{

    /** The base class for all event holder types. Identifier is used to mark
        the event in order to remove it from the event hander list. */
    /** @private */
    template <typename T>
    class EventHolderI: public EventHolderIdentifier
    {
    public:
        EventHolderI(EventIdentifier identifier)
            : EventHolderIdentifier(identifier)
        { };

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
    public:
        EventHolderScript() { };
    };

    /** @private */
    class EventHolderScriptCallableMousePosition: public EventHolderI<Origin>, public EventHolderScript
    {
        CallableScriptFunctionParameters2<float, float> m_script;
    public:
        EventHolderScriptCallableMousePosition(EventIdentifier identifier, CallableScriptFunctionParameters2<float, float> fnc)
            : EventHolderI<Origin>(identifier)
            , EventHolderScript()
            , m_script(fnc)
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
    class EventHolderKeyDown: public EventHolderI<char>, public EventHolderScript
    {
        CallableParameters1<char> m_script;
    public:
        EventHolderKeyDown(EventIdentifier identifier, CallableParameters1<char> fnc)
            : EventHolderI<char>(identifier)
            , EventHolderScript()
            , m_script(fnc)
        { };

        void Process(char*);
    };

    /** Holder for mouse moved event. Provides the position. */
    /** @private */
    class EventHolderMouseMoved: public EventHolderI<Origin>, public EventHolderScript
    {
        typedef std::shared_ptr<CallableParameters1<Origin>> FunctionType;

        FunctionType m_script;
    public:
        EventHolderMouseMoved(EventIdentifier identifier, FunctionType fnc)
            : EventHolderI<Origin>(identifier)
            , EventHolderScript()
            , m_script(fnc)
        { };

        void Process(Origin*);
    };

    /** Gamepad Connection Event Handler */
    class EventHolderGamepadConnection: public EventHolderI<GamepadI*>, public EventHolderScript
    {
        std::shared_ptr<CallableParameters2<GamepadI*, bool>> m_script;
    public:
        EventHolderGamepadConnection(EventIdentifier identifier, std::shared_ptr<CallableParameters2<GamepadI*, bool>> fnc)
            : EventHolderI<GamepadI*>(identifier)
            , EventHolderScript()
            , m_script(fnc)
        { };

        void Process(GamepadI**);
    };

    /** Gamepad Stick Event Handler */
    class EventHolderGamepadStickAxis: public EventHolderI<Vector2>, public EventHolderScript
    {
        CallableParameters1<Vector2> m_script;
    public:
        EventHolderGamepadStickAxis(EventIdentifier identifier, CallableParameters1<Vector2> fnc)
            : EventHolderI<Vector2>(identifier)
            , EventHolderScript()
            , m_script(fnc)
        { };

        void Process(Vector2*);
    };

    /** Gamepad Button Event Holder */
    class EventHolderGamepadButton: public EventHolderI<GamepadButtonActionHolder>, public EventHolderScript
    {
        CallableScriptFunctionParameters3<GamepadButtonType, GamepadButtonAction, float> m_script;
    public:
        EventHolderGamepadButton(EventIdentifier identifier, CallableScriptFunctionParameters3<GamepadButtonType, GamepadButtonAction, float> fnc)
            : EventHolderI<GamepadButtonActionHolder>(identifier)
            , EventHolderScript()
            , m_script(fnc)
        { };

        void Process(GamepadButtonActionHolder*);
    };
};

#endif /* events_manager_types_hpp */
