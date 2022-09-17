//
//  gamepad.hpp
//  Engine
//
//  Created by krzysp on 14/09/2022.
//

#ifndef gamepad_hpp
#define gamepad_hpp

#include "common.h"
#include "common_engine_impl.h"
#include "gamepad_interface.h"
#include "events_manager_types.hpp"
#include "scripting_engine_provider_interface.h"

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
        GamepadEventIdentifier RegisterLeftThumbstickAxis(CallableScriptFunctionParameters1<Vector2>);
        GamepadEventIdentifier RegisterRightThumbstickAxis(CallableScriptFunctionParameters1<Vector2>);
        GamepadEventIdentifier RegisterDpadAxis(CallableScriptFunctionParameters1<Vector2>);
        GamepadEventIdentifier RegisterButtonTapped(CallableScriptFunctionParameters2<GamepadButtonType, GamepadButtonAction>);
        void SetLight(Color3 color);
    private:

    private: /** scripting */
        /** @private */
        SCRIPTING_INTERFACE_HEADERS(Gamepad);
    };
};

#endif /* gamepad_hpp */
