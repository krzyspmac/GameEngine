//
//  event_provider.cpp
//  RendererAppSDL
//
//  Created by krzysp on 21/12/2021.
//

#include "event_provider.hpp"

using namespace engine;

static EVENT SDLEvent2EVENT(SDL_Event *event);

int EventProvider::PollEvent(EVENT *event, SDL_Event *originalEvent)
{
    SDL_Event m_event;

    int hasEvent = SDL_PollEvent(&m_event);
    *event = SDLEvent2EVENT(&m_event);
    *originalEvent = m_event;
    return hasEvent;
}

void EventProvider::DoEvent()
{
    
}

static EVENT SDLEvent2EVENT(SDL_Event *event)
{
    switch (event->type)
    {
        case SDL_QUIT:
            return EVENT_QUIT;

        case SDL_KEYDOWN:
            return EVENT_KEYDOWN;

        case SDL_MOUSEMOTION:
            return EVENT_MOUSEMOVE;

        case SDL_MOUSEBUTTONUP:
            return EVENT_MOUSEUP;

        default:
            break;
    }

    return EVENT_NONE;
}

void EventProvider::SetMouseLocation(Origin)
{

}
