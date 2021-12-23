//
//  common_engine_impl.h
//  RendererAppSDL
//
//  Created by krzysp on 20/12/2021.
//

#ifndef common_engine_impl_h
#define common_engine_impl_h

//#import "common.h"
#import "SDL.h"

namespace engine
{

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
} SDL_APP;

typedef struct {
    int x;
    int y;
} MOUSE_POSITION;

}

#endif /* common_engine_impl_h */
