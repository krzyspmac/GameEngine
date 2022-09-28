//
//  gamepad_interface.h
//  Engine
//
//  Created by krzysp on 14/09/2022.
//

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
        virtual GamepadEventIdentifier RegisterLeftThumbstickAxis(CallableParameters1<Vector2>) = 0;
        virtual GamepadEventIdentifier RegisterRightThumbstickAxis(CallableParameters1<Vector2>) = 0;
        virtual GamepadEventIdentifier RegisterDpadAxis(CallableParameters1<Vector2>) = 0;
        virtual GamepadEventIdentifier RegisterButtonTapped(CallableParameters3<GamepadButtonType, GamepadButtonAction, float>) = 0;

        virtual void SetLight(Color3) = 0;
    };
};

#endif /* gamepad_interface_h */
