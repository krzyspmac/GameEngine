//
//  gamepad_apple.cpp
//  Engine-Mac
//
//  Created by krzysp on 17/09/2022.
//

#include "gamepad_apple_handle.hpp"
#include <GameController/GameController.h>

using namespace engine;

void GamepadAppleHandle::SetLight(Color3 color3)
{
    if (m_controller != nullptr)
    {
        GCDeviceLight *light = m_controller.light;
        if (light != nil)
        {
            light.color = [[GCColor alloc] initWithRed:color3.r green:color3.g blue:color3.b];
        }
    }
}
