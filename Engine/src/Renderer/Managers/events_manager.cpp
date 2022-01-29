//
//  events_manager.cpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#include "events_manager.hpp"
#include "engine.hpp"

using namespace engine;

EventsManager::EventsManager(EventProviderI &provider, EngineProviderI &engineProvider)
    : m_eventProvider(provider)
    , m_identifierCounter(0)
    , m_engineProvider(engineProvider)
    , m_shiftKeyDown(false)
    , m_controlKeyDown(false)
{
    bzero(m_keys, KEY_TABLE_SIZE);
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
                auto& state = m_keys[key];
                auto& isDown = event->GetIsDown();
                if (state != isDown)
                {
                    m_keys[key] = isDown;
                }

                for (auto& keyHandler : m_keyshortcuts)
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
                std::for_each(m_mouseMoves.begin(), m_mouseMoves.end(), [&](EventHolderMouseMoved &l) {
                    auto mouseEvent = static_cast<EventMouseMove*>(baseEvent);
                    l.Process(&mouseEvent->GetLocation());
                });
                break;
            }
            case EVENT_MOUSEUP:
            {
                std::for_each(m_mouseClicks.begin(), m_mouseClicks.end(), [&](EventHolderMouseClicked &l) {
                    Origin& mousePosition = GetMainEngine()->GetMousPosition();
                    l.Process(&mousePosition);
                });
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

EventIdentifier EventsManager::RegisterMouseMovedEvents(std::function<void(Origin*)> lambda)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_mouseMoves.push_back(EventHolderMouseMoved(identifier, lambda));
    return identifier;
}

EventIdentifier EventsManager::RegisterMouseClickedEvents(std::function<void(void*)> lambda)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_mouseClicks.push_back(EventHolderMouseClicked(identifier, lambda));
    return identifier;;
}

EventIdentifier EventsManager::RegisterKeyShortcut(std::vector<EventFlagType> modifiers, std::vector<unsigned short>keys, std::function<void(void*)> lambda)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_keyshortcuts.push_back(EventHolderKeyShortcutPressed(identifier, lambda, modifiers, keys));
    return identifier;
}

void EventsManager::UnregisterEvent(EventIdentifier identifier)
{
    for (auto it = m_mouseMoves.begin(); it != m_mouseMoves.end(); it++)
    {
        if ((*it).GetIdentifier() == identifier)
        {
            m_mouseMoves.erase(it);
            return;
        }
    }
    for (auto it = m_mouseClicks.begin(); it != m_mouseClicks.end(); it++)
    {
        if ((*it).GetIdentifier() == identifier)
        {
            m_mouseClicks.erase(it);
            return;
        }
    }
    for (auto it = m_keyshortcuts.begin(); it != m_keyshortcuts.end(); it++)
    {
        if ((*it).GetIdentifier() == identifier)
        {
            m_keyshortcuts.erase(it);
            return;
        }
    }
}

void EventsManager::UnregisterAllEvents()
{
    m_mouseMoves.clear();
    m_mouseClicks.clear();
    m_keyshortcuts.clear();
}

/** Event holder implementations */

bool EventHolderKeyShortcutPressed::Matches(bool shiftDown, bool controlDown, bool keys[KEY_TABLE_SIZE])
{
    for (auto& modifier : m_modifiers)
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
