//
//  engine_state_hpp
//  EngineState
//
//  Created by krzysp on 01/01/2022.
//

#ifndef engine_state_hpp
#define engine_state_hpp

#include "interfaces.h"
#include "engine_state_interface.h"

namespace engine
{
    class EngineState: public EngineStateI
    {
        std::function<void(Size, float)> m_screenSizeChangeHandler;
    public:
        EngineState();
    public: // EngineStateI
        Size GetViewportSize();

        void SetViewportSize(Size, float);

        void SetOnScreenSizeChangeHandler(std::function<void(Size, float)>);

        void SendScreenSizeChangeEvent(Size, float);

    };
};

#endif /* engine_state_hpp */
