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

    typedef struct
    {
        SDL_Renderer *renderer;
        SDL_Window *window;
    } SDL_APP;

    typedef struct Size
    {
        int width;
        int height;
    } Size;

    typedef struct
    {
        int x;
        int y;
    } Origin;

    typedef struct
    {
        float x;
        float y;
    } Vector2;

    inline Vector2 Vector2Make(float x, float y)
    {
        Vector2 result;
        result.x = x;
        result.y = y;
        return result;;
    };

    inline bool Vector2Equals(Vector2 &first, Vector2 &second)
    {
        return first.x == second.x && first.y == second.y;
    };

    inline Origin OriginMake(int x, int y)
    {
        Origin result;
        result.x = x;
        result.y = y;
        return result;;
    };

    inline Origin OriginGetDiff(Origin &first, Origin &second)
    {
        Origin result;
        result.x = first.x - second.x;
        result.y = first.y - second.y;
        return result;
    }

    inline bool OriginEquals(Origin &first, Origin &second)
    {
        return first.x == second.x && first.y == second.y;
    }
}

#endif /* common_engine_impl_h */
