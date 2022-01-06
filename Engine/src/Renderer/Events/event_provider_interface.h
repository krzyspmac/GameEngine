//
//  event_provider_interface.h
//  RendererAppSDL
//
//  Created by krzysp on 21/12/2021.
//

#ifndef event_provider_interface_h
#define event_provider_interface_h

namespace engine
{

typedef enum {
    EVENT_NONE = 0,
    EVENT_KEYDOWN,

    EVENT_MOUSEMOVE,
    EVENT_MOUSEUP,

    EVENT_QUIT,
} EVENT;

    class EventProviderI
    {
    public:
        EventProviderI() { };

    public:
        virtual void DoEvent() = 0;

        /// Polls the next event and puts in into
        /// &event. Returns 1 if more events need
        /// be processed or 0 if it's done.
        virtual int PollEvent(EVENT *event) = 0;
    };

}; // namespace engine

#endif /* event_provider_interface_h */
