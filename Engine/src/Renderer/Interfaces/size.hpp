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

#ifndef size_h
#define size_h

namespace engine
{

    typedef struct Size
    {
        int width;
        int height;
    } Size;

    typedef struct
    {
        float r;
        float g;
        float b;
    } Color3;

    typedef struct
    {
        float r;
        float g;
        float b;
        float a;
    } Color4;

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

#endif /* size_h */
