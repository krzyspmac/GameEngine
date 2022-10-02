//
//  engine_screen.cpp
//  Engine-Mac
//
//  Created by krzysp on 12/08/2022.
//

#include "engine_screen.hpp"

using namespace engine;

EngineScreen::EngineScreen()
    : m_position({0.0f, 0.0f})
    , m_rotation(Rotation::empty())
    , m_zPosition(0.0f)
    , m_alpha(1.0f)
{
}
