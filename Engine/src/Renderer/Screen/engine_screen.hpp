//
//  engine_screen.hpp
//  Engine-Mac
//
//  Created by krzysp on 12/08/2022.
//

#ifndef engine_screen_hpp
#define engine_screen_hpp

#include "engine_screen_interface.h"
#include "scripting_engine_provider_interface.h"

namespace engine
{
    class EngineScreen: public EngineScreenI
    {
    private:
        Vector2 m_offset;
    public:
        EngineScreen();

        void SetScreenOffset(Vector2);
        Vector2& GetScreenOffset() { return m_offset; };

    private: /** scripting */
        /** @private */
        SCRIPTING_INTERFACE_HEADERS(EngineScreen);
    };
};

#endif /* engine_screen_hpp */
