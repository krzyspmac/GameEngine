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

#ifndef gamepad_hpp
#define gamepad_hpp

#include "common.h"
#include "interfaces.h"
#include "gamepad_interface.h"
#include "events_manager_types.hpp"

namespace engine
{
    class Gamepad: public GamepadI
    {
    private:
        GamepadEventIdentifier m_identifierCounter;
        std::vector<EventHolderGamepadStickAxis> m_leftStickAxisChange;
        std::vector<EventHolderGamepadStickAxis> m_rightStickAxisChange;
        std::vector<EventHolderGamepadStickAxis> m_dpadAxisChange;
        std::vector<EventHolderGamepadButton> m_buttonChange;

    public:
        Gamepad(GamepadType type, GamepadMakeFamily family, GamepadDeviceHandleI *handle)
            : GamepadI(type, family, handle)
            , m_identifierCounter(0)
        { };

        ~Gamepad();

    public: // GamepadI
        void ProcessEvent(EventGamepadThumbstickAxisChanged* event);
        void ProcessButtonEvent(GamepadButtonActionHolder*);

        void UnregisterEvent(GamepadEventIdentifier);
        void UnregisterAllEvents();

        GamepadEventIdentifier RegisterLeftThumbstickAxis(std::shared_ptr<CallableParameters1<Vector2>>);
        GamepadEventIdentifier RegisterRightThumbstickAxis(std::shared_ptr<CallableParameters1<Vector2>>);
        GamepadEventIdentifier RegisterDpadAxis(std::shared_ptr<CallableParameters1<Vector2>>);
        GamepadEventIdentifier RegisterButtonTapped(std::shared_ptr<CallableParameters3<GamepadButtonType, GamepadButtonAction, float>>);

        void SetLight(Color3 color);
    };
};

#endif /* gamepad_hpp */
