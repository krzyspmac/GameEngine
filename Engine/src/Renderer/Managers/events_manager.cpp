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

#include "events_manager.hpp"
#include "engine.hpp"
#include "gamepad.hpp"

using namespace engine;

EventsManager::EventsManager(EventProviderI &provider, EngineProviderI &engineProvider)
    : m_eventProvider(provider)
    , m_identifierCounter(0)
    , m_engineProvider(engineProvider)
    , m_shiftKeyDown(false)
    , m_controlKeyDown(false)
{
    bzero(m_keys, KEY_TABLE_SIZE);
    m_keysWrapper[0] = '\0';
    m_keysWrapper[1] = '\0';
}

int EventsManager::DoEvents()
{
    EventI *baseEvent = nullptr;

    while (m_eventProvider.PollEvent(&baseEvent))
    {
        switch (baseEvent->GetType())
        {
            case EVENT_NONE:
            {
                break;
            }
            case EVENT_KEY_FLAG_STATE_CHANGE:
            {
                auto* event = static_cast<EventKeyFlagStateChanged*>(baseEvent);
                switch (event->GetFlagType())
                {
                    case FLAG_SHIFT:
                    {
                        m_shiftKeyDown = event->GetState();
                        break;
                    }
                    case FLAG_CONTROL:
                    {
                        m_controlKeyDown = event->GetState();
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
                break;
            }
            case EVENT_KEY_STATE_CHANGE:
            {
                auto* event = static_cast<EventKeyStateChanged*>(baseEvent);
                auto& key = event->GetKey();
                auto& isDown = event->GetIsDown();

                m_keys[key] = isDown;
                m_keysWrapper[0] = key;

                if (isDown)
                {
                    for (auto& keyHandler : m_keyDowns)
                    {
                        keyHandler.Process(m_keysWrapper);
                    }
                }
                else
                {
                    for (auto& keyHandler : m_keyUps)
                    {
                        keyHandler.Process(m_keysWrapper);
                    }
                }

                for (auto& keyHandler : m_keyShortcuts)
                {
                    if (keyHandler.Matches(m_shiftKeyDown, m_controlKeyDown, m_keys))
                    {
                        keyHandler.Process(nullptr);
                    }
                }
                break;
            }
            case EVENT_MOUSEMOVE:
            {
                auto mouseEvent = static_cast<EventMouseMove*>(baseEvent);
                auto mouseLocation = &mouseEvent->GetLocation();

                for (auto& codeHandler : m_mouseMoves)
                {
                    codeHandler.Process(mouseLocation);
                }
                break;
            }
            case EVENT_MOUSEUP:
            {
                auto mouseLocation = &(ENGINE().GetMousPosition());

                for (auto& codeHandler : m_mouseClicks)
                {
                    codeHandler.Process(mouseLocation);
                }
                break;
            }
            case EVENT_GAMEPAD_THUMSTICK_AXIS_CHANGE:
            {
                auto* event = static_cast<EventGamepadThumbstickAxisChanged*>(baseEvent);
                for (auto& gamepad : m_gamepads)
                {
                    auto *ptr = gamepad.get();
                    if (ptr != nullptr)
                    {
                        ptr->ProcessEvent(event);
                    }
                }
                break;
            }
            case EVENT_GAMEPAD_BUTTON_ACTION_CHANGE:
            {
                auto *event = static_cast<EventGamepadButtonEventChanged*>(baseEvent);
                auto& action = event->GetAction();

                for (auto& gamepad : m_gamepads)
                {
                    auto *ptr = gamepad.get();
                    if (ptr != nullptr)
                    {
                        ptr->ProcessButtonEvent(&action);
                    }
                }
                break;
            }
            case EVENT_GAMEPAD_CONNECTION_CHANGE:
            {
                auto* event = static_cast<EventGamepadConnectionChanged*>(baseEvent);

                m_gamepads.clear();

                if (event->GetConnectionStatus() == GAMEPAD_CONNECTION_STATUS_CONNECTED)
                {
                    auto *gamepadHandle = event->GetDeviceHandle();
                    auto *gamepad = new Gamepad(event->GetGamepadType(), event->GetGamepadFamily(), gamepadHandle);
                    m_gamepads.emplace_back(std::move(gamepad));

                    for (auto& codeHandler : m_gamepadConnection)
                    {
                        codeHandler.Process((GamepadI**)&gamepad);
                    }
                }
                else
                {
                    for (auto& codeHandler : m_gamepadConnection)
                    {
                        codeHandler.Process(nullptr);
                    }

                }
                break;
            }
            case EVENT_QUIT:
            {
                return 1;
            }
        }
    }

    return 0;
}

EventIdentifier EventsManager::RegisterMouseMovedEvents(std::shared_ptr<CallableParameters1<Origin>> fnc)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_mouseMoves.push_back(EventHolderMouseMoved(identifier, fnc));
    return identifier;
}

EventIdentifier EventsManager::RegisterMouseClickedEvents(std::shared_ptr<CallableParameters1<Origin>> fnc)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_mouseClicks.push_back(EventHolderMouseClicked(identifier, fnc));
    return identifier;
}

EventIdentifier EventsManager::RegisterKeyShortcut(std::vector<EventFlagType> modifiers, std::vector<unsigned short>keys, std::shared_ptr<CallableParametersEmpty> fnc)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_keyShortcuts.push_back(EventHolderKeyShortcut(identifier, modifiers, keys, fnc));
    return identifier;
}

EventIdentifier EventsManager::RegisterKeyDown(std::shared_ptr<CallableParameters1<char>> fnc)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_keyDowns.push_back(EventHolderKeyDown(identifier, fnc));
    return identifier;
}

EventIdentifier EventsManager::RegisterKeyUp(std::shared_ptr<CallableParameters1<char>> fnc)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_keyUps.push_back(EventHolderKeyDown(identifier, fnc));
    return identifier;
}

EventIdentifier EventsManager::RegisterGamepadConnection(std::shared_ptr<CallableParameters2<GamepadI*, bool>> fnc)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_gamepadConnection.push_back(EventHolderGamepadConnection(identifier, fnc));
    return identifier;
}

void EventsManager::Unregister(EventHolderIdentifier* eventHolder)
{
    if (eventHolder != nullptr)
    {
        UnregisterEvent(eventHolder->GetIdentifier());
    }
}

template <typename T>
static void RemoveIfExists(EventIdentifier identifier, std::vector<T> &list)
{
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        EventHolderIdentifier holder = static_cast<EventHolderIdentifier>(*it);
        if (holder.GetIdentifier() == identifier)
        {
            list.erase(it);
            return;
        }
    }
}

void EventsManager::UnregisterEvent(EventIdentifier identifier)
{
    RemoveIfExists(identifier, m_mouseMoves);
    RemoveIfExists(identifier, m_mouseClicks);
    RemoveIfExists(identifier, m_keyShortcuts);
    RemoveIfExists(identifier, m_keyDowns);
    RemoveIfExists(identifier, m_keyUps);
    RemoveIfExists(identifier, m_gamepadConnection);
}

void EventsManager::UnregisterAllEvents()
{
    m_mouseMoves.clear();
    m_mouseClicks.clear();
    m_keyShortcuts.clear();
    m_keyDowns.clear();
    m_keyUps.clear();
    m_gamepadConnection.clear();
}
