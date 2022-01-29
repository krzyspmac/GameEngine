//
//  console_renderer.cpp
//  Engine
//
//  Created by krzysp on 07/01/2022.
//

#include <Metal/Metal.h>
#include <QuartzCore/QuartzCore.h>
#include "common.h"
#include "console_renderer.h"
#include "engine.hpp"
#include "console_logger.hpp"
#include "console_terminal.hpp"

#if defined(TARGET_IOS) || defined(TARGET_TVOS)
#include <UIKit/UIKit.h>
#else
#include <Cocoa/Cocoa.h>
#endif

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_metal.h"

#include "console_app_renderer_mac.hpp"

using namespace engine;

ConsoleRenderer::ConsoleRenderer()
    : m_hidden(true)
{
    this->m_platformRenderer = std::unique_ptr<ConsoleAppRendererI>(new ConsoleAppRendererMac());
    this->m_logger = new ConsoleLog();
    this->m_terminal = new ConsoleTerminal();
}

ConsoleLogI& ConsoleRenderer::GetLogger()
{
    return *m_logger;
}

ConsoleTerminalI& ConsoleRenderer::GetTerminal()
{
    return *m_terminal;
}

void ConsoleRenderer::Setup()
{
#if SHOW_CONSOLE
    SetupEvents();
#endif
}

void ConsoleRenderer::SetupEvents()
{
    GetMainEngine()->getEventsManager().RegisterKeyShortcut( {FLAG_CONTROL, FLAG_SHIFT}, { 'C' }, [&](void*) {
        this->SetConsoleHidden(!m_hidden);
    });
}

void ConsoleRenderer::DoFrame()
{
#if SHOW_CONSOLE
    m_platformRenderer->DoFrame([&]{
        DoGui();
    });
#endif
}

void ConsoleRenderer::SetConsoleHidden(bool hidden)
{
#if SHOW_CONSOLE
    if (!m_platformRenderer->IsSetup())
    {
        if (!hidden)
        {
            m_platformRenderer->Setup();
        }
    }
    else
    {
        m_platformRenderer->SetConsoleHidden(hidden);
    }

    m_hidden = hidden;
#endif
}

bool ConsoleRenderer::GetConsoleHidden()
{
    return m_hidden;
}

void ConsoleRenderer::DoGui()
{
#if SHOW_CONSOLE
    DoMenuBar();
    //ImGui::ShowDemoWindow();

    m_logger->Render();
    m_terminal->Render();
#endif
}

void ConsoleRenderer::DoMenuBar()
{
#if SHOW_CONSOLE
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Log"))
        {
            m_logger->ToggleVisibility();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Console"))
        {
            m_terminal->ToggleVisibility();
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
#endif
}
