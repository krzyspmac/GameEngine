//
//  events_manager.cpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#include "events_manager.hpp"
#include "engine.hpp"

using namespace engine;

int EventsManager::DoEvents()
{
    EventI *event = nullptr;

    while (m_eventProvider.PollEvent(&event))
    {
        switch (event->GetType())
        {
            case EVENT_NONE:
                break;
            case EVENT_KEYDOWN:
                break;
            case EVENT_MOUSEMOVE:
                std::for_each(m_mouseMoves.begin(), m_mouseMoves.end(), [&](EventHolderMouseMoved &l) {
                    auto mouseEvent = static_cast<EventMouseMove*>(event);
                    l.Process(&mouseEvent->GetLocation());
                });
                break;
            case EVENT_MOUSEUP:
                std::for_each(m_mouseClicks.begin(), m_mouseClicks.end(), [&](EventHolderMouseClicked &l) {
                    Origin& mousePosition = GetMainEngine()->GetMousPosition();
                    l.Process(&mousePosition);
                });
                break;
            case EVENT_QUIT:
                return 1;
        }
    }

    return 0;
}

void EventsManager::RegisterMouseMovedEvents(EventHolderMouseMoved val)
{
    m_mouseMoves.push_back(val);
}

void EventsManager::RegisterMouseClickedEvents(EventHolderMouseClicked val)
{
    m_mouseClicks.push_back(val);
}

void EventsManager::RegisterGeneralInputEvents(EventHolderSDLEvent val)
{
    m_generalInput.push_back(val);
}
