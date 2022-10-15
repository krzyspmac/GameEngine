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

#ifndef InertiaProcessor_hpp
#define InertiaProcessor_hpp

#include "game_include.hpp"

typedef struct IntertiaProcessorDescriptor {
    double max_speed;    // maximum speed (px/s)
    double inc_speed;    // speed increase when force applied (in px/s)
    double dmp_speed;    // speed fall when force not applied (in px/s)

    static IntertiaProcessorDescriptor standard() {
        IntertiaProcessorDescriptor result;
        result.max_speed = 20;
        result.inc_speed = 10;
        result.dmp_speed = 0.05;
        return result;
    }
} IntertiaProcessorDescriptor;

class IntertiaProcessor {
    IntertiaProcessorDescriptor m_descriptor;
    engine::Vector2 m_position;
    engine::Vector2 m_movementVector;
    engine::Vector2 m_forceVector;
    engine::TimeI&  m_time;
    double          m_frameDeltaSec;
public:
    IntertiaProcessor(IntertiaProcessorDescriptor descriptor = IntertiaProcessorDescriptor::standard());

    void UpdateForceVector(engine::Vector2);
    void Tick();
    void SetPosition(engine::Vector2);
    auto GetPosition() { return m_position; };

private:
    void Advance();
    void Damper();
    void Limit();
    void UpdatePosition();
};

#endif /* InertiaProcessor_hpp */
