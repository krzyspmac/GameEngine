// Copyright (c) 2022 Krzysztof Pawłowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

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
