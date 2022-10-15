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

#ifndef gamepad_interface_h
#define gamepad_interface_h

#include "common.h"
#include "interfaces.h"
#include "event_provider_interface.h"
#include "callable_interface.h"

namespace engine
{
    typedef unsigned int GamepadEventIdentifier;
    
    class GamepadI
    {
    protected:
        GamepadType m_gamepadType;
        GamepadMakeFamily m_gamepadFamily;
        GamepadDeviceHandleI *m_handle;

    public:
        GamepadI(GamepadType type, GamepadMakeFamily family, GamepadDeviceHandleI *handle)
            : m_gamepadType(type)
            , m_gamepadFamily(family)
            , m_handle(handle)
        { };

        virtual ~GamepadI() { };

        virtual void ProcessEvent(EventGamepadThumbstickAxisChanged* event) = 0;
        virtual void ProcessButtonEvent(GamepadButtonActionHolder*) = 0;
        virtual void UnregisterEvent(GamepadEventIdentifier) = 0;
        virtual void UnregisterAllEvents() = 0;
        virtual GamepadEventIdentifier RegisterLeftThumbstickAxis(std::shared_ptr<CallableParameters1<Vector2>>) = 0;
        virtual GamepadEventIdentifier RegisterRightThumbstickAxis(std::shared_ptr<CallableParameters1<Vector2>>) = 0;
        virtual GamepadEventIdentifier RegisterDpadAxis(std::shared_ptr<CallableParameters1<Vector2>>) = 0;
        virtual GamepadEventIdentifier RegisterButtonTapped(std::shared_ptr<CallableParameters3<GamepadButtonType, GamepadButtonAction, float>>) = 0;

        virtual void SetLight(Color3) = 0;
    };
};

#endif /* gamepad_interface_h */
