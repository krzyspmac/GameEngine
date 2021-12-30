//
//  events_manager.cpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#include "events_manager.hpp"

using namespace engine;

int EventsManager::DoEvents()
{
    EVENT event;
    while (m_eventProvider.PollEvent(&event))
    {
        switch (event)
        {
            case EVENT_NONE:
            {
                break;
            }

            case EVENT_KEYDOWN:
            {
//                m_character->Change();
                break;
            }

            case EVENT_MOUSEMOVE:
            {
                Origin mouse;
                m_engineProvider.GetMousePosition(&mouse.x, &mouse.y);

                std::for_each(m_mouseMoves.begin(), m_mouseMoves.end(), [&](EventHolderMouseMoved &l) {
                    l.Process(&mouse);
                });
                break;
            }

            case EVENT_MOUSEUP:
            {
                std::for_each(m_mouseClicks.begin(), m_mouseClicks.end(), [&](EventHolderMouseClicked &l) {
                    l.Process(nullptr);
                });
                break;
            }

            case EVENT_QUIT:
            {
                return 1;
            }
        };
    };

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
