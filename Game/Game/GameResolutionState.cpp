#include "GameResolutionState.hpp"

GameResolutionState::GameResolutionState()
    : m_wantedSize({1280, 720})
    , m_engineState(engine::Globals::engineState())
{
    m_engineState->SetOnScreenSizeChange([&](engine::Size size, float density) {
        float scale = MIN((float)size.width / m_wantedSize.x, (float)size.height / m_wantedSize.y);
        m_engineState->SetViewportSize({(int)m_wantedSize.x, (int)m_wantedSize.y}, scale);
    });
}
