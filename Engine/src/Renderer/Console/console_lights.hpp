//
//  console_lights.hpp
//  Engine
//
//  Created by krzysp on 06/02/2022.
//

#ifndef console_lights_hpp
#define console_lights_hpp

#include "common.h"
#include "console_renderer_interface.h"

namespace engine
{
    class ConsoleLightManagement: public ConsoleLightManagementI
    {
        bool p_open;
    public:
        ConsoleLightManagement();
        
        void Render();
        void ToggleVisibility();
    };
};

#endif /* console_lights_hpp */
