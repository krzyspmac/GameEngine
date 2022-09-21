//
//  engine_setup_interface.h
//  Engine
//
//  Created by krzysp on 24/01/2022.
//

#ifndef engine_setup_interface_h
#define engine_setup_interface_h

#include "common.h"
#include "common_engine_impl.h"

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
    } VirtualGamepadConfiguration;

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

        EngineSetup()
        :   resolution( {320, 200} )
        ,   gamepad_support(true)
        ,   gamepad_virtual_support(false)
        ,   gamepad_virtual_configuration(GamepadConfiguration_Unknown)
        ,   affineScale( 1.0 )
        ,   isDirty(false)
        ,   backgroundColor({1.0, 0.0, 1.0, 1.0})
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
            }
            return &types;
        }
    } GameButtonMapping;
};

#endif /* engine_setup_interface_h */
