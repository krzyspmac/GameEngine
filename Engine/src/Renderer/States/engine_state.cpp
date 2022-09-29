//
//  engine.cpp
//  Engine
//
//  Created by krzysp on 01/01/2022.
//

#include "engine_state.hpp"
#include "engine.hpp"
#include "common.h"

using namespace engine;

EngineState::EngineState()
    : m_screenSizeChangeHandler(nullptr)
{

}

Size EngineState::GetViewportSize()
{
    return ENGINE().getProvider().GetDesiredViewport();
}

void EngineState::SetOnScreenSizeChangeHandler(std::function<void (Size, float)> lambda)
{
    m_screenSizeChangeHandler = lambda;
}

void EngineState::SendScreenSizeChangeEvent(Size size, float density)
{
    if (m_screenSizeChangeHandler != nullptr)
    {
        m_screenSizeChangeHandler(size, density);
    }
}

void EngineState::SetViewportSize(Size size, float scale)
{
    auto& engineSetup = ENGINE().GetEngineSetup();
    engineSetup.resolution.width = size.width;
    engineSetup.resolution.height = size.height;
    engineSetup.affineScale = scale;
    engineSetup.isDirty = true;
}
