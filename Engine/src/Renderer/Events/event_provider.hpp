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
        std::unique_ptr<ObjectPool<EventI>> m_poolGamepadButtonActionChanged;
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
        void    PushDpadAxisChange(float, float);
        void    PushButtonAction(GamepadButtonActionHolder);
        void    PushGamepadConnectionEvent(GamepadType gamepadType, GamepadMakeFamily gamepadFamily, GamepadConnectionStatus connectionStatus, GamepadDeviceHandleI *handle);

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
