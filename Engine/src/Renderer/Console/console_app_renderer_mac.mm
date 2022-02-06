//
//  console_app_renderer_mac.cpp
//  Engine
//
//  Created by krzysp on 08/01/2022.
//

#include <Metal/Metal.h>
#include <QuartzCore/QuartzCore.h>
#include "common.h"
#include "console_renderer.h"
#include "engine.hpp"
#include "console_logger.hpp"
#include "console_terminal.hpp"
#include "console_app_renderer_mac.hpp"
#include "imgui.h"
#include "imgui_impl_metal.h"
#include "imgui_impl_osx.h"

#if defined(TARGET_IOS) || defined(TARGET_TVOS)
#include <UIKit/UIKit.h>
#else
#include <Cocoa/Cocoa.h>
#endif

using namespace engine;

ConsoleAppRendererMac::ConsoleAppRendererMac()
    : ConsoleAppRendererI()
    , m_isSetup(false)
    , m_device(NULL)
    , m_renderPassDescriptor(NULL)
#if TARGET_OS_OSX
    , m_view(NULL)
#endif
{
}

void ConsoleAppRendererMac::SetDevice(MTL::Device *device)
{
    m_device = device;
}

#if TARGET_OS_OSX

void ConsoleAppRendererMac::SetView(NSView *view)
{
    m_view = view;
}

void ConsoleAppRendererMac::PrepareForFrame(NSView *view,
                                            MTL::RenderPassDescriptor *pass,
                                            MTL::CommandBuffer *buffer,
                                            MTL::RenderCommandEncoder *encoder)
{
#if SHOW_CONSOLE
    m_view = view;
    m_renderPassDescriptor = pass;
    m_commandBuffer = buffer;
    m_encoder = encoder;

    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize.x = view.bounds.size.width;
    io.DisplaySize.y = view.bounds.size.height;

#if TARGET_OS_OSX
    CGFloat framebufferScale = view.window.screen.backingScaleFactor ?: NSScreen.mainScreen.backingScaleFactor;
#else
    CGFloat framebufferScale = view.window.screen.scale ?: UIScreen.mainScreen.scale;
#endif
    io.DisplayFramebufferScale = ImVec2(framebufferScale, framebufferScale);
#endif
}

bool ConsoleAppRendererMac::HandleEvent(NSEvent *event)
{
#if SHOW_CONSOLE
    return ImGui_ImplOSX_HandleEvent(event, m_view);
#else
    return false;
#endif
}

#endif

void ConsoleAppRendererMac::SetupWindow()
{
#if SHOW_CONSOLE
    if (m_isSetup) { return; };

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplMetal_Init((__bridge id<MTLDevice>)m_device);

#if TARGET_OS_OSX
    ImGui_ImplOSX_Init(m_view);
#endif
    
    m_isSetup = true;
#endif
}

void ConsoleAppRendererMac::DoFrame(std::function<void(void)> lambda)
{
#if SHOW_CONSOLE
    if (!m_isSetup) { return; };
    if (m_renderPassDescriptor == nullptr) { return; };

    ImGui_ImplMetal_NewFrame((__bridge MTLRenderPassDescriptor*)m_renderPassDescriptor);

    #if TARGET_OS_OSX
    ImGui_ImplOSX_NewFrame(m_view);
    #endif

    ImGui::NewFrame();
    lambda();
#endif
}

void ConsoleAppRendererMac::Render()
{
#if SHOW_CONSOLE
    ImGui::Render();
    ImDrawData* draw_data = ImGui::GetDrawData();

    ImGui_ImplMetal_RenderDrawData(
       draw_data,
       (__bridge id<MTLCommandBuffer>)m_commandBuffer,
       (__bridge id<MTLRenderCommandEncoder>)m_encoder
    );

    m_renderPassDescriptor = nullptr;
    m_commandBuffer = nullptr;
    m_encoder = nullptr;
#endif
}

bool ConsoleAppRendererMac::IsSetup()
{
    return m_isSetup;
}

void ConsoleAppRendererMac::SetConsoleHidden(bool hidden)
{
    // TODO: not implemented
}

void ConsoleAppRendererMac::Setup()
{
#if SHOW_CONSOLE
    SetupWindow();
#endif
}
