//
//  event_provider.cpp
//  RendererAppSDL
//
//  Created by krzysp on 21/12/2021.
//

#include "event_provider.hpp"

#define POOL_COUNT_PER_TYPE 20

using namespace engine;

EventProvider::EventProvider()
    :EventProviderI()
{
    EventsPoolPopulate();
}

void EventProvider::EventsPoolPopulate()
{
    for (int i = 0; i < POOL_COUNT_PER_TYPE; ++i)
    {
        EventMouseMove *event = new EventMouseMove({0, 0});
        m_poolMouseMove.emplace_back(std::unique_ptr<EventMouseMove>(std::move(event)));
    }
    for (int i = 0; i < POOL_COUNT_PER_TYPE; ++i)
    {
        EventMouseLeftUp *event = new EventMouseLeftUp();
        m_poolMouseLeftUp.emplace_back(std::unique_ptr<EventMouseLeftUp>(std::move(event)));
    }
}

std::vector<std::unique_ptr<EventI>> *EventProvider::EventsPoolForType(EventType type)
{
    switch (type)
    {
        case EVENT_NONE:
            return nullptr;
        case EVENT_KEYDOWN:
            return nullptr;
        case EVENT_MOUSEMOVE:
            return &m_poolMouseMove;
        case EVENT_MOUSEUP:
            return &m_poolMouseLeftUp;
        case EVENT_QUIT:
            return nullptr;
    }
}

EventI* EventProvider::EventsPoolDequeue(EventType type)
{
    std::vector<std::unique_ptr<EventI>> *pool = EventsPoolForType(type);

    if (pool != nullptr)
    {
        for (auto& event : *pool)
        {
            if (!event.get()->GetInUse())
            {
                return event.get();
            }
        }
        return nullptr;
    }
    else
    {
        return nullptr;
    }
}

void EventProvider::EventPush(EventI *event)
{
    m_eventQueue.emplace_back(event);
}

void EventProvider::PushMouseLocation(Origin position)
{
    EventI *event = EventsPoolDequeue(EVENT_MOUSEMOVE);
    if (event != nullptr)
    {
        static_cast<EventMouseMove*>(event)->GetLocation() = position;
        EventPush(event);
    }
}

void EventProvider::PushMouseLeftUp()
{
    EventI *event = EventsPoolDequeue(EVENT_MOUSEUP);
    if (event != nullptr)
    {
        EventPush(event);
    }
}

bool EventProvider::PollEvent(EventI **outEvent)
{
    if (!m_eventQueue.empty())
    {
        if (outEvent != nullptr)
        {
            *outEvent = m_eventQueue.back();
            m_eventQueue.pop_back();
            return true;
        }
    }
    return false;
}
