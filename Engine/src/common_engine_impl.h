//
//  common_engine_impl.h
//  RendererAppSDL
//
//  Created by krzysp on 20/12/2021.
//

#ifndef common_engine_impl_h
#define common_engine_impl_h

#include "general.hpp"
#include "vector2.hpp"
#include "line.hpp"

namespace engine
{

    typedef struct Size
    {
        int width;
        int height;
    } Size;

    typedef struct Color
    {
        int r;
        int g;
        int b;
        int a;
    } Color;

    typedef struct
    {
        int x;
        int y;
    } Origin;

    typedef struct
    {
        Origin origin;
        Size size;
    } Rect;

    typedef struct
    {
        float x;
        float y;
    } OriginF;

    typedef struct
    {
        float width;
        float height;
    } SizeF;

    typedef struct
    {
        OriginF origin;
        SizeF size;
    } RectF;

    inline Origin OriginMake(int x, int y)
    {
        Origin result;
        result.x = x;
        result.y = y;
        return result;
    };

    inline Origin OriginGetDiff(Vector2 &first, Origin &second)
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
