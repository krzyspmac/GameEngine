//
//  common_engine_impl.h
//  RendererAppSDL
//
//  Created by krzysp on 20/12/2021.
//

#ifndef common_engine_impl_h
#define common_engine_impl_h

#import "SDL.h"

namespace engine
{

    typedef struct {
        SDL_Renderer *renderer;
        SDL_Window *window;
    } SDL_APP;

    typedef struct Size {
        int width;
        int height;
    } Size;

    typedef struct {
        int x;
        int y;
    } Origin;

    inline Origin OriginMake(int x, int y) {
        Origin result;
        result.x = x;
        result.y = y;
        return result;;
    };
}

#endif /* common_engine_impl_h */
