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

#include "GameInput.hpp"

using namespace engine;

GameInput::GameInput()
    : m_eventsManager(Globals::eventsManager())
    , m_leftThumbstickVector(Vector2::zero())
{
    m_keys = m_eventsManager->GetKeys();

    SetupHandlers();
}

void GameInput::SetupHandlers()
{
    m_eventsManager->RegisterGamepadConnection(CallableParameters2<GamepadI *, bool>::make_shared([&](GamepadI *gamepad, bool active){
        UpdateWithGamepad(gamepad);
    }));

    m_eventsManager->RegisterKeyUp(CallableParameters1<char>::make_shared([&](char c){
        UpdateKeys();
    }));

    m_eventsManager->RegisterKeyDown(CallableParameters1<char>::make_shared([&](char c){
        UpdateKeys();
    }));
}

void GameInput::UpdateWithGamepad(GamepadI* gamepad)
{
    if (gamepad == nullptr) { return; };

    gamepad->RegisterLeftThumbstickAxis(CallableParameters1<Vector2>::make_shared([&](Vector2 vector){
        m_leftThumbstickVector = vector;
    }));

    gamepad->RegisterRightThumbstickAxis(CallableParameters1<Vector2>::make_shared([&](Vector2 vector){
        m_rightThumbstickVector = vector * 3;
    }));
}

void GameInput::UpdateKeys()
{
    if (m_keys['d'] || m_keys['D'])
    {
        m_leftThumbstickVector.x = 1.0f;
    }
    else if (m_keys['a'] || m_keys['A'])
    {
        m_leftThumbstickVector.x = -1.0f;
    }
    else
    {
        m_leftThumbstickVector.x = 0.0f;
    }

    if (m_keys['s'] || m_keys['S'])
    {
        m_leftThumbstickVector.y = 1.0f;
    }
    else if (m_keys['w'] || m_keys['W'])
    {
        m_leftThumbstickVector.y = -1.0f;
    }
    else
    {
        m_leftThumbstickVector.y = 0.0f;
    }
}
