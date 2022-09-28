//
//  events_manager_types.cpp
//  Engine
//
//  Created by krzysp on 30/01/2022.
//

#include "events_manager_types.hpp"
#include "gamepad.hpp"

using namespace engine;

bool EventHolderKeyShortcut::Matches(bool shiftDown, bool controlDown, bool keys[KEY_TABLE_SIZE])
{
    for (auto& modifier : m_flags)
    {
        if (modifier == FLAG_SHIFT)
        {
            if (!shiftDown)
            {
                return false;
            }
        }
        else if (modifier == FLAG_CONTROL)
        {
            if (!controlDown)
            {
                return false;
            }
        }
    }

    for (auto& key : m_keys)
    {
        if (keys[key] != true)
        {
            return false;
        }
    }

    return true;
}

void EventHolderKeyShortcut::Process(void*)
{
    if (m_script->CanCall())
    {
        auto fnc = m_script.get();
        fnc->Call();
    }
}

void EventHolderVoid::Process(void*)
{
    if (m_script->CanCall())
    {
        auto fnc = m_script.get();
        fnc->Call();
    }
}

void EventHolderMouseMoved::Process(Origin *obj)
{
    if (m_script->CanCall())
    {
        auto fnc = m_script.get();
        fnc->Call(*obj);
    }
}

void EventHolderKeyDown::Process(char *c)
{
    if (m_script->CanCall())
    {
        auto fnc = m_script.get();
        fnc->Call(*c);
    }
}

void EventHolderGamepadStickAxis::Process(Vector2 *vector)
{
    if (m_script == nullptr) { return; }
    if (m_script.get() == nullptr) { return; }

    if (m_script->CanCall())
    {
        m_script->Call(*vector);
    }
}

void EventHolderGamepadConnection::Process(GamepadI **_gamepad)
{
    if (m_script == nullptr) { return; }

    if (m_script.get() != nullptr)
    {
        if (_gamepad != nullptr)
        {
            GamepadI* gamepad = *_gamepad;
            auto fnc = m_script.get();
            fnc->Call(gamepad, true);
        }
        else
        {
            auto fnc = m_script.get();
            fnc->Call(nullptr, false);
        }
    }
}

void EventHolderGamepadButton::Process(GamepadButtonActionHolder *descriptor)
{
    if (m_script == nullptr) { return; }
    if (m_script.get() == nullptr) { return; }

    if (m_script->CanCall())
    {
        m_script->Call(descriptor->button, descriptor->action, descriptor->value);
    }
}
