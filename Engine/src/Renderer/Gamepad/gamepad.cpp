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

#include "gamepad.hpp"
#include "engine.hpp"

using namespace engine;

Gamepad::~Gamepad()
{
}

template<typename S>
static void TemplateRemoveIfMatching(std::vector<S> &handlers, GamepadEventIdentifier identifier)
{
    for (auto it = handlers.begin(); it != handlers.end(); it++)
    {
        if ((*it).GetIdentifier() == identifier)
        {
            handlers.erase(it);
            return;
        }
    }
}

void Gamepad::ProcessEvent(EventGamepadThumbstickAxisChanged* event)
{
    auto& vector = event->GetVector();

    switch (event->GetThumbstickType())
    {
        case GAMEPAD_THUMBSTICK_AXIS_LEFT:
        {
            for (auto& codeHandler : m_leftStickAxisChange)
            {
                codeHandler.Process(&vector);
            }
            break;
        }
        case GAMEPAD_THUMBSTICK_AXIS_RIGHT:
        {
            for (auto& codeHandler : m_rightStickAxisChange)
            {
                codeHandler.Process(&vector);
            }
            break;
        }
        case GAMEPAD_DPAD:
        {
            for (auto& codeHandler : m_dpadAxisChange)
            {
                codeHandler.Process(&vector);
            }
            break;
        }
    }
}

void Gamepad::ProcessButtonEvent(GamepadButtonActionHolder *action)
{
    for (auto& codeHandler : m_buttonChange)
    {
        codeHandler.Process(action);
    }
}

void Gamepad::UnregisterEvent(GamepadEventIdentifier identifier)
{
    TemplateRemoveIfMatching<EventHolderGamepadStickAxis>(m_leftStickAxisChange, identifier);
    TemplateRemoveIfMatching<EventHolderGamepadStickAxis>(m_rightStickAxisChange, identifier);
    TemplateRemoveIfMatching<EventHolderGamepadStickAxis>(m_dpadAxisChange, identifier);
}

void Gamepad::UnregisterAllEvents()
{
    m_leftStickAxisChange.clear();
    m_rightStickAxisChange.clear();
    m_dpadAxisChange.clear();
    m_buttonChange.clear();
}

GamepadEventIdentifier Gamepad::RegisterLeftThumbstickAxis(std::shared_ptr<CallableParameters1<Vector2>> fnc)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_leftStickAxisChange.push_back(EventHolderGamepadStickAxis(identifier, fnc));
    return identifier;
}

GamepadEventIdentifier Gamepad::RegisterRightThumbstickAxis(std::shared_ptr<CallableParameters1<Vector2>> fnc)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_rightStickAxisChange.push_back(EventHolderGamepadStickAxis(identifier, fnc));
    return identifier;
}

GamepadEventIdentifier Gamepad::RegisterDpadAxis(std::shared_ptr<CallableParameters1<Vector2>> fnc)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_dpadAxisChange.push_back(EventHolderGamepadStickAxis(identifier, fnc));
    return identifier;
}

GamepadEventIdentifier Gamepad::RegisterButtonTapped(std::shared_ptr<CallableParameters3<GamepadButtonType, GamepadButtonAction, float>> fnc)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_buttonChange.push_back(EventHolderGamepadButton(identifier, fnc));
    return identifier;
}

void Gamepad::SetLight(Color3 color)
{
    if (m_handle != nullptr)
    {   m_handle->SetLight(color);
    }
}
