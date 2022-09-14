//
//  event_provider.hpp
//  RendererAppSDL
//
//  Created by krzysp on 21/12/2021.
//

#ifndef event_provider_hpp
#define event_provider_hpp

#include "common.h"
#include "event_provider_interface.h"
#include "object_pool.hpp"

namespace engine
{
    class EventProvider: public EventProviderI
    {
        std::unique_ptr<ObjectPool<EventI>> m_poolMouseMove;
        std::unique_ptr<ObjectPool<EventI>> m_poolMouseLeftUp;
        std::unique_ptr<ObjectPool<EventI>> m_poolKeyFlagStateChanged;
        std::unique_ptr<ObjectPool<EventI>> m_poolKeyStateChanged;
        std::unique_ptr<ObjectPool<EventI>> m_poolThumbstickAxisChanged;
        std::unique_ptr<ObjectPool<EventI>> m_poolGamepadConnectionChanged;

        std::vector<EventI*> m_eventQueue;
    public:
        EventProvider();

    public:
        void    PushMouseLocation(Origin);
        void    PushMouseLeftUp();
        void    PushFlagsChange(EventFlagType, bool);
        void    PushKeyStateChange(unsigned short, bool);
        void    PushLeftThumbstickAxisChange(float, float);
        void    PushRightThumbstickAxisChange(float, float);
        void    PushGamepadConnectionEvent(GamepadType gamepadType, GamepadMakeFamily gamepadFamily, GamepadConnectionStatus connectionStatus);

        bool    PollEvent(EventI **outEvent);

    private:
        EventI* EventsPoolDequeue(EventType type);
        void    EventsPoolPutBack(EventI*);

        void    EventPush(EventI*);

    private: // helpers
        ObjectPool<EventI> *EventsPoolForType(EventType type);
    };

}; // namespace engine

#endif /* event_provider_hpp */
