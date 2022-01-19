//
//  event_provider_interface.h
//  RendererAppSDL
//
//  Created by krzysp on 21/12/2021.
//

#ifndef event_provider_interface_h
#define event_provider_interface_h

#include "common.h"
#include "common_engine_impl.h"

namespace engine
{

    typedef enum {
        EVENT_NONE = 0,
        EVENT_KEYDOWN,

        EVENT_MOUSEMOVE,
        EVENT_MOUSEUP,

        EVENT_QUIT,
    } EVENT;

    /** Declares an abstract interface to provide real events directly into the
        engine. The platform code should setup its own processing and pass those
        events to the event provider.

        During one frame multiple events can be passed.
     */
    class EventProviderI
    {
    public:
        EventProviderI() { };

    public:
        virtual void DoEvent() = 0;

        /** Updates the current mouse location if applicable. Also sends out
            a mouse moved event. */
        virtual void SetMouseLocation(Origin) = 0;

        /// Polls the next event and puts in into
        /// &event. Returns 1 if more events need
        /// be processed or 0 if it's done.
        virtual int PollEvent(EVENT *event, SDL_Event *originalEvent) = 0;
    };

}; // namespace engine

#endif /* event_provider_interface_h */
