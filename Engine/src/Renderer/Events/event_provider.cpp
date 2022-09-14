//
//  event_provider.cpp
//  RendererAppSDL
//
//  Created by krzysp on 21/12/2021.
//

#include "event_provider.hpp"

#define POOL_COUNT_PER_TYPE 50

using namespace engine;

EventProvider::EventProvider()
    : EventProviderI()
{
    {
        auto *pool = new ObjectPool<EventI>(POOL_COUNT_PER_TYPE, [](void){
            return new EventMouseMove({0, 0});
        });
        m_poolMouseMove = std::unique_ptr<ObjectPool<EventI>>(std::move(pool));
    }

    {
        auto *pool = new ObjectPool<EventI>(POOL_COUNT_PER_TYPE, [](void){
            return new EventMouseLeftUp();
        });
        m_poolMouseLeftUp = std::unique_ptr<ObjectPool<EventI>>(std::move(pool));
    }

    {
        auto *pool = new ObjectPool<EventI>(POOL_COUNT_PER_TYPE, [](void){
            return new EventKeyFlagStateChanged();
        });
        m_poolKeyFlagStateChanged = std::unique_ptr<ObjectPool<EventI>>(std::move(pool));
    }

    {
        auto *pool = new ObjectPool<EventI>(POOL_COUNT_PER_TYPE, [](void){
            return new EventKeyStateChanged();
        });
        m_poolKeyStateChanged = std::unique_ptr<ObjectPool<EventI>>(std::move(pool));
    }

    {
        auto *pool = new ObjectPool<EventI>(POOL_COUNT_PER_TYPE, [](void){
            return new EventGamepadThumbstickAxisChanged();
        });
        m_poolThumbstickAxisChanged = std::unique_ptr<ObjectPool<EventI>>(std::move(pool));
    }

    {
        auto *pool = new ObjectPool<EventI>(10, [](void){
            return new EventGamepadConnectionChanged(GAMEPAD_TYPE_UNKNOWN, GAMEPAD_MAKE_UNKNOWN, GAMEPAD_CONNECTION_STATUS_UNKNOWN);
        });
        m_poolGamepadConnectionChanged = std::unique_ptr<ObjectPool<EventI>>(std::move(pool));
    }
}

ObjectPool<EventI> *EventProvider::EventsPoolForType(EventType type)
{
    switch (type)
    {
        case EVENT_NONE:
            return nullptr;
        case EVENT_KEY_FLAG_STATE_CHANGE:
            return m_poolKeyFlagStateChanged.get();
        case EVENT_KEY_STATE_CHANGE:
            return m_poolKeyStateChanged.get();
        case EVENT_MOUSEMOVE:
            return m_poolMouseMove.get();
        case EVENT_MOUSEUP:
            return m_poolMouseLeftUp.get();
        case EVENT_GAMEPAD_THUMSTICK_AXIS_CHANGE:
            return m_poolThumbstickAxisChanged.get();
        case EVENT_GAMEPAD_CONNECTION_CHANGE:
            return m_poolGamepadConnectionChanged.get();
        case EVENT_QUIT:
            return nullptr;
    }
}

EventI* EventProvider::EventsPoolDequeue(EventType type)
{
    auto* pool = EventsPoolForType(type);
    if (pool != nullptr)
    {
        return pool->Dequeue();
    }
    else
    {
        return nullptr;
    }
}

void EventProvider::EventsPoolPutBack(EventI *event)
{
    auto* pool = EventsPoolForType(event->GetType());
    if (pool != nullptr)
    {
        return pool->PutBack(event);
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

void EventProvider::PushFlagsChange(EventFlagType flagType, bool value)
{
    EventI *baseEvent = EventsPoolDequeue(EVENT_KEY_FLAG_STATE_CHANGE);
    if (baseEvent != nullptr)
    {
        auto* event = static_cast<EventKeyFlagStateChanged*>(baseEvent);
        event->GetState() = value;
        event->GetFlagType() = flagType;
        EventPush(baseEvent);
    }
}

void EventProvider::PushKeyStateChange(unsigned short key, bool pressed)
{
    EventI *baseEvent = EventsPoolDequeue(EVENT_KEY_STATE_CHANGE);
    if (baseEvent != nullptr)
    {
        auto* event = static_cast<EventKeyStateChanged*>(baseEvent);
        event->GetKey() = key;
        event->GetIsDown() = pressed;
        EventPush(baseEvent);
    }
}

void EventProvider::PushLeftThumbstickAxisChange(float xAxis, float yAxis)
{
    EventI *baseEvent = EventsPoolDequeue(EVENT_GAMEPAD_THUMSTICK_AXIS_CHANGE);
    if (baseEvent != nullptr)
    {
        auto* event = static_cast<EventGamepadThumbstickAxisChanged*>(baseEvent);
        event->GetVector() = Vector2(xAxis, yAxis);
        event->GetThumbstickType() = GAMEPAD_THUMBSTICK_AXIS_LEFT;
        EventPush(baseEvent);
    }
}

void EventProvider::PushRightThumbstickAxisChange(float xAxis, float yAxis)
{
    EventI *baseEvent = EventsPoolDequeue(EVENT_GAMEPAD_THUMSTICK_AXIS_CHANGE);
    if (baseEvent != nullptr)
    {
        auto* event = static_cast<EventGamepadThumbstickAxisChanged*>(baseEvent);
        event->GetVector() = Vector2(xAxis, yAxis);
        event->GetThumbstickType() = GAMEPAD_THUMBSTICK_AXIS_RIGHT;
        EventPush(baseEvent);
    }
}

void EventProvider::PushGamepadConnectionEvent(GamepadType gamepadType, GamepadMakeFamily gamepadFamily, GamepadConnectionStatus connectionStatus)
{
    EventI *baseEvent = EventsPoolDequeue(EVENT_GAMEPAD_CONNECTION_CHANGE);
    if (baseEvent != nullptr)
    {
        auto* event = static_cast<EventGamepadConnectionChanged*>(baseEvent);
        event->GetGamepadType() = gamepadType;
        event->GetGamepadFamily() = gamepadFamily;
        event->GetConnectionStatus() = connectionStatus;
        EventPush(baseEvent);
    }
}

bool EventProvider::PollEvent(EventI **outEvent)
{
    if (!m_eventQueue.empty())
    {
        if (outEvent != nullptr)
        {
            auto *last = m_eventQueue.back();
            *outEvent = last;
            EventsPoolPutBack(last);
            m_eventQueue.pop_back();
            return true;
        }
    }
    return false;
}
