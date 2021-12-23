//
//  event_provider.cpp
//  RendererAppSDL
//
//  Created by krzysp on 21/12/2021.
//

#include "event_provider.hpp"

using namespace engine;

static EVENT SDLEvent2EVENT(SDL_Event *event);

int EventProvider::PollEvent(EVENT *event)
{
    SDL_Event m_event;

    int hasEvent = SDL_PollEvent(&m_event);
    *event = SDLEvent2EVENT(&m_event);
    return hasEvent;
}

static EVENT SDLEvent2EVENT(SDL_Event *event)
{
    switch (event->type)
    {
        case SDL_QUIT:
            return EVENT_QUIT;
            break;

        default:
            break;
    }

    return EVENT_NONE;
}
