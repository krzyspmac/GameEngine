//
//  engine_state_hpp
//  EngineState
//
//  Created by krzysp on 01/01/2022.
//

#ifndef engine_state_hpp
#define engine_state_hpp

#include "interfaces.h"
#include "callable.hpp"
#include "engine_state_interface.h"

namespace engine
{
    class EngineState: public EngineStateI
    {
        std::function<void(Size, float)> m_screenSizeChangeHandler;
        CallableScriptFunctionParameters3<float, float, float> m_screenSizeChangeScriptHandler;
    public:
        EngineState();
    public: // EngineStateI
        Size GetViewportSize();

        void SetViewportSize(Size, float);

        void SetOnScreenSizeChangeHandler(std::function<void(Size, float)>);

        void SetOnScreenSizeChange(CallableScriptFunctionParameters3<float, float, float>);

        void SendScreenSizeChangeEvent(Size, float);

    };
};

#endif /* engine_state_hpp */
