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

#ifndef engine_screen_hpp
#define engine_screen_hpp

#include "engine_screen_interface.h"

namespace engine
{
    class EngineScreen: public EngineScreenI
    {
    private:
        Vector2 m_position;
        Rotation m_rotation;
        float m_zPosition;
        float m_alpha;
    public:
        EngineScreen();

    public: // AnimatablePropertiesI
        float       GetScale() { return 1.0; }
        void        SetScale(float x) { };
        void        SetPosition(Vector2 pos) { m_position = pos; };
        Vector2&    GetPosition() { return m_position; };
        void        SetZPosition(float zPos) { };
        float&      GetZPosition() { return m_zPosition; };
        void        SetAlpha(float val) { m_alpha = val; };
        float       GetAlpha() { return m_alpha; };
        void        SetRotation(Rotation rotation) { m_rotation = rotation; };
        Rotation    &GetRotation() { return m_rotation; }
    };
};

#endif /* engine_screen_hpp */
