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

#ifndef engine_setup_interface_h
#define engine_setup_interface_h

#include "common.h"
#include "interfaces.h"
#include "script_entry_interface.hpp"

namespace engine
{
    /** Available only on iOS */
    typedef enum VirtualGamepadConfiguration
    {
        GamepadConfiguration_Unknown            = 0
      , GamepadConfiguration_DirectionPad       = 1 << 0
      , GamepadConfiguration_LeftThumbstick     = 1 << 1
      , GamepadConfiguration_RightThumbstick    = 1 << 2

      , GamepadConfiguration_ButtonA            = 1 << 3
      , GamepadConfiguration_ButtonB            = 1 << 4
      , GamepadConfiguration_ButtonX            = 1 << 5
      , GamepadConfiguration_ButtonY            = 1 << 6

      , GamepadConfiguration_LeftShoulder       = 1 << 7
      , GamepadConfiguration_RightShoulder      = 1 << 8
      , GamepadConfiguration_LeftTrigger        = 1 << 9
      , GamepadConfiguration_RightTrigger       = 1 << 10

      , GamepadConfiguration_LeftThumbstickBtn  = 1 << 11
      , GamepadConfiguration_RightThumbstickBtn = 1 << 12
    } VirtualGamepadConfiguration;

    /** EngineSetup
        @brief Main .ini configuration file holder.
     */
    typedef struct EngineSetup
    {
        /** The game folder in relation to the executable path */
        std::string gameFolder;

        /** The initial resolution */
        Size resolution;

        /** Uses the gamepad if connected. The last one will be used.
            Default is true.
         */
        bool gamepad_support;

        /** Uses the gamepad virtual interface when gamepad is not availagle;
            only on iOS.
            Default is false.
         */
        bool gamepad_virtual_support;

        /** Virtual gamepad configuration. Only on iOS. */
        VirtualGamepadConfiguration gamepad_virtual_configuration;

        /** The scale to apply to the whole framebuffer. Allows for keeping
            the framebuffer resolution while scaling the whole screen.
            Default is 1.
         */
        float affineScale;

        /** Can mark the setup as dirty to inform the main renderer pass that
            changes have to pulled and reintegrated. */
        bool isDirty;

        /** Renderer background color */
        Color4 backgroundColor;

        /** Scripting init function */
        ScriptingFunctionVoid initFunction;

        /** Scripting frame-update function */
        ScriptingFunctionVoid frameUpdateFunction;

        EngineSetup()
        :   resolution( {320, 200} )
        ,   gamepad_support(true)
        ,   gamepad_virtual_support(false)
        ,   gamepad_virtual_configuration(GamepadConfiguration_Unknown)
        ,   affineScale( 1.0 )
        ,   isDirty(false)
        ,   backgroundColor({1.0, 0.0, 1.0, 1.0})
        ,   initFunction(nullptr)
        ,   frameUpdateFunction(nullptr)
        { };
    } EngineSetup;

    typedef struct VirtualGameConfigurationButtonMapping {
        const char *name;
        VirtualGamepadConfiguration mapping;

        VirtualGameConfigurationButtonMapping(const char *name, VirtualGamepadConfiguration mapping)
        {
            this->name = name;
            this->mapping = mapping;
        }

        static std::vector<VirtualGameConfigurationButtonMapping> *shared()
        {
            static std::vector<VirtualGameConfigurationButtonMapping> types;
            if (types.empty())
            {
                types.push_back(VirtualGameConfigurationButtonMapping("DirectionPad", GamepadConfiguration_DirectionPad));
                types.push_back(VirtualGameConfigurationButtonMapping("LeftThumbstick", GamepadConfiguration_LeftThumbstick));
                types.push_back(VirtualGameConfigurationButtonMapping("RightThumbstick", GamepadConfiguration_RightThumbstick));
                types.push_back(VirtualGameConfigurationButtonMapping("ButtonA", GamepadConfiguration_ButtonA));
                types.push_back(VirtualGameConfigurationButtonMapping("ButtonB", GamepadConfiguration_ButtonB));
                types.push_back(VirtualGameConfigurationButtonMapping("ButtonX", GamepadConfiguration_ButtonX));
                types.push_back(VirtualGameConfigurationButtonMapping("ButtonY", GamepadConfiguration_ButtonY));
                types.push_back(VirtualGameConfigurationButtonMapping("LeftShoulder", GamepadConfiguration_LeftShoulder));
                types.push_back(VirtualGameConfigurationButtonMapping("RightShoulder", GamepadConfiguration_RightShoulder));
                types.push_back(VirtualGameConfigurationButtonMapping("LeftTrigger", GamepadConfiguration_LeftTrigger));
                types.push_back(VirtualGameConfigurationButtonMapping("RightTrigger", GamepadConfiguration_RightTrigger));
                types.push_back(VirtualGameConfigurationButtonMapping("LeftThumbstickButton", GamepadConfiguration_LeftThumbstickBtn));
                types.push_back(VirtualGameConfigurationButtonMapping("RightThumbstickButton",GamepadConfiguration_RightThumbstickBtn));
            }
            return &types;
        }
    } GameButtonMapping;
};

#endif /* engine_setup_interface_h */
