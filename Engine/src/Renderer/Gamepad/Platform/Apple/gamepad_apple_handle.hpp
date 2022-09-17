//
//  gamepad_apple_handle.hpp
//  Engine-Mac
//
//  Created by krzysp on 17/09/2022.
//

#ifndef gamepad_apple_handle_hpp
#define gamepad_apple_handle_hpp

#include "common.h"
#include "common_engine_impl.h"
#include "gamepad_interface.h"
#include "events_manager_types.hpp"

#include <GameController/GameController.h>

namespace engine
{
    class GamepadAppleHandle: public GamepadDeviceHandleI
    {
        GCController *m_controller;
    public:
        GamepadAppleHandle(GCController *controller)
            : m_controller(controller)
        { };
        
        virtual ~GamepadAppleHandle() { };

    public: // GamepadDeviceHandleI
        void SetLight(Color3);
    };
};

#endif /* gamepad_apple_handle_hpp */
