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
