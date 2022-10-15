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

#include <Metal/Metal.h>
#include <QuartzCore/QuartzCore.h>
#include "common.h"
#include "console_renderer.h"
#include "engine.hpp"
#include "console_logger.hpp"
#include "console_terminal.hpp"
#include "console_lights.hpp"

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
    this->m_lightManagement = new ConsoleLightManagement();
}

ConsoleRenderer::~ConsoleRenderer()
{
}

ConsoleLogI& ConsoleRenderer::GetLogger()
{
    return *m_logger;
}

ConsoleTerminalI& ConsoleRenderer::GetTerminal()
{
    return *m_terminal;
}

ConsoleLightManagementI& ConsoleRenderer::GetLightManagement()
{
    return *m_lightManagement;
}

void ConsoleRenderer::Setup()
{
#if SHOW_CONSOLE
    SetupEvents();
#endif
}

void ConsoleRenderer::SetupEvents()
{
    ENGINE()
        .getEventsManager()
        .RegisterKeyShortcut( {FLAG_NONE}, {CODE_TIDLE}, CallableParametersEmpty::make_shared([&](void){
            this->SetConsoleHidden(!m_hidden);
        }));
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
    ImGui::ShowDemoWindow();

    m_logger->Render();
    m_terminal->Render();
    m_lightManagement->Render();
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
        if (ImGui::BeginMenu("LightManager"))
        {
            m_lightManagement->ToggleVisibility();
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
#endif
}
